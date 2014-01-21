#ifndef TRAPEZOIDAL_H
#define TRAPEZOIDAL_H

#include <numerica/tools/nvector.h>

namespace numerica
{
    namespace integration
    {
        using numerica::tools::NVector;

        double Trapezoidal(const NVector &y, double a, double b);
        template<class Function>
        double Trapezoidal(const Function &f,double a,double b,int nEvals);
    }
}




//---------- Definitions -----------------------

namespace numerica
{
    template<class Function>
    double integration::Trapezoidal(const Function &f,double a,double b,int nEvals)
    {
        NVector y(nEvals);
        double h=(b-a)/(nEvals-1);
        for(int i=0;i<nEvals;i++)
            y[i]=f(a+h*i);
        return Trapezoidal(y,a,b);
    }
}



#endif // TRAPEZOIDAL_H
