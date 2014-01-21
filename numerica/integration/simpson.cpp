#include "simpson.h"
#include<stdexcept>

using std::runtime_error;
using namespace numerica;


double integration::Simpson(const NVector &y, double a, double b)
{
    size_t n=y.size()-1;
    if (n & 1 || n==0) throw
            std::runtime_error("integration::Simpson integration with an odd n");
    double h=(b-a)/n;
    double I0=y[0]+y[n], I1=0,I2=0;
    for(size_t i=1;i<n;i++)
        if (i%2==0) I2+=y[i];
        else I1+=y[i];

    return h*(I0+2*I2+4*I1)/3;
}
