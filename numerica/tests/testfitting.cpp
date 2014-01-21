#include <numerica/tests/testfitting.h>
#include <numerica/fitting/linearfit.h>
#include <numerica/plot/plotter2d.h>

using numerica::plot::Plotter2D;
using namespace numerica::fitting;
using namespace numerica::tools;
using namespace std;

double f1(double x){return 1.;}
double f2(double x){return x;}
double f3(double x){return x*x;}
double f4(double x){return pow(x,4);}

void TestFitting()
{
    NVector x1={1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            y1={1.3, 3.5, 4.2, 5.0, 7.0, 8.8, 10.1, 12.5, 13.0, 15.6};

    vector< double(*)(double) > df;
    df.push_back(f1);
    df.push_back(f2);
    //df.push_back(f3);
    //df.push_back(f4);

    LinearFit<double (*)(double)> fit(x1,y1,df);

    Plotter2D p("fitting");
    p.AddPoints(x1,y1);
    p.AddFunction(fit,x1.min(),x1.max());
    p.DoIt();
}
