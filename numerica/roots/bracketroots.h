#ifndef ROOTLOCALIZER_H
#define ROOTLOCALIZER_H

#include <vector>
#include <functional>
#include <numerica/tools/nvector.h>


namespace numerica {
    namespace roots {

        using std::function;
        using std::vector;
        using std::pair;
        using numerica::tools::NVector;


        vector<pair<double, double> > BracketRoots(const std::function<double(const double &)> &f, double a, double b,
                                                   double dx, int maxIntervals = -1) {
            vector<pair<double, double> > intervals;
            int n = (b - a) / dx, c = 0;

            double xa = a, fa = f(a), x, fx;

            for (int i = 0; i <= n; i++) {
                if (intervals.size() == maxIntervals) break;

                x = xa + dx;
                if (x > b) x = b;
                fx = f(x);
                if (fx * fa < 0. || fa == 0.) {
                    intervals.push_back({xa, x});
                }
                xa = x;
                fa = fx;
            }
            return intervals;
        }

        vector<int> LocalizeRoots(const NVector values, int maxIntervals = -1) {

            vector<int> intervals;
            for (int i = 1; i < values.size(); i++) {
                if (intervals.size() == maxIntervals) break;
                if (values[i - 1] * values[i] < 0) {
                    intervals.emplace_back(i - 1);
                }
            }
            return intervals;
        };

    }
}


#endif // ROOTLOCALIZER_H
