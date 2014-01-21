#ifndef CUBICNATURALSPLINE_H
#define CUBICNATURALSPLINE_H

#include "../tools/nvector.h"

namespace numerica
{
    namespace interpolation
    {
        using tools::NVector;
        class NaturalCubicSpline
        {
        public:
            NaturalCubicSpline(const NVector& datax,const NVector& datay);
            double operator()(double x);

            NVector dx,dy;

        private:
            NVector A,B,D,C;
        };

    }
}

#endif // CUBICNATURALSPLINE_H
