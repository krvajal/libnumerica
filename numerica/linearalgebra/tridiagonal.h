#ifndef TRIDIAGONAL_H
#define TRIDIAGONAL_H

#include "../tools/nvector.h"

namespace numerica
{
    namespace la
    {
        using tools::NVector;
        /**
         * This function solves the problem Ax = y
         * for a given matrix square matrix A of size NxN in tridiagonal form
         *
         * @param diag the main diagonal of the matrix, of size N
         * @param diag_low the elements of the diagonal below the main diagonal, of size N-1
         * @param diag_upper the elements of the diagonal above the main diagonal, of size N-1
         * @param y the vector y to solve the problem, of size N
         * @return the vector x that is solution to the problem
         */
        NVector SolveTridiagonal
                (const NVector& diag,const NVector& diag_low,const NVector& diag_upper, const NVector& y);
    }
}

#endif // TRIDIAGONAL_H
