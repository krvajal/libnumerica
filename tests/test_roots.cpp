#include "catch.hpp"
#include <numerica/roots/roots.h>
#include <tuple>

using namespace numerica::roots;



/* f(x) = x^{20} - 1 */
/* f'(x) = 20x^{19} */
/* zero at x = 1 or -1 */

double func1(double x) {
    return pow(x, 20.0) - 1;
}

/* f(x) = sqrt(abs(x))*sgn(x) */
/* f'(x) = 1 / sqrt(abs(x) */
/* zero at x = 0 */
double func2(double x) {
    double delta;

    if (x > 0)
        delta = 1.0;
    else if (x < 0)
        delta = -1.0;
    else
        delta = 0.0;

    return sqrt(fabs(x)) * delta;
}

/* f(x) = x^2 - 1e-8 */
/* f'(x) = 2x */
/* zero at x = sqrt(1e-8) or -sqrt(1e-8) */
double func3(double x) {
    return pow(x, 2.0) - 1e-8;
}

/* f(x) = x exp(-x) */
/* f'(x) = exp(-x) - x exp(-x) */
/* zero at x = 0 */
double func4(double x) {
    return x * exp(-x);
}


/* f(x) = 1/(1+exp(x)) */
/* f'(x) = -exp(x) / (1 + exp(x))^2 */
/* no roots! */
double func5(double x, void *p) {
    return 1 / (1 + exp(x));
}


/* f(x) = (x - 1)^7 */
/* f'(x) = 7 * (x - 1)^6 */
/* zero at x = 1 */
double func6(double x) {
    return pow(x - 1, 7.0);
}


/* linear function to test that solvers exit correctly
   when entered with an exact root */

double func7(double x) {
    return -M_PI * x + M_E;
}


TEST_CASE("Root finding", "[roots]") {

    using numerica::tools::constants::pi;
    numerica::roots::Brent brent{0.3, 2.1};


    SECTION("Root bracketing") {

        auto res = BracketRoots(func2, 0.0, 2 * pi, 0.2, 2);
        REQUIRE(res.size() <= 2);
        int maxRoots = 2;
        double dx = 0.2;
        res = BracketRoots(func2, 0.0, 10 * pi, dx, maxRoots);
        REQUIRE(res.size() <= maxRoots);

        WHEN("Increase the maxRoot") {
            maxRoots = 10;
            dx = 0.2;
            THEN("the number of roots should be kept small") {
                res = BracketRoots(sin, 0.0, 10 * pi, dx, maxRoots);
                REQUIRE(res.size() <= maxRoots);
                REQUIRE(res.size() == 10);
            }

        }
        WHEN("Increase the dx") {
            dx = 4;
            THEN("the number of roots should be reduced") {
                res = BracketRoots(func2, 0.0, 10 * pi, dx, maxRoots);
                REQUIRE(res.size() < 4);

            }
        }


    }
    SECTION("BRENT") {
//        REQUIRE(brent.DoIt(func1) == Approx(0.5149).epsilon(0.01));
//        CHECK_THROWS(brent.DoIt(func2));
    }
    SECTION("SECANT") {
        numerica::roots::Secant secant{0.5, 3.54, 1e-5, 100};
        REQUIRE(secant.DoIt(sin) == Approx(pi).epsilon(1e-5));
    }
    SECTION("BISECTION") {

        double eps = 1e-8;
        REQUIRE(bisec(sin, 3.0, 4.0, eps_termination<double>(eps)).first == Approx(pi).epsilon(eps));
        REQUIRE(bisec(sin, 3.0, 4.0, eps_termination<double>(eps)).second == Approx(pi).epsilon(eps));
        REQUIRE(bisec(sin, -4.0, -3.0, eps_termination<double>(eps)).first == Approx(-pi).epsilon(eps));
        REQUIRE(bisec(sin, -4.0, -3.0, eps_termination<double>(eps)).second == Approx(-pi).epsilon(eps));
        REQUIRE(bisec(sin, -1 / 3.0, 1.0, eps_termination<double>(eps)).first == Approx(0.0).epsilon(eps));
        REQUIRE(bisec(sin, -1 / 3.0, 1.0, eps_termination<double>(eps)).second == Approx(0.0).epsilon(eps));
        REQUIRE(bisec(cos, 0.0, 3.0, eps_termination<double>(eps)).first == Approx(pi/2).epsilon(eps));
        REQUIRE(bisec(cos, 0.0, 3.0, eps_termination<double>(eps)).second == Approx(pi/2).epsilon(eps));
        REQUIRE(bisec(func1, 0.1, 2.0, eps_termination<double>(eps)).first == Approx(1.0).epsilon(eps));
        REQUIRE(bisec(func1, 0.1, 2.0, eps_termination<double>(eps)).second == Approx(1.0).epsilon(eps));
        INFO("f(x) = \"sqrt(|x|)*sgn(x)\"");
        REQUIRE(bisec(func2, -1.0/3, 1.0, eps_termination<double>(eps)).first == Approx(0.0).epsilon(eps));
        REQUIRE(bisec(func2, -1.0/3, 1.0, eps_termination<double>(eps)).second == Approx(0.0).epsilon(eps));
        INFO("f(x) = x^2");
        REQUIRE(bisec(func3, 0.0, 1.0, eps_termination<double>(eps)).first == Approx(sqrt(1e-8)).epsilon(eps));
        REQUIRE(bisec(func3, 0.0, 1.0, eps_termination<double>(eps)).second == Approx(sqrt(1e-8)).epsilon(eps));

        INFO("f(x) = x exp(-x)");

        REQUIRE(bisec(func4, -1.0/3, 2.0, eps_termination<double>(eps)).first == Approx(0.0).epsilon(eps));
        REQUIRE(bisec(func4, -1.0/3, 2.0, eps_termination<double>(eps)).second == Approx(0.0).epsilon(eps));

        INFO("f(x) = \"(x - 1)^7");
        REQUIRE(bisec(func6, 0.9995, 1.0002, eps_termination<double>(eps)).first == Approx(1.0).epsilon(eps));
        REQUIRE(bisec(func6, 0.9995, 1.0002, eps_termination<double>(eps)).second == Approx(1.0).epsilon(eps));






    }


}
