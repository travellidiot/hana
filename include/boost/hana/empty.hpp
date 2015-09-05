/*!
@file
Defines `boost::hana::empty`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EMPTY_HPP
#define BOOST_HANA_EMPTY_HPP

#include <boost/hana/fwd/empty.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


namespace boost { namespace hana {
    template <typename M>
    struct empty_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(_models<MonadPlus, M>::value,
        "hana::empty<M>() requires 'M' to be a MonadPlus");
    #endif

        constexpr auto operator()() const {
            using Empty = BOOST_HANA_DISPATCH_IF(empty_impl<M>,
                _models<MonadPlus, M>::value
            );

            return Empty::apply();
        }
    };

    template <typename M, bool condition>
    struct empty_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct empty_impl<S, when<_models<Sequence, S>::value>> {
        static constexpr auto apply() {
            return hana::make<S>();
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EMPTY_HPP