/* @file grid1d_fn.test.cpp */

#include "xo/function/reals.hpp"
#include "xo/function/grid1d_set.hpp"
#include <catch2/catch.hpp>

namespace xo {
    namespace fn {
        using namespace std;

        TEST_CASE("fn.grid1d_set", "[function]") {
            vector<double> v{1,2,3,4,5};

            grid1d_set grid(reals::instance(), v);

            REQUIRE(grid.is_empty() == false);
            REQUIRE(grid.is_finite() == false);
            REQUIRE(grid.is_ordered() == true);

            REQUIRE(grid.glb_pos(0.99999) == -1);

        } /*TEST_CASE(fn.grid1d_set)*/

    } /*namespace fn*/
} /*namespace xo*/


/* end grid1d_fn.test.cpp */
