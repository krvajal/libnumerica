#include "embeddedrungekuttabase.h"


using namespace numerica;
using namespace ode;

EmbeddedRungeKuttaBase::EmbeddedRungeKuttaBase
        (double t1, double t2,const NVector& y0,
         double Tol,double hmax,double hmin,int nStages,int order,int NMax)
             :t1(t1),t2(t2),Tol(Tol),hmax(hmax),hmin(hmin),
             nStages(nStages),order(order),NMax(NMax),
             y0(y0),b(nStages),c(nStages),d(nStages)
{}

void EmbeddedRungeKuttaBase::DoInterpolations()
{
    Matrix y(y0.size(),t.size()),yDer(y0.size(),t.size());
    NVector datax(t.size());
    for (int i=0;i<t.size();i++)
    {
        datax[i]=t[i];
        for (int j=0;j<y0.size();j++)
        {
            y[j][i]=w[i][j];
            yDer[j][i]=wp[i][j];
        }
    }
    for (int i=0;i<y0.size();i++)
        solution.push_back(OdeInterpolation(datax,y[i],yDer[i]));
}


