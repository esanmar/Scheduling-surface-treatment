#include "jobshop.h"
#include <cstdlib>

using namespace std;

void loaddata_demo1(vector<job> &_myj) {
    // ALODIADO
    for (int i=0; i<=0; ++i) { // 1
        _myj.push_back(job("alodiado"));
        _myj[i].addops(0,1,100);
        _myj[i].addops(3,10,5);
        _myj[i].addops(5,5,10);
        _myj[i].addops(4,2,0);
        _myj[i].addops(5,5,10);
        _myj[i].addops(7,10,0);
        _myj[i].addops(9,2,0);
        _myj[i].addops(25,2,0);
        _myj[i].addops(26,2,0);
        _myj[i].addops(35,30,0);
        _myj[i].addops(37,2,100);
    }
    // ANODIZADO CRÓMICO SIN SELLAR TIPO I
    for (int i=1; i<=3; ++i) { // 3
        _myj.push_back(job("anodcrom"));
        _myj[i].addops(0,1,100);
        _myj[i].addops(3,10,5);
        _myj[i].addops(5,5,5);
        _myj[i].addops(7,1,4);
        _myj[i].addops(9,5,5);
        _myj[i].addops(16,51,0);
        _myj[i].addops(18,1,1);
        _myj[i].addops(30,5,5);
        _myj[i].addops(35,30,30);
        _myj[i].addops(37,2,100);
    }
    // ANODIZADO SULFÚRICO SIN SELLAR TITANIO
    for (int i=4; i<=4; ++i) { // 1
        _myj.push_back(job("anodsulftita"));
        _myj[i].addops(0,1,100);
        _myj[i].addops(3,12,8);
        _myj[i].addops(5,5,15);
        _myj[i].addops(11,1,19);
        _myj[i].addops(20,5,15);
        _myj[i].addops(15,5,20);
        _myj[i].addops(19,15,5);
        _myj[i].addops(20,2,18);
        _myj[i].addops(22,5,15);
        _myj[i].addops(35,30,100);
        _myj[i].addops(37,2,100);
    }
    // LIMPIEZA Y DECAPADO DE ALUMINIO
    for (int i=5; i<=5; ++i) { // 1
        _myj.push_back(job("limpdecalum"));
        _myj[i].addops(0,1,100);
        _myj[i].addops(3,10,5);
        _myj[i].addops(5,5,5);
        _myj[i].addops(35,30,30);
        _myj[i].addops(37,2,100);
    }
}

void loaddata_demo2(vector<job> &_myj) {
    // LIMPIEZA POR EMULSIÓN
    for (int i=0; i<=0; ++i) { // 1
        _myj.push_back(job("limpiezaemulsion"));
        _myj[i].addops(2,15,25);
        _myj[i].addops(5,10,20);
        _myj[i].addops(35,25);
        _myj[i].addops(37,0);
    }

    // DESENGRASE ALCALINO (RR) POST
    for (int i=1; i<=5; ++i) { // 5
        _myj.push_back(job("desengrasepost"));
        _myj[i].addops(3,20,0);
        _myj[i].addops(5,10,20);
        _myj[i].addops(35,60);
        _myj[i].addops(37,0);
    }

    // LIMPIEZA Y DECAPADO DE ALUMINIO
    for (int i=6; i<=14; ++i) { // 9
        _myj.push_back(job("limpdecalum"));
        _myj[i].addops(3,12,3);
        _myj[i].addops(5,5,10);
        _myj[i].addops(4,6,4);
        _myj[i].addops(5,5,5);
        _myj[i].addops(7,1,0);
        _myj[i].addops(9,10,5);
        _myj[i].addops(35,30);
        _myj[i].addops(37,0);
    }

    // LIMPIEZA Y DESOXIDADO DE ALUMINIO
    for (int i=15; i<=17; ++i) { // 3
        _myj.push_back(job("limpdesoalum"));
        _myj[i].addops(3,12,3);
        _myj[i].addops(5,5,10);
        _myj[i].addops(7,8,2);
        _myj[i].addops(9,10,5);
        _myj[i].addops(35,30);
        _myj[i].addops(37,0);
    }

    // LIMPIEZA Y DECAPADO DE TITANIO
    for (int i=18; i<=18; ++i) { // 1
        _myj.push_back(job("limpidecaptita"));
        _myj[i].addops(3,15,5);
        _myj[i].addops(5,10,5);
        _myj[i].addops(10,20,10);
        _myj[i].addops(20,5,10);
        _myj[i].addops(11,1,2);
        _myj[i].addops(10,1,4);
        _myj[i].addops(20,5,15);
        _myj[i].addops(15,10,5);
        _myj[i].addops(35,20,10);
        _myj[i].addops(37,0);
    }

    // ANODIZADO SULFÚRICO SIN SELLAR TITANIO
    for (int i=19; i<=19; ++i) { // 1
        _myj.push_back(job("anodsulftita"));
        _myj[i].addops(3,12,8);
        _myj[i].addops(5,5,15);
        _myj[i].addops(11,1,19);
        _myj[i].addops(20,5,15);
        _myj[i].addops(15,10,10);
        _myj[i].addops(19,15,5);
        _myj[i].addops(20,2,18);
        _myj[i].addops(22,10,10);
        _myj[i].addops(35,30);
        _myj[i].addops(37,0);
    }

    // ANODIZADO CRÓMICO SIN SELLAR TIPO I
    for (int i=20; i<=28; ++i) { // 9
        _myj.push_back(job("anodcrom"));
        _myj[i].addops(3,12,8);
        _myj[i].addops(5,5,15);
        _myj[i].addops(7,6,14);
        _myj[i].addops(9,5,15);
        _myj[i].addops(16,48,12);
        _myj[i].addops(18,5,15);
        _myj[i].addops(20,5,15);
        _myj[i].addops(30,5,15);
        _myj[i].addops(35,30);
        _myj[i].addops(37,0);
    }

    // ANODIZADO CRÓMICO SELLADO EN DICROMATO TIPO I
    for (int i=29; i<=29; ++i) { // 1
        _myj.push_back(job("anodcromdicro"));
        _myj[i].addops(3,12,8);
        _myj[i].addops(5,5,15);
        _myj[i].addops(7,8,12);
        _myj[i].addops(9,5,15);
        _myj[i].addops(16,48,12);
        _myj[i].addops(18,5,15);
        _myj[i].addops(20,2,3);
        _myj[i].addops(30,5,15);
        _myj[i].addops(32,40,0);
        _myj[i].addops(34,5,15);
        _myj[i].addops(35,30);
        _myj[i].addops(37,0);
    }

    // ANODIZADO CRÓMICO SELLADO EN AGUA TIPO I
    for (int i=30; i<=30; ++i) { // 1
        _myj.push_back(job("anodcromagua"));
        _myj[i].addops(3,12,8);
        _myj[i].addops(5,5,15);
        _myj[i].addops(7,6,14);
        _myj[i].addops(9,5,15);
        _myj[i].addops(16,56,0);
        _myj[i].addops(18,5,15);
        _myj[i].addops(20,2,3);
        _myj[i].addops(30,5,15);
        _myj[i].addops(31,40,10);
        _myj[i].addops(35,20);
        _myj[i].addops(37,0);
    }

    // ANODIZADO CRÓMICO SIN SELLAR TIPO IB
    for (int i=31; i<=31; ++i) { // 1
        _myj.push_back(job("anodcrom"));
        _myj[i].addops(3,12,8);
        _myj[i].addops(5,5,15);
        _myj[i].addops(1,8,12);
        _myj[i].addops(9,5,15);
        _myj[i].addops(16,56,0);
        _myj[i].addops(18,5,15);
        _myj[i].addops(20,2,3);
        _myj[i].addops(30,5,15);
        _myj[i].addops(35,30);
        _myj[i].addops(37,0);
    }

    // ANODIZADO CRÓMICO TIPO IB SELLADO EN DICROMATO
    for (int i=32; i<=32; ++i) { // 1
        _myj.push_back(job("andocromdib"));
        _myj[i].addops(3,12,8);
        _myj[i].addops(5,5,15);
        _myj[i].addops(7,8,12);
        _myj[i].addops(9,5,15);
        _myj[i].addops(16,56,0);
        _myj[i].addops(18,5,15);
        _myj[i].addops(20,2,3);
        _myj[i].addops(30,5,15);
        _myj[i].addops(32,40,0);
        _myj[i].addops(34,5,15);
        _myj[i].addops(35,30);
        _myj[i].addops(37,0);
    }

    // ALODIADO
    for (int i=33; i<=37; ++i) { // 5
        _myj.push_back(job("alodiado"));
        _myj[i].addops(3,12,0);
        _myj[i].addops(5,5,0);
        _myj[i].addops(7,10,0);
        _myj[i].addops(9,2,0);
        _myj[i].addops(24,2,0);
        _myj[i].addops(25,1,1);
        _myj[i].addops(26,2,0);
        _myj[i].addops(35,20);
        _myj[i].addops(37,0);
    }
}

int loaddata_file(vector<job> &_myj, string input, int &DueDate, int &BigM, int &fobjtype) {
    string tmp;
    int jn = 0;
    int infinito = 9999;

    ifstream fileinput(input.c_str());
    if (!fileinput) {
        cerr << "Error on fileinput" << endl;
        return EXIT_FAILURE;
    }

    fileinput >> tmp;
    if (tmp == "DueDate") {
        int t;
        fileinput >> t;
        DueDate = t;
    } else {
        cerr << "Error on fileinput DueDate" << endl;
        return EXIT_FAILURE;
    }

    fileinput >> tmp;
    if (tmp == "BigM") {
        int t;
        fileinput >> t;
        BigM = t;
    } else {
        cerr << "Error on fileinput BigM" << endl;
        return EXIT_FAILURE;
    }

    fileinput >> tmp;
    if (tmp == "fobj_t") {
        int t;
        fileinput >> t;
        fobjtype = t;
    } else {
        cerr << "Error on fileinput fobj_t" << endl;
        return EXIT_FAILURE;
    }

    fileinput >> tmp;
    while (tmp == "JobType") {
        string jobname;
        fileinput >> jobname;
        int num=0;
        int ops=0;
        int force_start=-1;
        int force_end=-1;

        fileinput >> tmp;
        if (tmp == "Number") {
            fileinput >> num;
        } else {
            cerr << "Error on fileinput Number" << endl;
            return EXIT_FAILURE;
        }

        fileinput >> tmp;
        if (tmp == "Operation") {
            fileinput >> ops;
        } else {
            cerr << "Error on fileinput Operation" << endl;
            return EXIT_FAILURE;
        }

        fileinput >> tmp;
        if (tmp == "start" ) {
            fileinput >> force_start;
            fileinput >> tmp;
        } else if ( tmp == "end") {
            fileinput >> force_end;
            fileinput >> tmp;
        }

        if (tmp != "Machine") {
            cerr << "Error on fileinput Machine" << endl;
            return EXIT_FAILURE;
        }

        fileinput >> tmp;
        if (tmp != "Duration") {
            cerr << "Error on fileinput Duration" << endl;
            return EXIT_FAILURE;
        }
        fileinput >> tmp;
        if (tmp != "MaxDuration") {
            cerr << "Error on fileinput MaxDuration" << endl;
            return EXIT_FAILURE;
        }
        fileinput >> tmp;
        if (tmp != "SetupTime") {
            cerr << "Error on fileinput SetupTime" << endl;
            return EXIT_FAILURE;
        }
        vector <vector <int> > jobdata(ops, vector<int>(4,0));
        for (int j=0; j<ops; ++j) {
            fileinput >> jobdata[j][0] // machine
                      >> jobdata[j][1] // duration
                      >> jobdata[j][2] // max duration -> extratime
                      >> jobdata[j][3] // setup
                         ;
            if (jobdata[j][2] == infinito) {
                jobdata[j][2] = -1;
            } else {
                jobdata[j][2] -= jobdata[j][1];
            }
        }

        for (int i=0; i<num; ++i) {
            _myj.push_back(job(jobname, force_start, force_end));
            for (int j=0; j<ops; ++j) {
                _myj[jn].addops(jobdata[j][0], jobdata[j][1], jobdata[j][2], jobdata[j][3]);
            }
            ++jn;
        }

        fileinput >> tmp;
    }

    if (tmp != "END") {
        cerr << "Error on fileinput, not EOF flag found " << endl;
        return EXIT_FAILURE;
    }

    fileinput.close();

    return EXIT_SUCCESS;
}
