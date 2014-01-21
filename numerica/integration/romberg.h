#ifndef ROMBERG_H
#define ROMBERG_H

#include <numerica/tools/nvector.h>

namespace numerica
{
    namespace integration
    {
        template<class Function>
        double Romberg(const Function &f,double a, double b, double tol=1e-5, int nExtrapols=10);
    }
}




//---------- Definitions -----------------------

#include <numerica/tools/nmatrix.h>

namespace numerica
{
    using numerica::tools::Matrix;
    template<class Function>
    double integration::Romberg(const Function &f, double a, double b, double tol, int nExtrapols)
    {
        Matrix I(nExtrapols,nExtrapols);
        int n=1;
        double h=b-a;
        I[0][0]=.5*h*(f(a)+f(b));
        for(int k=1;k<nExtrapols;k++)
        {
            double sum=0;
            for(int i=1;i<=n;i++)
                sum+=f(a+(i-.5)*h);
            I[k][0]=.5*(I[k-1][0]+h*sum);
            for(int j=1;j<=k;j++)
                I[k][j]=I[k][j-1]+(I[k][j-1]-I[k-1][j-1])/(pow(4.,j)-1.);
            if(fabs(I[k][k]-I[k-1][k-1])<tol)
                return I[k][k];
            n*=2;
            h*=.5;
        }
        throw std::runtime_error("integration::Romberg The nEvals extrapolations exceeded");
    }
}


#endif // ROMBERG_H
