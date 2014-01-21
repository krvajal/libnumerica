#ifndef DORMANDPRINCE54_H
#define DORMANDPRINCE54_H

#include"embeddedrungekuttabase.h"


namespace numerica
{
    namespace ode
    {
        class DormandPrince54 : public EmbeddedRungeKuttaBase
        {
        public:
            DormandPrince54(double t1, double t2,const NVector& y0,
                            double Tol=1e-5,double hmax=1,double hmin=1e-7);
        };
    }
}


#endif // DORMANDPRINCE54_H
