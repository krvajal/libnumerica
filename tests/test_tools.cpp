#include "catch.hpp"

#include "../numerica/tools/tools.h"

using namespace numerica::tools;
using namespace except;

TEST_CASE("Base tools", "[tools]") {


    SECTION("linspace") {
        NVector v = linspace(0, 1, 2);

        REQUIRE(v.size() == 2);
        REQUIRE(v[0] == Approx(0));
        REQUIRE(v[1] == Approx(1));
        v = linspace(0, 100, 2);

        REQUIRE(v.size() == 2);
        REQUIRE(v[0] == Approx(0));
        REQUIRE(v[1] == Approx(100));

        v = linspace(-10, 10, 3);
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == Approx(-10));
        REQUIRE(v[1] == Approx(0));
        REQUIRE(v[2] == Approx(10));

        SECTION("Inversed interval") {

            v = linspace(10, -10, 3);
            INFO("DEFINE A REVERSED ARRAY");
            REQUIRE(v.size() == 3);
            REQUIRE(v[0] == Approx(10));
            REQUIRE(v[1] == Approx(0));
            REQUIRE(v[2] == Approx(-10));
        }

        SECTION("0 length interval") {
            CHECK_THROWS_AS(linspace(0, 10, 0), InvalidArgumentException);
            CHECK_THROWS_AS(linspace(0, 1, 1), InvalidArgumentException);
            CHECK_NOTHROW(linspace(0, 0, 1));

        }

    }
    SECTION("vector operations","[nvector]") {

        NVector v1 = linspace(0, 10, 10);
        NVector sum;
        NVector prod;
        WHEN("sum two vectors ") {
            sum = v1 + v1;
            prod = v1 * 2;
            CHECK(sum.size() == v1.size());
            for (int i = 0; i < sum.size(); i++)
                CHECK(prod[i] == sum[i]);
            CHECK(sum[0] == Approx(0));
        }

    }


}