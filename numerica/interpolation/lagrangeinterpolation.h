#ifndef LAGRANGEPOLYNOMIAL_H
#define LAGRANGEPOLYNOMIAL_H

#include "../tools/nvector.h"

namespace numerica
{
    namespace interpolation
    {
        using tools::NVector;

        class LagrangeInterpolation
        {
        public:
            LagrangeInterpolation(const NVector& datax,const NVector& datay);
            double operator()(double x);

            NVector dx,dy;

        };


    }
}

#endif // LAGRANGEPOLYNOMIAL_H
