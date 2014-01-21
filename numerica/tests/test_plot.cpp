 #include <numerica/tests/test_plot.h>
#include <numerica/plot/plotter2d.h>
#include <numerica/tools/tools.h>
#include <cmath>

using namespace numerica;
using namespace tools;
using namespace plot;

void TestPlot()
{
    //numerica::plot::plot(sin,1,1.15);
    Plotter2D p("testing");
    // for(double x=0;x<10;x+=.1)
    //     p.AddPoint(x,sin(x));
    p.xLabel    = "abcisa x";
    p.yLabel    = "y = sen(x)";
    p.plotLabel = "grafica del sen(x)";



    // p.AddFunction(cos,0,10);
    // p.AddFunction(atan,0,10,RGBColor(0,1,0),"2 6");

    
    const int N=1000;
    for(int i=0 ; i < 1000; i++)
    {
        double t = 2 * M_PI *i / N;
        double xx=(cos(2*t));
        double yy=(sin(6*t) );
        p.AddPoint(xx,yy);
    }

    p.DoIt();
}
