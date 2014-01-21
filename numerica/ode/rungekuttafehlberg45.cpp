#include "rungekuttafehlberg45.h"

using namespace numerica;
using namespace ode;

RungeKuttaFehlberg45::RungeKuttaFehlberg45
        (double t1, double t2,const NVector& y0,
         double Tol,double hmax,double hmin)
             :EmbeddedRungeKuttaBase(t1,t2,y0,Tol,hmax,hmin,6,4)

{
    static double acoeff[]=
    {
        0,           0,            0,           0,           0,
        1./4,        0,            0,           0,           0,
        3./32,       9./32,        0,           0,           0,
        1932./2197, -7200./2197,   7296./2197,  0,           0,
        439./216,   -8,            3680./513,  -845./4104,   0,
        -8./27,       2,           -3544./2565,  1859./4104, -11./40
    };
    static double bcoeff[]={25./216,0,1408./2565,2197./4104,-1./5,0};
    static double ccoeff[]={0,1./4,3./8,12./13,1,1./2};
    static double dcoeff[]={1./360,0,-128./4275,-2197./75240,1./50,2./55};

    a=Matrix(acoeff,nStages,nStages-1);
    b=NVector(bcoeff,nStages);
    c=NVector(ccoeff,nStages);
    d=NVector(dcoeff,nStages);
}

