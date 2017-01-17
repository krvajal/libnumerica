#include "catch.hpp"

#include "../numerica/integration/integration.h"
#include "../numerica/tools/tools.h"

using namespace numerica::integration;

using  namespace numerica::tools;
TEST_CASE("Numerical integration","[integration]"){
    auto pi = numerica::tools::constants::pi;
    //create test function
    NVector v = sin(linspace(0,2*pi,1001));

    SECTION("Simpson integration"){

        REQUIRE(Simpson(v,0,2*pi) == Approx(0));
    }


}