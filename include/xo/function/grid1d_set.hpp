/** @file grid1d_set.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

#include "set_concept.hpp"
#include "xo/indentlog/print/tag.hpp"
#include "xo/indentlog/print/tostr.hpp"
#include <vector>
#include <stdexcept>
//#include <cstdint>

namespace xo {
    namespace fn {
        namespace detail {
            /** @class grid_util.
             *
             *  @brief Utility functions for working with 1d grids
             **/
            struct grid_util {
                /** verify that members of @p grid appear in strictly-increasing order.
                 *  If @p grid is out-of-order and @p ex_on_fail is true,  throw a @c std::runtime_error
                 *  exception
                 *  @retval @c true on success, @c false on failure
                 **/
                template <typename Repr>
                static bool check_ordering(const Repr & grid,
                                           bool ex_on_fail) {
                    for (size_t i = 1; i < grid.size(); ++i) {
                        if (grid[i-1] >= grid[i]) {
                            throw std::runtime_error(tostr("grid1d_set::check_ordering: out-of-order elements v[i-1], v[i]",
                                                           xtag("i", i), xtag("v[i-1]", grid[i-1]), xtag("v[i]", grid[i])));

                            return false;
                        }
                    }

                    return true;
                }
            };
        }

        /** @class grid1d_set
         *  @brief A totally-ordered set of points.
         *
         *  Intended for discretizing an interval,  for example to construct a
         *  finite approximation to a continuous function.
         **/
        template <typename Set,
                  typename ApproxEltType = typename Set::approx_elt_type>
        class grid1d_set {
        public:
            static_assert(set_concept<Set>);

            /** set being discretized by this grid **/
            using underlying_set_type = Set;
            /** approximate set members using this type **/
            using approx_elt_type = ApproxEltType;
            /** representation for an ordered collection of grid elements **/
            using repr_type = std::vector<approx_elt_type>;
            /** position in a grid.
             *  -1 -> sentinel value
             *  0 -> 1st (smallest) member
             *  n-1 -> last (largest) member (where n = .size())
             **/
            using pos_type = ssize_t;

            using const_iterator = typename repr_type::const_iterator;
            using const_reverse_iterator = typename repr_type::const_reverse_iterator;

        public:
            grid1d_set(const underlying_set_type & ul_set,
                       const repr_type & elt_v,
                       bool verify_ordering = true)
                : ul_set_{ul_set}, elt_v_{elt_v}
                {
                    if (verify_ordering)
                        detail::grid_util::check_ordering(elt_v, true /*ex_on_fail*/);
                }
            grid1d_set(const underlying_set_type & ul_set,
                       repr_type && elt_v,
                       bool verify_ordering = true)
                : ul_set_{ul_set}, elt_v_{std::move(elt_v)}
                {
                    if (verify_ordering)
                        detail::grid_util::check_ordering(elt_v, true /*ex_on_fail*/);
                }
            grid1d_set(grid1d_set && x) = default;
            grid1d_set(const grid1d_set & x) = default;

            /** @note we identify the grid, with the set being approximated **/

            /** true iff the set being approximated is empty **/
            bool is_empty() const { return ul_set_.is_empty(); }
            /** true iff the set being approximated is finite (very likely false) **/
            bool is_finite() const { return ul_set_.is_finite(); }
            /** true, since the set being approximated must be totally ordered. **/
            bool is_ordered() const { return true; }

            /** size of grid **/
            std::size_t size() const { return elt_v_.size(); }

            /** compute greatest-lower-bound of @p x in grid **/
            pos_type glb_pos(approx_elt_type x, bool allow_eq = true) const {
                /* binary search */
                if (elt_v_.empty()
                    || (allow_eq ? (x < elt_v_[0]) : (x <= elt_v_[0])))
                {
                    return -1;
                }

                /* here: elt_v[0] is a lower bound for x,
                 * so a greatest lower bound for x, in elt_v[], must exist
                 */

                pos_type i_lo = 0;
                pos_type i_hi = elt_v_.size();

                while (i_lo + 1 < i_hi) {
                    /* glb is in [i_lo,..,i_hi-1].
                     * when i_lo+1 == i_hi, i_lo is desired glb
                     */

                    pos_type i_mid = i_lo + (i_hi - i_lo) / 2;

                    if (allow_eq ? (x < elt_v_[i_mid]) : (x <= elt_v_[i_mid])) {
                        /* elt_v_[i_mid] is not a lower bound */
                        i_hi = i_mid;
                    } else {
                        i_lo = i_mid;
                    }
                }

                return i_lo;
            }

            /** we can iterate over grid members **/
            const_iterator cbegin() const { return elt_v_.cbegin(); }
            const_iterator cend() const { return elt_v_.cend(); }
            const_iterator crbegin() const { return elt_v_.crbegin(); }
            const_iterator crend() const { return elt_v_.crend(); }

            grid1d_set & operator= (grid1d_set && x) = default;
            grid1d_set & operator= (const grid1d_set & x) = default;

        private:
            /** underlying set for which this grid is defined;
             *  for example could be reals::instance().
             *  More likely will be a (perhaps real-valued) observable
             **/
            underlying_set_type ul_set_;
            /** 1-dimensional grid of elements
             *  @invariant members of @ref elt_v_ are strictly increasing
             **/
            repr_type elt_v_;
        };
    } /*namespace fn*/
} /*namespace xo*/


/** end grid1d_set.hpp **/
