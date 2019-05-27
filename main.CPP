#include "jobshop.h"
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    cerr << "Aciturri JobShop build " <<  __DATE__ << " " << __TIME__ << endl;
    if (argc != 2) {
        cerr << "Modo de uso: " << endl;
        cerr << argv[0] << " entrada.txt" << endl;
        return EXIT_FAILURE;
    }

    GRBEnv env = GRBEnv("debug_gurobi.log");
    try {
        GRBModel model = GRBModel(env);

        // input
        vector <job> MyJobShop;
        int DueDate = -1;
        int BigM = -1;
        int fobjtype = -1;  // 1 = min makespan , 2 max job finished

        if ( string(argv[1]) == "demo1" )  {
            DueDate = 8*60;
            BigM = DueDate;
            fobjtype = 1;
            loaddata_demo1(MyJobShop);
        } else if ( string(argv[1]) == "demo2" )  {
            DueDate = 16*60;
            BigM = DueDate;
            fobjtype = 2;
            loaddata_demo2(MyJobShop);
        } else {
            if ( loaddata_file(MyJobShop, string(argv[1]), DueDate, BigM, fobjtype ) ) return EXIT_FAILURE;
        }

        // debug input
        ofstream loginput("debug_input.log");
        loginput << "* INPUT DATA *" << endl;
        loginput << "Due Date " << DueDate << endl;
        loginput << "Big M " << BigM << endl;
        loginput << "Function Objective Type " << fobjtype << endl;
        loginput << "# Jobs " << MyJobShop.size() << endl;
        for (unsigned int i=0; i<MyJobShop.size(); ++i) {
            loginput << "Job Name: " << MyJobShop[i].name << "_#" << i+1 << endl;
            loginput << "Force_Begin: " << MyJobShop[i].force_begin << endl;
            loginput << "Force_Finish: " << MyJobShop[i].force_finish << endl;
            for (unsigned int j=0; j<MyJobShop[i].ops.size(); ++j ){
                loginput << " Ops " << j+1 << " Machine " << MyJobShop[i].ops[j].machine
                         << " Duration " << MyJobShop[i].ops[j].duration
                         << " ExtraTime " << MyJobShop[i].ops[j].extratime
                         << " SetupTime " << MyJobShop[i].ops[j].setuptime
                         << endl;
            }
        }
        loginput.close();

        // Variable JobNotFinished: Job
        // Variable BeginTime: Job, Op
        // Variable ExtraTimeUsed: Job, Op
        for (unsigned int i=0; i<MyJobShop.size(); ++i) {
            stringstream nn0;
            nn0 << "JNF" << i+1;
            MyJobShop[i].JobNotFinished = model.addVar(0, 1, 0, GRB_BINARY, nn0.str() );
            for (unsigned int j=0; j<MyJobShop[i].ops.size(); ++j ){
                stringstream nn1;
                nn1 << "ST" << i+1 << "o" << j+1;
                MyJobShop[i].ops[j].SetupTime = model.addVar(MyJobShop[i].ops[j].setuptime, MyJobShop[i].ops[j].setuptime, 0, GRB_CONTINUOUS, nn1.str() );
                stringstream nn2;
                nn2 << "BT" << i+1 << "o" << j+1;
                MyJobShop[i].ops[j].BeginTime = model.addVar(0, GRB_INFINITY, 0, GRB_INTEGER, nn2.str() );
                stringstream nn3;
                nn3 << "ETU" << i+1 << "o" << j+1;
                MyJobShop[i].ops[j].ExtraTimeUsed = model.addVar(0, (MyJobShop[i].ops[j].extratime == -1 ? GRB_INFINITY : MyJobShop[i].ops[j].extratime), 0, GRB_CONTINUOUS, nn3.str() );
            }
        }
        GRBVar makespan = model.addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, "MakeSpan");
        model.update();

        if ( fobjtype == 1 ) {
            for (unsigned int i=0; i<MyJobShop.size(); ++i) {
                MyJobShop[i].JobNotFinished.set(GRB_DoubleAttr_UB, 0);
                int EndOps = MyJobShop[i].ops.size()-1;

                stringstream nn1;
                nn1 << "MS" << i+1;
                model.addConstr( MyJobShop[i].ops[EndOps].BeginTime
                                + MyJobShop[i].ops[EndOps].SetupTime
                                + MyJobShop[i].ops[EndOps].duration
                                + MyJobShop[i].ops[EndOps].ExtraTimeUsed
                                <= makespan, nn1.str() );
            }
            model.update();
        } else if ( fobjtype == 2) {
            // Constrain JobNotFinished
            for (unsigned int i=0; i<MyJobShop.size(); ++i) {
                int EndOps = MyJobShop[i].ops.size()-1;

                stringstream nn1;
                nn1 << "NF" << i+1;
                model.addConstr( MyJobShop[i].ops[EndOps].BeginTime
                                + MyJobShop[i].ops[EndOps].SetupTime
                                + MyJobShop[i].ops[EndOps].duration
                                + MyJobShop[i].ops[EndOps].ExtraTimeUsed
                                <= DueDate + BigM*MyJobShop[i].JobNotFinished, nn1.str() );
            }
            model.update();
        } else  {
            cerr << "Bad fobjtype = " << fobjtype << endl;
            return EXIT_FAILURE;
        }

        // force begin, force finish
        for (unsigned int i=0; i<MyJobShop.size(); ++i) {
            if (MyJobShop[i].force_begin != -1) {
                MyJobShop[i].JobNotFinished.set(GRB_DoubleAttr_UB, 0);
                 MyJobShop[i].ops[0].BeginTime.set(GRB_DoubleAttr_UB, MyJobShop[i].force_begin);
            }
            if (MyJobShop[i].force_finish != -1) {
                MyJobShop[i].JobNotFinished.set(GRB_DoubleAttr_UB, 0);
                int EndOps = MyJobShop[i].ops.size()-1;
                stringstream nn1;
                nn1 << "FF" << i+1;
                model.addConstr( MyJobShop[i].ops[EndOps].BeginTime
                                + MyJobShop[i].ops[EndOps].SetupTime
                                + MyJobShop[i].ops[EndOps].duration
                                + MyJobShop[i].ops[EndOps].ExtraTimeUsed
                                <= MyJobShop[i].force_finish, nn1.str() );
            }
        }

        // Constrain Sequence
        for (unsigned int i=0; i<MyJobShop.size(); ++i) {
            for (unsigned int j=0; j<MyJobShop[i].ops.size()-1; ++j ){
                stringstream nn1;
                nn1 << "S" << i+1 << "o" << j+1;
                model.addConstr( MyJobShop[i].ops[j].BeginTime
                                + MyJobShop[i].ops[j].SetupTime
                                + MyJobShop[i].ops[j].duration
                                + MyJobShop[i].ops[j].ExtraTimeUsed
                                == MyJobShop[i].ops[j+1].BeginTime
                                , nn1.str() );
            }
        }
        model.update();

        // Variable BeforeORAfter: Job Op Job Op
        vector <GRBVar> BeforeORAfter;
        for (unsigned int i=0; i<MyJobShop.size(); ++i) {
            for (unsigned int j=0; j<MyJobShop[i].ops.size(); ++j ) {
                for (unsigned int ii=i+1; ii<MyJobShop.size(); ++ii) {
                    for (unsigned int jj=0; jj<MyJobShop[ii].ops.size(); ++jj ) {
                        int m1 = MyJobShop[i].ops[j].machine;
                        int m2 = MyJobShop[ii].ops[jj].machine;
                        if ( m1 != m2 ) {
                            stringstream nn;
                            nn << "BoAm" << MyJobShop[i].ops[j].machine
                               << "f" << i+1 << "o" << j+1
                               << "t" << ii+1 << "o" << jj+1;
                            BeforeORAfter.push_back( model.addVar(0, 1, 0, GRB_BINARY, nn.str())) ;
                            continue;
                        }

                        if ( ( MyJobShop[i].name == MyJobShop[ii].name ) && ( j == jj ) ) {
                        } else {
                            stringstream nn;
                            nn << "BoAm" << MyJobShop[i].ops[j].machine
                               << "f" << i+1 << "o" << j+1
                               << "t" << ii+1 << "o" << jj+1;
                            BeforeORAfter.push_back( model.addVar(0, 1, 0, GRB_BINARY, nn.str())) ;
                        }
                    }
                }
            }
        }
        model.update();

        // Constrain BeforeORAfter
        for (unsigned int i=0; i<MyJobShop.size(); ++i) {
            for (unsigned int j=0; j<MyJobShop[i].ops.size(); ++j ) {
                for (unsigned int ii=i+1; ii<MyJobShop.size(); ++ii) {
                    for (unsigned int jj=0; jj<MyJobShop[ii].ops.size(); ++jj ) {
                        int m1 = MyJobShop[i].ops[j].machine;
                        int m2 = MyJobShop[ii].ops[jj].machine;
                        static int BoA = 0;

                        if ( m1 != m2 ) {
                            model.addConstr( MyJobShop[i].ops[j].BeginTime
                                            + MyJobShop[i].ops[j].SetupTime
                                            + ( j && jj && MyJobShop[i].ops[j].duration <= MyJobShop[i].ops[j].setuptime ? 1 : 0)
                                            - BigM*MyJobShop[i].JobNotFinished
                                            <= MyJobShop[ii].ops[jj].BeginTime
                                            + BigM*BeforeORAfter[BoA] );
                            model.addConstr( MyJobShop[ii].ops[jj].BeginTime
                                            + MyJobShop[ii].ops[jj].SetupTime
                                            + ( j && jj && MyJobShop[ii].ops[jj].duration <= MyJobShop[ii].ops[jj].setuptime ? 1 : 0)
                                            - BigM*MyJobShop[ii].JobNotFinished
                                            <= MyJobShop[i].ops[j].BeginTime
                                            + BigM - BigM*BeforeORAfter[BoA] );
                            BoA++;
                            continue;
                        }

                        if ( ( MyJobShop[i].name == MyJobShop[ii].name ) && ( j == jj ) ) {
                            model.addConstr( MyJobShop[i].ops[j].BeginTime
                                            + MyJobShop[i].ops[j].SetupTime
                                            + ( j && jj && MyJobShop[i].ops[j].duration <= MyJobShop[i].ops[j].setuptime ? 1 : 0)
                                            + MyJobShop[i].ops[j].duration
                                            + MyJobShop[i].ops[j].ExtraTimeUsed
                                            - BigM*MyJobShop[i].JobNotFinished
                                            <= MyJobShop[ii].ops[jj].BeginTime );
                        } else {
                            model.addConstr( MyJobShop[i].ops[j].BeginTime
                                            + MyJobShop[i].ops[j].SetupTime
                                            + ( j && jj && MyJobShop[i].ops[j].duration <= MyJobShop[i].ops[j].setuptime ? 1 : 0)
                                            + MyJobShop[i].ops[j].duration
                                            + MyJobShop[i].ops[j].ExtraTimeUsed
                                            - BigM*MyJobShop[i].JobNotFinished
                                            <= MyJobShop[ii].ops[jj].BeginTime
                                            + BigM*BeforeORAfter[BoA] );
                            model.addConstr( MyJobShop[ii].ops[jj].BeginTime
                                            + MyJobShop[ii].ops[jj].SetupTime
                                            + ( j && jj && MyJobShop[ii].ops[jj].duration <= MyJobShop[ii].ops[jj].setuptime ? 1 : 0)
                                            + MyJobShop[ii].ops[jj].duration
                                            + MyJobShop[ii].ops[jj].ExtraTimeUsed
                                            - BigM*MyJobShop[ii].JobNotFinished
                                            <= MyJobShop[i].ops[j].BeginTime
                                            + BigM - BigM*BeforeORAfter[BoA] );
                            BoA++;
                        }
                    }
                }
            }
        }
        model.update();

        model.setCallback(new logmipsol(MyJobShop));
        // model.getEnv().set(GRB_IntParam_MIPFocus, GRB_MIPFOCUS_FEASIBILITY);
        // model.getEnv().set(GRB_DoubleParam_Heuristics, 0.66);
        // model.getEnv().set(GRB_IntParam_PumpPasses, max(BigM, DueDate));
        // model.getEnv().set(GRB_IntParam_MinRelNodes, max(BigM, DueDate));
        // model.getEnv().set(GRB_IntParam_VarBranch, GRB_VARBRANCH_MAX_INFEAS);

        if ( fobjtype == 1 ) {
            // Objetive Min Makespan
            model.set(GRB_IntAttr_ModelSense, +1); // Min
            makespan.set(GRB_DoubleAttr_Obj, 1);
            model.update();
        } else if ( fobjtype == 2) {
            // Objetive function Max NJob - JobNotFinished = Max Job Finished
            for (unsigned int i=0; i<MyJobShop.size(); ++i) {
                MyJobShop[i].JobNotFinished.set(GRB_DoubleAttr_Obj, -1 );
            }
            model.set(GRB_DoubleAttr_ObjCon, MyJobShop.size());
            model.set(GRB_IntAttr_ModelSense, -1); // Max
            model.update();
        } else  {
            cerr << "Bad fobjtype = " << fobjtype << endl;
            return EXIT_FAILURE;
        }

        model.write("debug_model.mps");
        model.optimize();

        if ( model.get(GRB_IntAttr_SolCount) ) {
            cout << " ** Solution found! ** " << endl;
            ofstream logsolution("debug_solution.log");
            logsolution << "* Jobs *" << endl;
            logsolution << "JobName" << '\t'
                        << "Ops" << '\t'
                        << "Machine" << '\t'
                        << "StartUpTime" << '\t'
                        << "SetupTime" << '\t'
                        << "BeginTime" << '\t'
                        << "Duration" << '\t'
                        << "EndTime" << '\t'
                        << "BoundDuration" << '\t'
                        << "BoundExtraTime" << '\t'
                        << endl;
            for (unsigned int i=0; i<MyJobShop.size(); ++i) {
                if ( floor(0.5+ MyJobShop[i].JobNotFinished.get(GRB_DoubleAttr_X))) continue;
                for (unsigned int j=0; j<MyJobShop[i].ops.size(); ++j ){
                    logsolution << MyJobShop[i].name << "_#" << i+1 << '\t'
                                << j+1 << '\t'
                                << MyJobShop[i].ops[j].machine << '\t'
                                << MyJobShop[i].ops[j].BeginTime.get(GRB_DoubleAttr_X) << '\t'
                                << MyJobShop[i].ops[j].SetupTime.get(GRB_DoubleAttr_X) << '\t'
                                << MyJobShop[i].ops[j].BeginTime.get(GRB_DoubleAttr_X)+MyJobShop[i].ops[j].SetupTime.get(GRB_DoubleAttr_X) << '\t'
                                << MyJobShop[i].ops[j].duration+MyJobShop[i].ops[j].ExtraTimeUsed.get(GRB_DoubleAttr_X) << '\t'
                                << MyJobShop[i].ops[j].BeginTime.get(GRB_DoubleAttr_X)+MyJobShop[i].ops[j].SetupTime.get(GRB_DoubleAttr_X)+MyJobShop[i].ops[j].duration+MyJobShop[i].ops[j].ExtraTimeUsed.get(GRB_DoubleAttr_X) << '\t'
                                << MyJobShop[i].ops[j].duration << '\t'
                                << MyJobShop[i].ops[j].extratime << '\t'
                                << endl;
                }
            }
            logsolution.close();
        } else {
            cout << " ** Error ** Not solution found !" << endl;
        }

    } catch(GRBException e) {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch (...) {
        cout << "Error during optimization" << endl;
    }

    return EXIT_SUCCESS;
}

void logmipsol::callback() {
    try {
        if (where == GRB_CB_MIPSOL) {
            stringstream nn;
            nn << "debug_solution_" << getIntInfo(GRB_CB_MIPSOL_SOLCNT) << ".log";
            ofstream logsolution(nn.str().c_str());
            logsolution << "* Jobs *" << endl;
            logsolution << "JobName" << '\t'
                        << "Ops" << '\t'
                        << "Machine" << '\t'
                        << "StartUpTime" << '\t'
                        << "SetupTime" << '\t'
                        << "BeginTime" << '\t'
                        << "Duration" << '\t'
                        << "EndTime" << '\t'
                        << "BoundDuration" << '\t'
                        << "BoundExtraTime" << '\t'
                        << endl;
            for (unsigned int i=0; i<_js.size(); ++i) {
                if ( floor(0.5 + getVarSolution(_js[i].JobNotFinished))) continue;
                for (unsigned int j=0; j<_js[i].ops.size(); ++j ){
                    logsolution << _js[i].name << "_#" << i+1 << '\t'
                                << j+1 << '\t'
                                << _js[i].ops[j].machine << '\t'
                                << getVarSolution(_js[i].ops[j].BeginTime) << '\t'
                                << getVarSolution(_js[i].ops[j].SetupTime) << '\t'
                                << getVarSolution(_js[i].ops[j].BeginTime)+getVarSolution(_js[i].ops[j].SetupTime) << '\t'
                                << _js[i].ops[j].duration+getVarSolution(_js[i].ops[j].ExtraTimeUsed) << '\t'
                                << getVarSolution(_js[i].ops[j].BeginTime)+getVarSolution(_js[i].ops[j].SetupTime)+_js[i].ops[j].duration+getVarSolution(_js[i].ops[j].ExtraTimeUsed) << '\t'
                                << _js[i].ops[j].duration << '\t'
                                << _js[i].ops[j].extratime << '\t'
                                << endl;
                }
            }
            logsolution.close();
        }
    } catch (GRBException e) {
        cout << "Error number: " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch (...) {
        cout << "Error during callback" << endl;
    }
}
