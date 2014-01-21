#ifndef BRENT_H
#define BRENT_H

namespace numerica
{
    namespace roots
    {
        class Brent
        {
        public:
            Brent(const double x_low,const double x_upper, double TOL=1e-7,int nEvals=100)
                 :x_low(x_low),x_upper(x_upper),TOL(TOL),nEvals(nEvals){}

            template<typename Function>
            double DoIt(Function& f);
        private:
            double x_low,x_upper,TOL;
            int nEvals;

        };
    }
}


//--- Definitions -----//

#include<limits>
#include<stdexcept>
#include "../tools/mathfunctions.h"

namespace numerica
{
    namespace roots
    {
        using std::numeric_limits;
        using tools::Sign;

        template<class Function>
        double Brent::DoIt(Function& f)
        {
            double a=x_low;
            double b=x_upper;
            double c=x_upper;
            double d,e;
            double fa=f(a);
            double fb=f(b);
            double fc=fb;
            double p, q, r, s, t, m,delta;

            double eps=numeric_limits<double>::epsilon();

            if( fa*fb > 0 )
                throw std::invalid_argument("Brent: fa*fb>0");

            for(int i=0;i<nEvals;i++)
            {
                if(fb*fc>0)
                {
                    c = a;
                    d = b-a;
                    e = d;
                    fc = fa;
                }
                if( fabs(fc) < fabs(fb))
                {
                    a=b;
                    b=c;
                    c=a;
                    fa=fb;
                    fb=fc;
                    fc=fa;
                }
                delta = 2.0 * eps * fabs(b)+0.5*TOL;
                m = 0.5 * (c-b); 

                if((fabs(m)<=delta) || (f(b)==0.0) )
                    return b;
                if(fabs(e)<delta||fabs(fa)<fabs(fb))
                {
                    d=m;//bisection step
                    e=m;
                }
                else if( a==c )
                {
                    s=fb/fa;
                    p=(a-b)*s;
                    q=1.-s;

                }
                else
                {
                    r=fb/fc;
                    s=fb/fa;
                    t=fa/fc;
                    p=s*(t*(t-r)*(c-b)-(r-1)*(b-a));
                    q=(t-1.)*(r-1.)*(s-1.);
                }

                if(p>0) q=-q;

                p=fabs(p);
                double minim = std::min(1.5*(c-b)*q-fabs(delta*q),fabs(e*q));
                if(2.*p<minim)
                {
                    e=d;
                    d=p/q;
                }
                else
                {
                    d=m;
                    e=d;
                }
                a  = b;
                fa = fb;
                if(fabs(d)>delta)
                {
                    b+=d;
                }
                else
                { 
                    b += delta * Sign(m);
                }

                fb =f(b);
            }
        }
    }
}
#endif // BRENT_H
