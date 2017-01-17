#ifndef NUMERICA_TOOLS_UTILS_H
#define  NUMERICA_TOOLS_UTILS_H
#include "nvector.h"


namespace numerica{

    namespace tools{
        /**
         * @brief generate a equally spaced set of points in the interval [start,end]
         * If the number of points is equal to zero an InvalidArgumentException is thrown
         * If the number of points is equal to one and the start and ending point are different
         * an InvalidArgumentException is thrown
         * @param start starting point of the interval
         * @param end  ending point for the interval
         * @param points number of points in the returned vector
         * @return a vector with a number of items equal to points
         * @throws InvalidArgumentException
         */
        NVector linspace(double start, double end, uint points);
    }
}




#endif //NUMERICA_TOOLS_UTILS_H