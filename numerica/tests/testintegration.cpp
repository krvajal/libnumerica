#include <numerica/tests/testintegration.h>

#include <numerica/integration/integration.h>

#include <iostream>
#include <iomanip>

using namespace std;
using namespace numerica::integration;

double fun(double x)
{
    return sin(x);
}

void TestIntegration()
{
    cout<<setprecision(16);
    cout<<"Integral of sin(x) from pi to 2pi= "<<Simpson(fun,M_PI,2*M_PI,50)<<endl;
    cout<<"Integral of sin(x) from pi to 2pi= "<<Trapezoidal(fun,M_PI,2*M_PI,50)<<endl;
    cout<<"Integral of sin(x) from pi to 2pi= "<<Romberg(fun,M_PI,2*M_PI,1e-15)<<endl;
}
