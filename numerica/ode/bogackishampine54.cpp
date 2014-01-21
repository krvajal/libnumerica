#include"bogackishampine54.h"

using namespace numerica;
using namespace ode;

BogackiShampine54::BogackiShampine54
        (double t1, double t2,const NVector& y0,
         double Tol,double hmax,double hmin)
             :EmbeddedRungeKuttaBase(t1,t2,y0,Tol,hmax,hmin,8,5)

{
    static double acoeff[]=
    {
        0,                0,              0,                   0,                 0,              0,               0,
        1./6,             0,              0,                   0,                 0,              0,               0,
        2./27,            4./27,          0,                   0,                 0,              0,               0,
        183./1372,       -162./343,       1053./1372,          0,                 0,              0,               0,
        68./297,         -4./11,          42./143,             1960./3861,        0,              0,               0,
        597./22528,       81./352,        63099./585728,       58653./366080,     4617./20480,    0,               0,
        174197./959244,  -30942./79937,   8152137./19744439,   666106./1039181,  -29421./29068,   482948./414219,  0,
        587./8064,        0,              4440339./15491840,   24353./124800,     387./44800,     2152./5985,      7267./94080
    };
    static double bcoeff[]={587./8064, 0, 4440339./15491840, 24353./124800, 387./44800, 2152./5985,7267./94080, 0};
    static double ccoeff[]={0, 1./6, 2./9, 3./7, 2./3, 3./4, 1, 1};
    static double dcoeff[]={3817./1959552,0,-140181./15491840,4224731./272937600,-8557./403200,57928./4363065,23930231./4366535040,-3293./556956};

    a=Matrix(acoeff,nStages,nStages-1);
    b=NVector(bcoeff,nStages);
    c=NVector(ccoeff,nStages);
    d=NVector(dcoeff,nStages);
}
