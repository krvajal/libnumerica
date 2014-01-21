#include"tridiagonal.h"

using namespace numerica;
using tools::NVector;

NVector linearAlgebra::SolveTridiagonal
        (const NVector& a,const NVector& b,const NVector& c, const NVector& d)
{
    int n=a.size();
    NVector p(n),q(n),r(n),x(n);
    p[0]=c[0]/a[0];
    q[0]=d[0]/a[0];
    for(int i=1;i<n;i++)
    {
        r[i]=a[i]-b[i]*p[i-1];
        p[i]=c[i]/r[i];
        q[i]=(d[i]-b[i]*q[i-1])/r[i];
    }
    x[n-1]=q[n-1];
    for (int i=n-2;i>=0;i--)
        x[i]=q[i]-p[i]*x[i+1];
    return x;
}
