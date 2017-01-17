#include "utils.hpp"
#include "exceptions/InvalidArgumentException.h"


namespace numerica {

    namespace tools {


        NVector linspace(double a, double b, uint points) {

            if (points == 0) throw except::InvalidArgumentException("linspace: number of points should be bigger than zero");
            if(points == 1 && (a != b)) throw except::InvalidArgumentException("linspace: number of points equal 1 but interval is bigger");
            NVector v(points);
            double dx = (b - a) / (points - 1);

            for (int i = 0; i < points; i++) {
                v[i] = a + dx * i;
            }
            return v;
        }
    }
}
