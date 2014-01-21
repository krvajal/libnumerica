#ifndef BOGACKISHAMPINE45_H
#define BOGACKISHAMPINE45_H

#include"embeddedrungekuttabase.h"


namespace numerica
{
    namespace ode
    {
        class BogackiShampine54 : public EmbeddedRungeKuttaBase
        {
        public:
            BogackiShampine54(double t1, double t2,const NVector& y0,
                              double Tol=1e-8,double hmax=1,double hmin=1e-9);
        };
    }
}


#endif // BOGACKISHAMPINE45_H
