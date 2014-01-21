#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>

#include "nvector.h"

namespace numerica
{
    namespace tools
    {

        using tools::NVector;
        using std::vector;
        using std::valarray;
        using std::ostream;
        using std::iostream;
        using std::out_of_range;

        class Matrix
        {
        public:
            Matrix(){}
            Matrix(size_t nRows,size_t nColumns);                               //Constructors
            Matrix(const Matrix& M);
            Matrix& operator=(const Matrix& M);
            Matrix(const double data[],size_t nRows,size_t nColumns);
            Matrix(const vector<double>& data,size_t nRows,size_t nColumns);

            size_t nOfRows() const {return nRows;}
            size_t size() const {return nRows;}
            size_t nOfColumns() const {return nColumns;}


            bool operator==(const Matrix& M);
            bool operator!=(const Matrix& M) {return !(*this==M);}
            NVector& operator[](size_t i){CheckRow(i);return mat[i];}
            NVector operator[](size_t i) const {CheckRow(i);return mat[i];}
            NVector operator*(const NVector& x);
            void operator+=(const Matrix& M);


        private:
            void CheckRow(size_t i) const {if (i>=nRows) throw out_of_range("Matrix row out of range");}

            valarray<NVector> mat;
            size_t nRows,nColumns;
        };

        Matrix operator+(const Matrix& A, const Matrix& B);
        Matrix operator*(const Matrix& A, const Matrix& B);
        Matrix operator*(const Matrix& A, double x);
        Matrix operator*(double x,const Matrix& A);
        Matrix operator/(const Matrix& A, double x);
        ostream& operator<<(ostream& out,const Matrix& A);

        Matrix Transpose(const Matrix& m);
        Matrix IdentityMatrix(size_t n);
    }
}


#endif // MATRIX_H
