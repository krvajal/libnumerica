#ifndef GAUSSIANELIMINATION_H
#define GAUSSIANELIMINATION_H

#include "../tools/nmatrix.h"

namespace numerica
{
    namespace linearAlgebra
    {
        using tools::NVector;
        using tools::Matrix;

        NVector Solve(const Matrix& A,const NVector& b);
        double Determinant(const Matrix& A);
        Matrix Inverse(const Matrix& A);
        NVector BackwareSustitution(const Matrix& A,int column=0);


        template<class PivotingStrategy>
        class GaussianEliminator
        {
        public:
            GaussianEliminator(Matrix& A):A(A),nPermutations(0){}
            bool DoIt();

            int nPermutations;
        private:
            Matrix& A;

        };


        class PartialScaledStrategy
        {
        public:
            PartialScaledStrategy(Matrix& A);
            bool SelectPivote(int column);

            int nPermutations;
        private:
            Matrix &A;
            NVector s;
            bool emptyRow;
        };
    }
}


//Definitions

namespace numerica
{
    namespace linearAlgebra
    {
        template<class PivotingStrategy>
        bool GaussianEliminator<PivotingStrategy>::DoIt()
        {
            PivotingStrategy strategy(A);
            for(int i=0;i<A.size()-1;i++)
            {
                if (!strategy.SelectPivote(i)) return false;
                for (size_t j=i+1;j<A.size();j++)
                {
                    double m=A[j][i]/A[i][i];
                    A[j]-=m*A[i];
                }
            }
            nPermutations=strategy.nPermutations;
            return (A[A.size()-1][A.size()-1]!=0);
        }
    }
}


#endif // GAUSSIANELIMINATION_H
