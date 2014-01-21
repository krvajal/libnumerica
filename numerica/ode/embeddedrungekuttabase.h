#ifndef EMBEDDEDRUNGEKUTTABASE_H
#define EMBEDDEDRUNGEKUTTABASE_H

#include "../tools/mathfunctions.h"
#include "../interpolation/interpolation.h"

namespace numerica
{
    namespace ode
    {
        using interpolation::OdeInterpolation;
        using std::vector;
        using tools::NVector;
        using tools::Matrix;

        class EmbeddedRungeKuttaBase
        {
        public:
            template<typename Function>
            void DoIt(Function& f);

            double t1,t2;
            vector<double> t;
            vector<NVector> w,wp;
            vector<OdeInterpolation> solution;


        protected:
            EmbeddedRungeKuttaBase
                    (double t1, double t2,const NVector& y0,
                     double Tol,double hmax,double hmin,int nStages,int order,int NMax=1000);


            int nStages,order,NMax;
            Matrix a;
            NVector c,b,d;

            double Tol,hmax,hmin;
            NVector y0;

        private:
            void DoInterpolations();
        };
    }
}


//Definitions

namespace numerica
{
    namespace ode
    {
        using tools::Norm2;
        template<class Function>
        void EmbeddedRungeKuttaBase::DoIt(Function& f)
        {
            double t=t1,h=hmax,R,delta;
            NVector w=y0;
            Matrix k(nStages,y0.size());
            for(int n=0;n<NMax;n++)
            {
                NVector error(y0.size()),wnew(y0.size());
                for(int i=0;i<nStages;i++)
                {
                    NVector sum(y0.size());
                    for(int j=0;j<i;j++)
                        sum+=a[i][j]*k[j];
                    k[i]=h*f(t+c[i]*h,w+sum);
                    error+=d[i]*k[i];
                    wnew+=b[i]*k[i];
                }

                R=Norm2(error)/h;
                if (R<=Tol)
                {
                    this->t.push_back(t); //tilovel
                    this->w.push_back(w);
                    this->wp.push_back(k[0]/h);
                    t+=h;
                    w+=wnew;
                }
                delta=0.84*pow(Tol/R,1./order);
                if (delta<.1) h*=0.1;
                else if (delta>=4) h*=4;
                else h*=delta;
                if (h>hmax) h=hmax;
                if (t>=t2)
                {
                    this->t.push_back(t); //tilovel
                    this->w.push_back(w);
                    this->wp.push_back(f(t,w));
                    DoInterpolations();
                    return;
                }
                else if (t+h>t2) h=t2-t;
                else if (h<hmin)
                    throw std::runtime_error("ERK::DoIt minimum h exceeded");
            }
            throw std::runtime_error("ERK::DoIt iterations (NMax) limit exceeded");
        }
    }
}


#endif // EMBEDDEDRUNGEKUTTABASE_H
