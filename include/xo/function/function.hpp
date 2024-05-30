/** @file function.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

#include <concepts>

namespace xo {
    namespace fn {
        /** @@class function.  A mapping from domain to range
         **/
        template <typename Domain, typename Range>
        class function {
            Range operator()(const Domain & x) const;
        };
    } /*namespace fn*/
} /*namespace xo*/

/** end function.hpp **/
