#ifndef NVECTOR_H
#define NVECTOR_H

#include <valarray>
#include <iostream>
namespace numerica
{
    namespace tools
    {
        using std::ostream;
        typedef std::valarray<double> NVector; // This can be upgraded!


        ostream& operator<<(ostream& out,const NVector& v);
        bool operator==(const NVector& a, const NVector& b);
        bool operator!=(const NVector& a, const NVector& b);
    }
}


#endif // NVECTOR_H
