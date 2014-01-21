#include "nmatrix.h"
using namespace std;
using namespace numerica;
using namespace tools;


Matrix::Matrix(size_t nRows,size_t nColumns):nRows(nRows),nColumns(nColumns)
{
    mat.resize(nRows,NVector(nColumns));
}

Matrix::Matrix(const Matrix& M):nRows(M.nRows),nColumns(M.nColumns)
{
    mat.resize(nRows,NVector(nColumns));
    for(size_t i=0;i<nRows;i++)
        mat[i]=M[i];
}
Matrix& Matrix::operator=(const Matrix& M)
{
    mat.resize(M.nOfRows(),NVector(M.nOfColumns()));
    nRows=M.nOfRows();
    nColumns=M.nOfColumns();
    for(size_t i=0;i<nRows;i++)
        mat[i]=M[i];
    return *this;
}

Matrix::Matrix(const double data[],size_t nRows,size_t nColumns):nRows(nRows),nColumns(nColumns)
{
    mat.resize(nRows,NVector(nColumns));
    for(size_t i=0;i<nRows;i++)
        copy(&data[i*nColumns],&data[(i+1)*nColumns],&mat[i][0]);
}

Matrix::Matrix(const vector<double>& data,size_t nRows,size_t nColumns):nRows(nRows),nColumns(nColumns)
{
    mat.resize(nRows,NVector(nColumns));
    for(size_t i=0;i<nRows;i++)
        for(size_t j=0;j<nColumns;j++)
            mat[i][j]=data[i*nColumns+j];
}


bool Matrix::operator==(const Matrix& M)
{
    if (nOfRows()!=M.nOfRows() || nOfColumns()!=M.nOfColumns())
        return false;
    for(size_t i=0;i<nOfRows();i++)
        if(!(mat[i]==M[i])) return false;
    return true;
}

NVector Matrix::operator*(const NVector& b)
{
    if(nOfColumns()!=b.size())
        throw invalid_argument("Matrix*NVector invalid NVector size.");
    NVector c(nOfRows());
    for(size_t i=0;i<nOfRows();i++)
        for(size_t j=0;j<nOfColumns();j++)
            c[i]+=mat[i][j]*b[j];
    return c;
}

void Matrix::operator+=(const Matrix& M)
{
    if (nOfRows()!=M.nOfRows() || nOfColumns()!=M.nOfColumns())
        throw invalid_argument("Matrix+=Matrix incompatible size.");
    for(size_t i=0;i<nOfRows();i++)
        mat[i]+=M[i];
}

ostream& tools::operator<<(ostream& out,const Matrix& A)
{
    for(size_t i=0;i<A.nOfRows();i++)
        out<<A[i];
    return out;
}
Matrix tools::operator+(const Matrix& A, const Matrix& B)
{
    Matrix sum=A;
    sum+=B;
    return sum;
}

Matrix tools::operator*(const Matrix& A, const Matrix& B)
{
    if (A.nOfColumns()!=B.nOfRows())
        throw invalid_argument("Matrix*Matrix incompatible size.");
    Matrix prod(A.nOfRows(),B.nOfColumns());
    for(size_t i=0;i<A.nOfRows();i++)
        for(size_t j=0;j<B.nOfColumns();j++)
            for(size_t k=0;k<A.nOfColumns();k++)
                prod[i][j]+=A[i][k]*B[k][j];
    return prod;
}

Matrix tools::operator*(const Matrix& A, double x)
{
    Matrix res=A;
    for(size_t i=0;i<A.nOfRows();i++)
        res[i]*=x;
    return res;
}
Matrix tools::operator*(double x,const Matrix& A)
{
    return A*x;
}
Matrix tools::operator/(const Matrix& A, double x)
{
    return A*(1./x);
}

Matrix tools::Transpose(const Matrix& m)
{
    Matrix trans(m.nOfColumns(),m.nOfRows());
    for(size_t i=0;i<m.nOfRows();i++)
        for(size_t j=0;j<m.nOfColumns();j++)
            trans[j][i]=m[i][j];
    return trans;
}

Matrix tools::IdentityMatrix(size_t n)
{
    Matrix id(n,n);
    for (size_t i=0;i<n;i++)
        id[i][i]=1;
    return id;
}
