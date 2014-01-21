#ifndef MULLER_H
#define MULLER_H

#include<complex>

namespace numerica
{
    namespace roots
    {
        using std::complex;
        class Muller
        {
        public:
            Muller(const complex<double> x0,const complex<double> x1,const complex<double> x2,double TOL,int nEvals)
                :x0(x0),x1(x1),x2(x2),TOL(TOL),nEvals(nEvals){}
            template<typename Function>
            complex<double> DoIt(Function& f);
        private:
            complex<double> x0,x1,x2;
            double TOL,nEvals;
        };
    }
}


//-------Definitions----------//

#include<stdexcept>

namespace numerica
{
    namespace roots
    {
        template<typename Function>
        complex<double> Muller::DoIt(Function& f)
        {
            complex<double> b,D,E,h,p;
            complex<double> h1=x1-x0;
            complex<double> h2=x2-x1;
            complex<double> d1=(f(x1)-f(x0))/h1;
            complex<double> d2=(f(x2)-f(x1))/h2;
            complex<double> d=(d2-d1)/(h1+h2);

            for(int i=3;i<=nEvals;i++)
            {
                b=d2+h2*d;
                D=-sqrt(b*b-4.0*f(x2)*d);
                if(abs(b-D)<abs(b+D))
                    E=b+d;
                else E=b-D;
                h=-2.0*f(x2)/E;
                p=x2+h;
                if(abs(h)<TOL*abs(p))
                    return p;
                x0=x1;
                x1=x2;
                x2=p;
                h1=x1-x0;
                h2=x2-x1;
                d1=(f(x1)-f(x0))/h1;
                d2=(f(x2)-f(x1))/h2;
                d=(d2-d1)/(h1+h2);

            }
            throw std::runtime_error("numerica::roots::muller fails to obtain root");

        }
    }
}


#endif // MULLER_H
