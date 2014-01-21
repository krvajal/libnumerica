#include <numerica/interpolation/interpolation.h>

#include <numerica/tests/testinterpolation.h>

#include <numerica/plot/plotter2d.h>

using namespace numerica;
using namespace plot;
using namespace interpolation;
using namespace std;


void TestInterpolations()
{    
    TestInterpolationLagrange();
    TestInterpolationNewton();
    TestInterpolationHermite();
    TestInterpolationNCSpline();
}

void TestInterpolationLagrange()
{
    cout<<"Lagrange interpolation"<<endl;
    NVector x1={0,1,2,3,4,5,6,7,8,9,10}, y1=cos(x1);
    LagrangeInterpolation p(x1,y1);
    Plotter2D g("Lagrange");
    g.AddFunction(p,x1.min(),x1.max());
    g.AddPoints(x1,y1);
    g.DoIt();
}

void TestInterpolationNCSpline()
{
    cout<<"Natural cubic spline"<<endl;
    NVector x1={0,1,2,3,4,5,6,7,8,9,10}, y1=cos(x1);
    NaturalCubicSpline p(x1,y1);
    Plotter2D g("Spline");
    g.AddFunction(p,x1.min(),x1.max());
    g.AddPoints(x1,y1);
    g.DoIt();
}

void TestInterpolationNewton()
{
    cout<<"Newton interpolation"<<endl;
    NVector x1={0,1,2,3,4,5,6,7,8,9,10}, y1=cos(x1);
    NaturalCubicSpline p(x1,y1);
    Plotter2D g("Newton");
    g.AddFunction(p,x1.min(),x1.max());
    g.AddPoints(x1,y1);
    g.DoIt();
}

void TestInterpolationHermite()
{
    cout<<"Hermite interpolation"<<endl;
    NVector x1={0,1,2,3,4,5,6,7,8,9,10}, y1=cos(x1), y1d=-sin(x1);
    HermiteInterpolation p(x1,y1,y1d);
    Plotter2D g("Hermite");
    g.AddFunction(p,x1.min(),x1.max());
    g.AddPoints(x1,y1);
    g.DoIt();
}
