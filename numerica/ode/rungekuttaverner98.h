#ifndef RUNGEKUTTAVERNER98_H
#define RUNGEKUTTAVERNER98_H

#include"embeddedrungekuttabase.h"

namespace numerica
{
    namespace ode
    {
        class RungeKuttaVerner98:public EmbeddedRungeKuttaBase
        {
        public:
            RungeKuttaVerner98(double t1, double t2,const NVector& y0,
                               double Tol=1e-8,double hmax=1,double hmin=1e-14);
        };
    }
}


#endif // RUNGEKUTTAVERNER98_H
