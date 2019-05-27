#ifndef JOBSHOP_H
#define JOBSHOP_H

#include <gurobi_c++.h>

class operation {
public:
    int machine;
    int duration;
    int extratime;
    int setuptime;
    GRBVar SetupTime;
    GRBVar BeginTime;
    GRBVar ExtraTimeUsed;
    operation(int _m, int _t, int _e, int _s): machine(_m), duration(_t), extratime(_e), setuptime(_s) {}
};

class job {
public:
    string name;
    vector <operation> ops;
    GRBVar JobNotFinished;
    int force_begin;
    int force_finish;
    job(string _n="MyJob", int _fb=-1, int _fe=-1) : name(_n), force_begin(_fb), force_finish(_fe) {}
    void addops(int _m=-1, int _t=-1, int _e=-1, int _s=2) {
        ops.push_back( operation(_m, _t, _e, _s ) );
    }
};

class logmipsol: public GRBCallback {
private:
    vector<job> _js;
protected:
    void callback();
public:
    logmipsol(vector<job> &_my) : _js(_my)  { }
};

void loaddata_demo1(vector<job> &_myj);
void loaddata_demo2(vector<job> &_myj);
int loaddata_file(vector<job> &_myj, string input, int &DueDate, int &BigM, int &fobjtype);

#endif // JOBSHOP_H
