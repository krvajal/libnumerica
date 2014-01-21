#include "lagrangeinterpolation.h"
#include "tools/nmatrix.h"

using namespace numerica::interpolation;
using numerica::tools::Matrix;

LagrangeInterpolation::LagrangeInterpolation
        (const NVector& datax,const NVector& datay):dx(datax),dy(datay)
{}

double LagrangeInterpolation::operator()
        (double x)
{
    int n=dx.size();
    Matrix Q(n,n);
    Q[0][0]=dy[0];
    for( int i=1;i<n;i++)
    {
        Q[i][0]=dy[i];
        for( int j=1;j<=i;j++)
            Q[i][j]=((x-dx[i-j])*Q[i][j-1]-(x-dx[i])*Q[i-1][j-1])/(dx[i]-dx[i-j]);
    }
    return Q[n-1][n-1];
}


