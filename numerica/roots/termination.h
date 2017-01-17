//
// Created by Miguel Angel Carvajal on 1/17/17.
//

#ifndef PROJECT_TERMINATION_H
#define PROJECT_TERMINATION_H

#include <cmath>

namespace numerica {

    namespace roots {


        template<typename T>
        struct eps_termination {
            T eps;

            eps_termination(T eps = 1e-5) : eps(eps) {}

            bool operator()(const T &a, const T &b) {
                return std::abs(a - b) < eps;
            }
        };
    }
}

#endif //PROJECT_TERMINATION_H
