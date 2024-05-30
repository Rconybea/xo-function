/* @file ex_id.cpp */

#include "xo/function/function.hpp"
#include "xo/function/reals.hpp"
#include "xo/function/grid1d_set.hpp"

using namespace std;

int
main() {
    using namespace xo::fn;

    vector<double> v{1,2,3,4,5};

    xo::fn::detail::grid_util::check_ordering(v, true);

    grid1d_set grid(reals::instance(), v);
}

/* end ex_id.cpp */
