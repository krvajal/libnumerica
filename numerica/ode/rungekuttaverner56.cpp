#include "rungekuttaverner56.h"

using namespace numerica;
using namespace ode;


RungeKuttaVerner56::RungeKuttaVerner56
        (double t1, double t2,const NVector& y0,
         double Tol,double hmax,double hmin)
             :EmbeddedRungeKuttaBase(t1,t2,y0,Tol,hmax,hmin,8,5)

{
    static double acoeff[]=
    {
        0,            0,         0,               0,          0,             0,             0,
        1./6,         0,         0,               0,          0,             0,             0,
        4./75,        16./75,    0,               0,          0,             0,             0,
        5./6,        -8./3,      5./2,            0,          0,             0,             0,
        -165./64,      55./6,    -425./64,         85./96,     0,             0,             0,
        12./5,       -8,         4015./612,      -11./36,     88./255,       0,             0,
        -8263./15000,  124./75,  -643./680,       -81./250,    2484./10625,   0,             0,
        3501./1720,  -300./43,   297275./52632,  -319./2322,  24068./84065,  0,   3850./26703
    };
    static double bcoeff[]={13./160, 0, 2375./5984, 5./16, 12./85, 3./44, 0, 0};
    static double ccoeff[]={0, 1./6, 4./15, 2./3, 5./6, 1, 1./15, 1};
    static double dcoeff[]={1./160, 0, 125./17952, -1./144, 12./1955, 3./44, -125./11592, -43./616};

    a=Matrix(acoeff,nStages,nStages-1);
    b=NVector(bcoeff,nStages);
    c=NVector(ccoeff,nStages);
    d=NVector(dcoeff,nStages);
}
