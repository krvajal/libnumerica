#include "dormandprince54.h"

using namespace numerica;
using namespace ode;

DormandPrince54::DormandPrince54
        (double t1, double t2,const NVector& y0,double Tol,double hmax,double hmin)
            :EmbeddedRungeKuttaBase(t1,t2,y0,Tol,hmax,hmin,7,5)
{
    static double acoeff[]=
    {
        0,            0,            0,            0,           0,            0,
        1./5,         0,            0,            0,           0,            0,
        3./40,        9./40,        0,            0,           0,            0,
        44./45,      -56./15,       32./9,        0,           0,            0,
        19372./6561, -25360./2187,  64448./6561, -212./729,    0,            0,
        9017./3168,  -355./33,      46732./5247,  49./176,    -5103./18656,  0,
        35./384,      0,            500./1113,    125./192,   -2187./6784,   11./84
    };
    static double bcoeff[7]={35./384,0,500./1113,125./192,-2187./6784,11./84,0};
    static double ccoeff[7]={0,1./5,3./10,4./5,8./9,1,1};
    static double dcoeff[7]={71./57600,0,-71./16695,71./1920,-17253./339200,22./525,-1./40};

    a=Matrix(acoeff,nStages,nStages-1);
    b=NVector(bcoeff,nStages);
    c=NVector(ccoeff,nStages);
    d=NVector(dcoeff,nStages);
}
