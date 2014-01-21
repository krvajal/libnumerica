#include "odeinterpolation.h"
#include<stdexcept>

using namespace numerica::interpolation;

OdeInterpolation::OdeInterpolation
        (const NVector& datax,const NVector& datay,const NVector& datayDer)
        :dx(datax),dy(datay),dyDer(datayDer)
{
    for(int i=0;i<datax.size()-1;i++)
    {
        double ddx[]={datax[i],datax[i+1]};
        double ddy[]={datay[i],datay[i+1]};
        double dyD[]={datayDer[i],datayDer[i+1]};
        NVector dx(ddx,2),dy(ddy,2),yD(dyD,2);
        hs.push_back(HermiteInterpolation(dx,dy,yD));
    }
}

double OdeInterpolation::operator ()(double x)
{
    if (x<dx.min() || x>dx.max())
        throw std::invalid_argument("OdeInterp:: x out of range");
    for(int i=0;i<dx.size()-1;i++)
        if(x>=dx[i] && x<=dx[i+1])
            return hs[i](x);
}
