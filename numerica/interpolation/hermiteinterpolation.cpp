#include "hermiteinterpolation.h"
#include "tools/nmatrix.h"

using namespace numerica::interpolation;
using numerica::tools::Matrix;

HermiteInterpolation::HermiteInterpolation
        (const NVector& datax,const NVector& datay,const NVector& datayDer)
            :dx(datax),dy(datay),dyDer(datayDer),coeff(2*dx.size())
{
    int n=dx.size();
    NVector z(2*n);
    Matrix Q(2*n,2*n);
    for(int i=0;i<n;i++)
    {
        z[2*i]=dx[i];
        z[2*i+1]=dx[i];
        Q[2*i][0]=dy[i];
        Q[2*i+1][0]=dy[i];
        Q[2*i+1][1]=dyDer[i];
        if(i!=0)
            Q[2*i][1]=(Q[2*i][0]-Q[2*i-1][0])/(dx[i]-dx[i-1]);

    }

    for(int i=2;i<2*n;i++)
        for(int j=2;j<i+1;j++)
            Q[i][j]=(Q[i][j-1]-Q[i-1][j-1])/(z[i]-z[i-j]);
    for(int i=0;i<2*n;i++)
        coeff[i]=Q[i][i];


}
double HermiteInterpolation::operator ()(double x)
{
    int n=dx.size();
    double s=coeff[2*(n-1)+1]*(x-dx[n-1]);
    for(int i=n-1;i>=1;i--)
    {
        s=(s+coeff[2*i])*(x-dx[i-1]);
        s=(s+coeff[2*i-1])*(x-dx[i-1]);
    }
    return s+coeff[0];
}

