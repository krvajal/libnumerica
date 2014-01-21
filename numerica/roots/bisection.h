#ifndef BISECTION_H
#define BISECTION_H


namespace numerica
{
    namespace roots
    {

        class Bisection
        {
        public:
            Bisection(const double x_low,const double x_upper, double TOL=1e-5,int nEvals=40)
                :x_low(x_low),x_upper(x_upper),TOL(TOL),nEvals(nEvals){}
            template<typename Function>
            double DoIt(Function& f);

        protected:
            double x_low,x_upper,TOL;
            int nEvals;

        };


    }
}


//--- Definitions -----//

#include<cmath>
#include<stdexcept>

namespace numerica
{
    namespace roots
    {
        template<typename Function>
        double Bisection::DoIt(Function& f)
        {
            double a=x_low,b=x_upper;
            double x,y,y1=f(a), y2=f(b);
            if (y1==0) return a;
            if (y2==0) return b;
            for(int i=0;i<nEvals;i++)
            {
                x=a+0.5*(b-a);
                if (fabs(x-a)<TOL) return x;
                y=f(x);
                if (y==0) return x;
                if (y*y1>0){
                    a=x;
                    y1=y;
                }
                else{
                    b=x;
                    y2=y;
                }
            }
            throw std::runtime_error("FindRoot1D::Bisection fails to obtain TOL");
        }
    }
}



#endif // BISECTION_H
