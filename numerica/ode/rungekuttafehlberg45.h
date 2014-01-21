#ifndef RUNGEKUTTAFEHLBERG45_H
#define RUNGEKUTTAFEHLBERG45_H

#include"embeddedrungekuttabase.h"

namespace numerica
{
    namespace ode
    {
        class RungeKuttaFehlberg45: public EmbeddedRungeKuttaBase
        {
        public:
            RungeKuttaFehlberg45(double t1, double t2,const NVector& y0,
                                 double Tol=1e-5,double hmax=1,double hmin=1e-7);
        };
    }
}




#endif // RUNGEKUTTAFEHLBERG45_H
