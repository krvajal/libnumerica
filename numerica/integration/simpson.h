#ifndef SIMPSON_H
#define SIMPSON_H

#include <numerica/tools/nvector.h>

namespace numerica
{
    namespace integration
    {
        using numerica::tools::NVector;
        double Simpson(const NVector &y, double a, double b);
        template<class Function>
        double Simpson(const Function &f,double a,double b,int nEvals);
    }
}




//---------- Definitions -----------------------

namespace numerica
{

    template<class Function>
    double integration::Simpson(const Function &f,double a,double b,int nEvals)
    {
        if ((nEvals & 1) ==0) nEvals++;
        NVector y(nEvals);
        double dx=(b-a)/(nEvals-1);
        for(int i=0;i<nEvals;i++)
            y[i]=f(a+dx*i);
        return Simpson(y,a,b);
    }
}




#endif // SIMPSON_H
