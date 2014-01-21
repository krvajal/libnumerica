#ifndef NEWTONPOLYNOMIAL_H
#define NEWTONPOLYNOMIAL_H

#include "../tools/nmatrix.h"

namespace numerica
{
    namespace interpolation
    {
        using tools::Matrix;
        using tools::NVector;

        class NewtonInterpolation
        {
        public:
            NewtonInterpolation(const NVector& datax,const NVector& datay);
            double operator()(double x);

            NVector dx,dy;
            NVector coeff;

        private:
            Matrix dd;

        };
    }
}
#endif // NEWTONPOLYNOMIAL_H
