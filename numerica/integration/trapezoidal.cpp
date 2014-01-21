#include "trapezoidal.h"
#include<stdexcept>

using std::runtime_error;
using namespace numerica;


double integration::Trapezoidal(const NVector &y, double a, double b)
{
    size_t n=y.size()-1;
    if (n<1) throw
            std::runtime_error("integration::Trapezoidal integration with n<1");
    double h=(b-a)/n,
           sum=0.5*(y[0]+y[n]);
    for(size_t i=1;i<n;i++)
        sum+=y[i];
    return h*sum;
}
