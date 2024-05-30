/** @file reals.hpp
 *
 *  Author: Roland Conybeare
 **/

#pragma once

//#include <cstdint>

namespace xo {
    namespace fn {
        /** @class reals
         *  @brief The set of real numbers -oo < x < +oo
         *
         *  Abstraction for the set of real numbers.
         *  Immutable zero-sized singleton
         **/
        class reals {
        public:
            using approx_elt_type = double;

        public:
            reals() = default;

            static reals instance() { return s_instance; }

            bool is_empty() const { return false; }
            bool is_finite() const { return false; }
            bool is_ordered() const { return true; }

        private:
            /** singleton instance **/
            static reals s_instance;
        };
    } /*namespace fn*/
} /*namespace xo*/


/** end reals.hpp **/
