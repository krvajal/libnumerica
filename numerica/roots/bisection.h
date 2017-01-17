#ifndef BISECTION_H
#define BISECTION_H

#include <functional>
#include <utility> //make_pair
#include <numerica/roots/termination.h>

namespace numerica {
    namespace roots {

        /**
         * @brief Locate a root using bisection algorithm
         * @param f An unary functor which is the function f(x) whose root is to be found
         * @param min the left bracket of the interval known to contain the root
         * @param max the right bracket of the interval known to contain the root:
         * this value should be bigger than min and also it must hold that f(min)* f(max) < 0 otherwise
         * the function will throw an InvalidArgumentException
         * @param tol a binary functor that specifies the termination conditions:
         * when tol(min,max) becomes true the function will return the current interval
         * @return a pair of values r that bracket the root so that
         * tol(r.first,r.second) < 0 || max_iter >= m where m is the initial value pased to max_iter
         *
         */
        template<class T, class F, class Tol>
        std::pair<T, T>
        bisec(F f, const T &min, const T &max, Tol tol = eps_termination<T>());


        /**
        * @brief Locate a root using bisection algorithm
        * @param f An unary functor which is the function f(x) whose root is to be found
        * @param min the left bracket of the interval known to contain the root
        * @param max the right bracket of the interval known to contain the root:
        * this value should be bigger than min and also it must hold that f(min)* f(max) < 0 otherwise
        * the function will throw an InvalidArgumentException
        * @param tol a binary functor that specifies the termination conditions:
        * when tol(min,max) becomes true the function will return the current interval
        * @param max_iter the maximun number of calls to f(x) to be made while searching for the root
        * @return a pair of values r that bracket the root so that
        * tol(r.first,r.second) < 0 || max_iter >= m where m is the initial value pased to max_iter
        *
        */
        template<class T, class F, class Tol>
        std::pair<T, T>
        bisec(F f, const T &min, const T &max, Tol tol, uint &max_iter);


        class Bisection {
        public:
            /**
             *
             * @param x_low
             * @param x_upper
             * @param TOL
             * @param nEvals
             */
            Bisection(const double x_low, const double x_upper, double TOL = 1e-5, int nEvals = 40)
                    : x_low(x_low), x_upper(x_upper), TOL(TOL), nEvals(nEvals) {}

            template<typename Function>
            double DoIt(Function &f);

        protected:
            double x_low, x_upper, TOL;
            int nEvals;

        };


    }
}


//--- Definitions -----//

#include<cmath>
#include<stdexcept>
#include <numerica/tools/exceptions/InvalidArgumentException.h>

namespace numerica {
    namespace roots {
        template<typename Function>
        double Bisection::DoIt(Function &f) {
            double a = x_low, b = x_upper;
            double x, y, y1 = f(a), y2 = f(b);
            if (y1 == 0) return a;
            if (y2 == 0) return b;
            for (int i = 0; i < nEvals; i++) {
                x = a + 0.5 * (b - a);
                if (fabs(x - a) < TOL) return x;
                y = f(x);
                if (y == 0) return x;
                if (y * y1 > 0) {
                    a = x;
                    y1 = y;
                } else {
                    b = x;
                    y2 = y;
                }
            }
            throw std::runtime_error("FindRoot1D::Bisection fails to obtain TOL");
        }

        template<typename T, class F, class Tol>
        std::pair<T, T>
        bisec(F f, const T &min, const T &max, Tol tol) {
            T _min = min;
            T _max = max;
            using numerica::tools::except::InvalidArgumentException;
            if (min >= max) throw InvalidArgumentException("bisec: min must be strict smaller than max");
            T fmin = f(min);
            T fmax = f(max);
            if (fmin * fmax > 0) throw InvalidArgumentException("bisec: intervals must contain a root");
            int iter_count = 0;
            while (!tol(_min, _max)) {
                T mid = (_min + _max) * 0.5;
                T fmid = f(mid);
                if (fmin * fmid <= 0) {
                    _max = mid;
                    fmax = fmid;
                } else {
                    _min = mid;
                    fmin = fmid;
                }
                iter_count++;
            }
            return std::make_pair(_min, _max);
        };


        template<class T, class F, class Tol>
        std::pair<T, T>
        bisec(F f, const T &min, const T &max, Tol tol , uint &max_iter) {

            T _min = min; // make a mutable copy
            T _max = max; // make a mutable copy
            uint m = max_iter;

            using numerica::tools::except::InvalidArgumentException;

            if (min >= max) throw InvalidArgumentException("bisec: min must be strict smaller than max");

            T fmin = f(min);

            T fmax = f(max);

            if (fmin * fmax > 0) throw InvalidArgumentException("bisec: intervals must contain a root");

            max_iter = 0;
            while (!tol(_min, _max) && max_iter < m) {
                //get the midle point
                T mid = (_min + _max) * 0.5;

                T fmid = f(mid);
                max_iter++; //update the function call count

                if (fmin * fmid <= 0) {
                    // bracket is in the left interval
                    _max = mid;
                    fmax = fmid;
                } else {

                    // bracket is in the right interval
                    _min = mid;
                    fmin = fmid;
                }
            }
            return std::make_pair(_min, _max);

        };


    }
}


#endif // BISECTION_H
