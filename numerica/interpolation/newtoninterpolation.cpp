#include "newtoninterpolation.h"

using namespace numerica::interpolation;

NewtonInterpolation::NewtonInterpolation
        (const NVector& datax,const NVector& datay)
            :dx(datax),dy(datay),coeff(datay),dd(datax.size(),datax.size())
{
    int n=dx.size();
    for(int i=0;i<n;i++)
        dd[i][0]=dy[i];
    for (int j=1;j<n;j++)
        for(int i=0;i<n-j;i++)
            dd[i][j]=(dd[i+1][j-1]-dd[i][j-1])/(dx[i+j]-dx[i]);
    coeff=dd[0];
}

double NewtonInterpolation::operator ()
        (double x)
{
    int n=dx.size();
    double s=coeff[n-1];
    for(int i=n-2;i>=0;i--)
        s=s*(x-dx[i])+coeff[i];
    return s;
}
