#include "gaussianelimination.h"
#include<stdexcept>

using namespace numerica;
using namespace tools;
using namespace linearAlgebra;
using namespace std;

namespace numerica
{
    namespace linearAlgebra
    {
        void CheckSquareMatrix(const Matrix &A)
        {
            if (A.size()==0)
                throw invalid_argument("Gauss with empty matrix");
            if (A.size()!=A[0].size())
                throw invalid_argument("Gauss solver with non square matrix");
        }
    }
}


NVector linearAlgebra::Solve(const Matrix &A,const NVector& b)
{
    CheckSquareMatrix(A);
    if (A.size()!=b.size())
        throw invalid_argument("Gaussia::Solve with incompatible b");

    Matrix ampA(A.size(),A.size()+1);
    for(size_t i=0;i<A.size();i++)
    {
        for(size_t j=0;j<A.size();j++)
            ampA[i][j]=A[i][j];
        ampA[i][A.size()]=b[i];
    }
    GaussianEliminator<PartialScaledStrategy> elim(ampA);
    elim.DoIt();
    return BackwareSustitution(ampA);
}

double linearAlgebra::Determinant(const Matrix& A)
{
    CheckSquareMatrix(A);
    Matrix tmpA=A;
    GaussianEliminator<PartialScaledStrategy> elim(tmpA);
    if (!elim.DoIt()) return 0;
    double det=1;
    for(size_t i=0;i<tmpA.size();i++)
        det*=tmpA[i][i];
    if (elim.nPermutations & 1) det=-det;
    return det;
}

Matrix linearAlgebra::Inverse(const Matrix& A)
{
    CheckSquareMatrix(A);
    Matrix ampA(A.size(),2*A.size());
    for(size_t i=0;i<A.size();i++)
    {
        for(int j=0;j<A.size();j++)
            ampA[i][j]=A[i][j];
        ampA[i][A.size()+i]=1;
    }
    GaussianEliminator<PartialScaledStrategy> elim(ampA);
    elim.DoIt();
    Matrix inv(A.size(),A.size());
    for(size_t i=0;i<A.size();i++)
        inv[i]=BackwareSustitution(ampA,i);
    return inv;
}

NVector linearAlgebra::BackwareSustitution(const Matrix &A, int column)
{
    if (A.size()==0)
        throw invalid_argument("Backware sustitution with empty matrix");
    int pos=A.size()+column;
    if (pos>=A[0].size())
        throw invalid_argument("Backware sustitution with invalid position");
    for(size_t i=0;i<A.size();i++)
        if (A[i][i]==0)
            throw runtime_error("Backware sustitution with singular matrix");

    NVector x(A.size());
    for(int i=A.size()-1;i>=0;i--)
    {
        x[i]=A[i][pos];
        for(size_t j=i+1;j<A.size();j++)
            x[i]-=A[i][j]*x[j];
        x[i]/=A[i][i];
    }
    return x;
}



//------------------------------ class PartialScaledStrategy ---------------------


PartialScaledStrategy::PartialScaledStrategy(Matrix &A):A(A)
{
    s.resize(A.size());
    emptyRow=false;
    for(int i=0;i<A.size();i++)
    {
        s[i]=(abs(A[i])).max();
        if (s[i]==0) {emptyRow=true;break;}
    }
    nPermutations=0;
}

bool PartialScaledStrategy::SelectPivote(int column)
{
    if (emptyRow) return false;
    int p=column;
    double maxi=fabs(A[column][column])/s[column];
    for(size_t j=column+1;j<A.size();j++)
        if (fabs(A[j][column])>maxi*s[j]){
            p=j;
            maxi=fabs(A[j][column])/s[j];
        }
    if (maxi==0.) return false;
    if (p!=column) {swap(A[column],A[p]); nPermutations++;}
    return true;
}
