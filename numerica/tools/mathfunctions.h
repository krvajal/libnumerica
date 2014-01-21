#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include<complex>
#include "nvector.h"
#include "constants.h"

using std::complex;

namespace numerica
{
    namespace tools
    {
        inline double Norm2(const NVector& x) {return (x*x).sum();}

        inline double NormInf(const NVector& x) {return abs(x).max();}

        inline double Sign(double x)
        {
            if(x>0)
                return 1.;
            if(x<0)
                return -1.;
            else
                return 0.0;
        }

        inline unsigned long factorial(long n)
        {
            unsigned long a=1;
            for(long i=0;i<n;i++)
                a*=i+1;
            return a;
        }

    }
}

#endif // MATHFUNCTIONS_H
