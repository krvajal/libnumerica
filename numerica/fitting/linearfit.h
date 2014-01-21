#ifndef LINEARFIT_H
#define LINEARFIT_H
#include <vector>
#include <numerica/tools/nvector.h>
#include <numerica/tools/nmatrix.h>
#include <numerica/linearalgebra/linearalgebra.h>

namespace numerica
{
    namespace fitting
    {
        using numerica::tools::NVector;
        using numerica::tools::Matrix;

        template<typename Function>

        class LinearFit
        {
        public:
            
            LinearFit(const NVector& datax,const NVector& datay,std::vector<Function> fs);
            double operator()(double x);

            NVector dx,dy;
        private:
            NVector coeff;
            std::vector<Function> fs;
        };
    }
}

//implementation

namespace numerica
{
    namespace fitting
    {
        template<typename Function>
        LinearFit<Function>::LinearFit(const NVector& datax,const NVector& datay,std::vector<Function> fs)
            : coeff(datax.size()),
              dx(datax),
              dy(datay),
              fs(fs)
        {
            int n=fs.size(),m=dx.size();
            Matrix G(n,m);
            for(int i=0;i<n;i++)
                for(int j=0;j<m;j++)
                    G[i][j]=fs[i](dx[j]);
            Matrix GGT=G*tools::Transpose(G);
            coeff=linearAlgebra::Solve(GGT,G*dy);
        }

        template<typename Function>
        double LinearFit<Function>::operator()(double x)
        {
            double suma=0;
            for(int i=0;i<fs.size();i++)
                suma+=fs[i](x)*coeff[i];
            return suma;
        }
    }

}



#endif // LINEARFIT_H
