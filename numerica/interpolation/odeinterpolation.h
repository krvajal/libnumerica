#ifndef ODEINTERPOLATION_H
#define ODEINTERPOLATION_H

#include<vector>
#include "hermiteinterpolation.h"

namespace numerica
{
    namespace interpolation
    {
        class OdeInterpolation
        {
        public:
            OdeInterpolation(const NVector& datax,const NVector& datay,const NVector& datayDer);
            double operator()(double x);

            NVector dx,dy,dyDer;
        private:
            std::vector<HermiteInterpolation> hs;
        };
    }
}

#endif // ODEINTERPOLATION_H
