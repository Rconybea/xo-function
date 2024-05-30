/** @file set_concept.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

#include <concepts>

namespace xo {
    namespace fn {
        template <typename Set>
        concept set_concept = requires(Set set)
        {
            /** (default) representation for elements **/
            typename Set::approx_elt_type;

            { set.is_empty() } -> std::same_as<bool>;
            { set.is_finite() } -> std::same_as<bool>;
            { set.is_ordered() } -> std::same_as<bool>;
        };
    } /*namespace fn*/
} /*namespace xo*/

/** end set_concept.hpp **/
