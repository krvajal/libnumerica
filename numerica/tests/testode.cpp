#include <numerica/ode/ode.h>
#include <numerica/tests/testode.h>

#include <iomanip>

using namespace numerica;
using namespace numerica::ode;
using namespace std;

//------------------------------Functions -------------------------

inline NVector f(double t,const NVector& y)
{
    double yp[]={y[1],-y[0]};
    return NVector(yp,y.size());
}

class F
{
public:
    F(double a):a_(a){}
    inline NVector operator()(double t,const NVector& y)
    {
        double yp[]={y[1],-y[0]};
        return NVector(yp,y.size());
    }
private:
    double a_;
};


//------------------------- Tests -------------------------------------


template<class Method>
void TestParticularOde(string name)
{
    double dy0[]={1,0};
    const int n=sizeof(dy0)/sizeof(double);
    NVector y0(dy0,n);
    Method sol(0,8,y0);
    F f(1);
    sol.DoIt(f);
    cout << name<< "  starts" <<endl;
    for (unsigned i=0;i<sol.t.size();i++)
        cout<<sol.t[i]<<" "<<sol.solution[0](sol.t[i])-cos(sol.t[i])<<endl;
    cout<<"total="<<sol.t.size()<<endl;
    //plot(sol.solution[0],sol.solution[1],sol.solution[0].dx.min(),sol.solution[0].dx.max());
    cout<<name<<" ends"<<endl<<endl;
}


void TestOde()
{
    TestParticularOde<RungeKuttaFehlberg45>("RKF45");
    TestParticularOde<DormandPrince54>("DP54");
    TestParticularOde<BogackiShampine54>("BS54");
    TestParticularOde<RungeKuttaVerner56>("RKV56");
    TestParticularOde<RungeKuttaVerner98>("RKV98");
}



