#include "catch.hpp"
#include "../numerica/roots/roots.h"




double f(double x)
{
    double a=cos(2.0*x);
    return a*a-x*x;

}
double fnewton(double x)
{
    return sin(x);
}

TEST_CASE("Root finding","[roots]"){


    numerica::roots::Brent brent{0.3,2.1};

    SECTION("BRENT"){
        REQUIRE(brent.DoIt(f) == Approx(0.5149).epsilon(0.01) );
        REQUIRE(brent.DoIt(fnewton) == Approx(1.0002));
    }
    SECTION("SECANT"){
        numerica::roots::Secant secant{0.5,3.54,1e-5,100};
        REQUIRE(secant.DoIt(fnewton) == Approx(3.1415926536));
    }
    SECTION("BISECTION"){

            numerica::roots::Bisection bisection{-1,1};
            auto linear = [](double x){return x;};
            REQUIRE(bisection.DoIt(linear) == Approx(0.0));


    }


}
