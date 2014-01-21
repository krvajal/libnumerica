#ifndef RUNGEKUTTAVERNER56_H
#define RUNGEKUTTAVERNER56_H

#include"embeddedrungekuttabase.h"

namespace numerica
{
    namespace ode
    {
        class RungeKuttaVerner56:public EmbeddedRungeKuttaBase
        {
        public:
            RungeKuttaVerner56(double t1, double t2,const NVector& y0,
                               double Tol=1e-5,double hmax=1,double hmin=1e-7);
        };
    }
}



#endif // RUNGEKUTTAVERNER56_H
