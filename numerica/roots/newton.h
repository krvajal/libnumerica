#ifndef NEWTON_H
#define NEWTON_H


namespace numerica
{
    namespace roots
    {
        class Newton
        {
        public:
            Newton(const double p0,double TOL=1e-8, int nEvals=20)
                :p0(p0),TOL(TOL),nEvals(nEvals){}
            template<typename Function,typename FDerivate>
            double DoIt(Function& f,FDerivate& fder);

        private:
            double p0,TOL,nEvals;

        };
    }
}


//-------Definitions---------//

#include<stdexcept>
#include<cmath>

namespace numerica
{
    namespace roots
    {
        template<typename Function,typename FDerivate>
        double Newton::DoIt(Function& f,FDerivate& fder)
        {
            double p,der,fp0;
            for(int i=0;i<nEvals;i++)
            {
                fp0=f(p0);
                if(fp0==0) return p0;
                der=fder(p0);
                if(der==0)
                    throw std::runtime_error("newton fails:Fderivate=0");
                p=p0-fp0/der;
                if(fabs(p0-p)<TOL) return p;
                p0=p;
            }
            throw std::runtime_error("newton fails to obtain root");
        }
    }
}



#endif // NEWTON_H
