#ifndef HERMITEPOLYNOMIAL_H
#define HERMITEPOLYNOMIAL_H

#include "../tools/nvector.h"

namespace numerica
{
    namespace interpolation
    {
        using tools::NVector;

        class HermiteInterpolation
        {
        public:
            HermiteInterpolation(const NVector& datax,const NVector& datay,const NVector& datayDer);
            double operator()(double x);

            NVector dx,dy,dyDer;
            NVector coeff;
        };


    }
}

#endif // HERMITEPOLYNOMIAL_H
