#ifndef TRIDIAGONAL_H
#define TRIDIAGONAL_H

#include "../tools/nvector.h"

namespace numerica
{
    namespace linearAlgebra
    {
        using tools::NVector;

        NVector SolveTridiagonal
                (const NVector& diag,const NVector& diag_low,const NVector& diag_upper, const NVector& b);
    }
}

#endif // TRIDIAGONAL_H
