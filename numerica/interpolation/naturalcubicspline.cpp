#include "naturalcubicspline.h"
#include "linearalgebra/tridiagonal.h"
#include <stdexcept>

using namespace numerica::interpolation;
using namespace numerica::linearAlgebra;


NaturalCubicSpline::NaturalCubicSpline(const NVector& datax,const NVector& datay)
    :dx(datax),dy(datay),A(dy),B(dx.size()),C(dx.size()),D(dx.size())
{
    int n=dx.size();
    NVector a(n),b(n),c(n),d(n),h(n-1);

    for(int i=0;i<n-1;i++)
        h[i]=dx[i+1]-dx[i];

    for(int j=1;j<n-1;j++)
    {
        a[j]=2.*(h[j-1]+h[j]);
        b[j]=h[j-1];
        c[j]=h[j];
        d[j]=3.*(dy[j+1]-dy[j])/h[j]-3.*(dy[j]-dy[j-1])/h[j-1];
    }
    a[0]=a[n-1]=1;

    C=SolveTridiagonal(a,b,c,d);

    for(int j=0;j<n-1;j++)
    {
        B[j]=(A[j+1]-A[j])/h[j] - h[j]*(2.*C[j]+C[j+1])/3.;
        D[j]=(C[j+1]-C[j])/(3.*h[j]);
    }
}

double NaturalCubicSpline::operator ()(double x)
{
    if (x<dx.min() || x>dx.max())
        throw std::invalid_argument("NCSpline:: x out of range");
    for(int i=0;i<dx.size()-1;i++)
        if(x>=dx[i] && x<=dx[i+1])
        {
            double t=x-dx[i];
            return A[i]+(B[i]+(C[i]+D[i]*t)*t)*t;
        }
}
