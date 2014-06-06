/*!
@file
Defines `boost::hana::Functor`.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTOR_HPP
#define BOOST_HANA_FUNCTOR_HPP

#include <boost/hana/core.hpp>
#include <boost/hana/detail/constexpr.hpp>


namespace boost { namespace hana {
    /*!
    @typeclass{Functor}
    @{
    `Functor` represents types that can be mapped over.

    @mcd
    `fmap`

    @laws
    Instances of `Functor` must satisfy the following laws:
    @code
        fmap id == id
        fmap (f . g) == fmap f . fmap g
    @endcode
     */
    template <typename T>
    struct Functor;

    //! Maps `f` over a `Functor`.
    //! @method{Functor}
    //!
    //! ### Fusion example
    //! @snippet example/list/functor/fmap.cpp fusion
    //!
    //! ### MPL example
    //! @snippet example/list/functor/fmap.cpp mpl
    BOOST_HANA_CONSTEXPR_LAMBDA auto fmap = [](auto f, auto functor) {
        return Functor<datatype_t<decltype(functor)>>::fmap_impl(f, functor);
    };

    //! @}
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTOR_HPP
