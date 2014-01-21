#ifndef SECANT_H
#define SECANT_H


namespace numerica
{
    namespace roots
    {
        class Secant
        {
        public:
            Secant(const double p0,const double p1,double TOL=1e-8, int nEvals=20)
                :p0(p0),p1(p1),TOL(TOL),nEvals(nEvals){}
            template<typename Function>
            double DoIt(Function& f);

        private:
            double p0,p1,TOL,nEvals;

        };
    }
}



//--------- Definitions ------------

#include <stdexcept>
#include <math.h>


namespace numerica
{
    namespace roots
    {

        template<typename Function>
        double Secant::DoIt(Function& f)
        {
            double p,df,fp0,fp1;
            fp0=f(p0);
            for(int i=0;i<nEvals;i++)
            {
                fp1=f(p1);
                if(fp0==0) return p0;
                df=fp1-fp0;
                if(df==0)
                    throw std::runtime_error("Secant fails:f(x1)-f(x2)==0");
                p=p1-fp1*(p1-p0)/df;
                if(fabs(p1-p)<TOL) return p;
                p0=p1;
                p1=p;
                fp0=fp1;
            }
            throw std::runtime_error("Secant fails to obtain root");
        }
    }
}




#endif // SECANT_H
