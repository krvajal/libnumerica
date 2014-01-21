 #include "plotter2d.h"

using namespace std;
using namespace numerica::tools;
using namespace numerica::plot;

#include <limits>
#include <cstring>

//----------------------------------------  Constructor ---------------------------------------------------------


Plotter2D::Plotter2D(string filename)
    : xLabel("x"),
      yLabel("y"),
      plotLabel("plot"),
      ps(*new PSWriter(filename+".ps")),
      xmin(numeric_limits<double>::max()),
      ymin(numeric_limits<double>::max()),
      xmax(-numeric_limits<double>::max()),
      ymax(-numeric_limits<double>::max()),
      lenYTicks(1)
{

}


//----------------------------------------- Public methods --------------------------------------------------------


void plot(NFunction f, double x1, double x2)
{
    static char i='A';
    Plotter2D p(string("plot")+i++);
    p.AddFunction(f,x1,x2);
    p.DoIt();
}


void Plotter2D::AddFunction(NVector x, NVector y, RGBColor col, string dashed)
{
    
    UpdateMinMax(x.min(),x.max(),y.min(),y.max());
    
    funs.push_back(FunctionData(x,y,col,dashed));
}

void Plotter2D::AddFunction(NFunction f,double x1,double x2,RGBColor col,string dashed,int nPoints)
{
    NVector x(nPoints),y(nPoints);

    double dx=(x2-x1)/(nPoints-1);
    
    for(int i=0;i<nPoints;i++)
    {
        x[i]=x1+dx*i;
        y[i]=f(x[i]);
    }

    UpdateMinMax(x.min(),x.max(),y.min(),y.max());
    funs.push_back(FunctionData(x,y,col,dashed));
}

void Plotter2D::AddPoint(double x, double y,int symbol,double size)
{
    UpdateMinMax(x,x,y,y);
    points.push_back(PointData(x,y,symbol,size));
}

void Plotter2D::AddPoints(const NVector &xs, const NVector &ys, int symbol, double size)
{
    UpdateMinMax(xs.min(),xs.max(),ys.min(),ys.max());
    for(size_t i=0;i<xs.size();i++)
        points.push_back(PointData(xs[i],ys[i],symbol,size));
}

void Plotter2D::AddHorLine(double y0,double x1,double x2,RGBColor col,string dashed,int nPoints)
{
    NVector x(nPoints),y(nPoints);
    double dx=(x2-x1)/(nPoints-1);
    for(int i=0;i<nPoints;i++)
    {
        x[i]=x1+dx*i;
        y[i]=y0;
    }
    UpdateMinMax(x.min(),x.max(),y.min(),y.max());
    funs.push_back(FunctionData(x,y,col,dashed));
}

void Plotter2D::AddVerLine(double x0,double y1,double y2,RGBColor col,string dashed,int nPoints)
{
    NVector x(nPoints),y(nPoints);
    double dy=(y2-y1)/(nPoints-1);
    for(int i=0;i<nPoints;i++)
    {
        x[i]=x0;
        y[i]=y1+dy*i;
    }
    UpdateMinMax(x.min(),x.max(),y.min(),y.max());
    funs.push_back(FunctionData(x,y,col,dashed));
}

void Plotter2D::DoIt()
{
    DrawFrame();
    DrawTicks();

    for(size_t i=0;i<points.size();i++)
        ps.DrawSymbol(TransformX(points[i].x),TransformY(points[i].y),
                      points[i].symbol,points[i].size);
    DrawLabels();
    DrawFunctions();
    delete &ps;
}



//----------------------------------------- Private methods ---------------------------------------------------------------


void Plotter2D::UpdateMinMax(double _xmin, double _xmax, double _ymin, double _ymax)
{
    xmin=std::min(xmin,_xmin);
    xmax=std::max(xmax,_xmax);
    ymin=std::min(ymin,_ymin);
    ymax=std::max(ymax,_ymax);
}

void Plotter2D::DrawLabels()
{
    static double fontSize=18;
    if (xLabel=="" && yLabel=="" && plotLabel=="")
        return;

    ps.SetFont("Arial",fontSize);
    ps.SetTextJustification(tjCentered);
    if (xLabel!="")
        ps.DrawText(0.5*gxSize+gx1,gy1-ymarg-1.3*fontSize-ticksfsize,xLabel);
    if (yLabel!="")
        ps.DrawText(gx1-xmarg-fontSize-0.5*lenYTicks*ticksfsize,0.5*gySize+gy1,yLabel,90);
    if (plotLabel!="")
        ps.DrawText(0.5*gxSize+gx1,gy1+gySize+ymarg+0.5*fontSize,plotLabel);

}


void Plotter2D::DrawFrame()
{
    static NVector dx={gx1-xmarg,gx1-xmarg,gx1+gxSize+xmarg,gx1+gxSize+xmarg};
    static NVector dy={gy1-ymarg,gy1+gySize+ymarg,gy1+gySize+ymarg,gy1-ymarg};
    ps.DrawConnectedLine(dx,dy,true);
    if (ymin*ymax<0)
    {
        ps.SetDashedLine();
        ps.DrawLine(gx1-xmarg,TransformY(0),gx1+gxSize+xmarg,TransformY(0));
        ps.SetSolidLine();
    }
}

void Plotter2D::DrawFunctions()
{
    double x1,y1,x2,y2;
    for(size_t i=0;i<funs.size();i++)
    {
        FunctionData& fd=funs[i];
        ps.SetDashedLine(fd.dashed);
        ps.SetColor(fd.col);
        for (size_t j=0;j<fd.xs.size()-1;j++)
        {
            x1=TransformX(fd.xs[j]);
            x2=TransformX(fd.xs[j+1]);
            y1=TransformY(fd.ys[j]);
            y2=TransformY(fd.ys[j+1]);
            ps.DrawLine(x1,y1,x2,y2);
        }
    }
}

struct DecimalPartition
{
    DecimalPartition(double x1,double x2):x1(x1),x2(x2)
    {
        double dx=x2-x1;
        n=floor(log10(fabs(dx)));
        int d1=floor(dx*pow(10,-n));
        mj_dx=pow(10,n);
        mn_dx=0.2*mj_dx;
        if (d1<3) {
            n--;
            d1=floor(dx*pow(10,-n));
        }
        if(d1>6 && d1<=10){
            mj_dx=2*pow(10,n);
            mn_dx=0.25*mj_dx;
        }
        else if(d1>10)
        {
            mj_dx=5*pow(10,n);
            mn_dx=0.2*mj_dx;
        }

    }
    void DoIt()
    {
        double z;
        for(double x=x1;x<x2+mj_dx;x+=mj_dx){
            z=floor(x*pow(10,-n))*pow(10,n);
            if (z>=x1-0.1*mj_dx && z<=x2+0.1*mj_dx)
                major_ticks.push_back(z);
        }
        for(double x=major_ticks[0]-mj_dx;x<x2+0.1*mn_dx;x+=mn_dx)
            if (x>=x1-0.1*mn_dx && x<=x2+0.1*mn_dx)
                minor_ticks.push_back(x);
    }

    vector<double> major_ticks;
    vector<double> minor_ticks;
private:
    double x1,x2,mj_dx,mn_dx;
    int n;
};

void Plotter2D::DrawTicks()
{
    if (xmin==xmax)
    {
        xmin-=1;
        xmax+=1;
    }
    if (ymin==ymax)
    {
        ymin-=1;
        ymax+=1;
    }
    DecimalPartition px(xmin,xmax); px.DoIt();
    DecimalPartition py(ymin,ymax); py.DoIt();
    DrawXTicks(px.major_ticks,8);
    DrawXTicks(px.minor_ticks,4,false);
    DrawYTicks(py.major_ticks,8);
    DrawYTicks(py.minor_ticks,4,false);
}

void Plotter2D::DrawXTicks(vector<double> ticks, double size,bool label)
{
    char str[20];
    double x;
    if (label)
    {
        ps.SetFont("Arial",ticksfsize);
        ps.SetTextJustification(tjCentered);
    }
    for(size_t i=0;i<ticks.size();i++)
    {
        x=TransformX(ticks[i]);
        ps.DrawLine(x,gy1-ymarg,x,gy1-ymarg+size);
        ps.DrawLine(x,gy1+ymarg+gySize-size,x,gy1+ymarg+gySize);
        if (label)
        {
            sprintf(str,"%g",ticks[i]);
            ps.DrawText(x,gy1-ymarg-ticksfsize,str);
        }
    }

}

void Plotter2D::DrawYTicks(vector<double> ticks, double size,bool label)
{
    char str[20];
    double y;
    if (label)
        ps.SetTextJustification(tjRight);
    for(size_t i=0;i<ticks.size();i++)
    {
        y=TransformY(ticks[i]);
        ps.DrawLine(gx1-xmarg,y,gx1-xmarg+size,y);
        ps.DrawLine(gx1+gxSize+xmarg-size,y,gx1+gxSize+xmarg,y);
        if (label)
        {
            sprintf(str,"%g",ticks[i]);
            ps.DrawText(gx1-xmarg-0.3*ticksfsize,y-0.3*ticksfsize,str);
            if (strlen(str)>lenYTicks)
                lenYTicks=strlen(str);
        }
    }
}


inline double Plotter2D::TransformX(double x)
{
    double m=gxSize/(xmax-xmin);
    return gx1+m*(x-xmin);
}

inline double Plotter2D::TransformY(double y)
{
    return gy1+gySize*(y-ymin)/(ymax-ymin);
}
