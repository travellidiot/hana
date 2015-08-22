/*!
@file
Forward declares `boost::hana::Optional`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_OPTIONAL_HPP
#define BOOST_HANA_FWD_OPTIONAL_HPP

#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/fwd/core/make.hpp>

#include <utility>


namespace boost { namespace hana {
    //! @ingroup group-datatypes
    //! Tag representing an optional value whose optional-ness is known at
    //! compile-time.
    //!
    //! An `Optional` either contains a value (represented as `just(x)`), or
    //! it is empty (represented as `nothing`). In essence, `Optional` is
    //! pretty much like a `boost::optional` or the upcoming `std::optional`,
    //! except the fact that an `Optional` is empty or not is known at
    //! compile-time. This can be particularly useful for returning from a
    //! function that might fail, when the reason of failure is unimportant.
    //! However, there is an important distinction to make between `Optional`
    //! and `std::optional`: `just(x)` and `nothing` do not share the same
    //! type. Hence, whether a `just` or a `nothing` will be returned from a
    //! function has to be known at compile-time for the return type to be
    //! computable by the compiler. This makes `Optional` well suited for
    //! static metaprogramming tasks but very poor for anything dynamic.
    //!
    //!
    //! Interoperation with `Type`s
    //! ---------------------------
    //! When a `just` contains an object of type `T` which is a `Type`,
    //! it has a nested `::%type` alias equivalent to `T::%type`. `nothing`,
    //! however, never has a nested `::%type` alias. If `t` is a `Type`,
    //! this allows `decltype(just(t))` to be seen as a nullary metafunction
    //! equivalent to `decltype(t)`. Along with the `sfinae` function,
    //! this allows `Optional` to interact seamlessly with SFINAE-friendly
    //! metafunctions.
    //! Example:
    //! @include example/optional/sfinae_friendly_metafunctions.cpp
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two `Optional`s are equal if and only if they are both empty or they
    //! both contain a value and those values are equal.
    //! @include example/optional/comparable.cpp
    //!
    //! 2. `Orderable`\n
    //! `Optional`s can be ordered by considering the value they are holding,
    //! if any. To handle the case of an empty `Optional`, we arbitrarily set
    //! `nothing` as being less than any other `just`. Hence,
    //! @code
    //!     just(x) < just(y) if and only if x < y
    //!     nothing < just(anything)
    //! @endcode
    //! Example:
    //! @include example/optional/orderable.cpp
    //!
    //! 3. `Functor`\n
    //! A `Optional` can be seen as a `List` containing either one element
    //! (`just(x)`) or no elements at all (`nothing`). As such, mapping
    //! a function over an `Optional` is equivalent to applying it to its
    //! value if there is one and to `nothing` otherwise:
    //! @code
    //!     transform(just(x), f) == just(f(x))
    //!     transform(nothing, f) == nothing
    //! @endcode
    //! Example:
    //! @include example/optional/functor.cpp
    //!
    //! 4. `Applicative`\n
    //! First, a value can be made optional with `lift<Optional>`, which is
    //! equivalent to `just`. Second, one can feed an optional value to an
    //! optional function with `ap`, which will return `just(f(x))` if there
    //! is both a function _and_ a value, and `nothing` otherwise:
    //! @code
    //!     ap(just(f), just(x)) == just(f(x))
    //!     ap(nothing, just(x)) == nothing
    //!     ap(just(f), nothing) == nothing
    //!     ap(nothing, nothing) == nothing
    //! @endcode
    //! A simple example:
    //! @include example/optional/applicative.cpp
    //! A more complex example:
    //! @include example/optional/applicative.complex.cpp
    //!
    //! 5. `Monad`\n
    //! The `Optional` `Monad` makes it easy to compose actions that might fail.
    //! One can feed an optional value if there is one into a function with
    //! `chain`, which will return `nothing` if there is no value. Finally,
    //! optional-optional values can have their redundant level of
    //! `Optional`ness removed with `flatten`. Also note that the `|` operator
    //! can be used in place of the `chain` function.
    //! Example:
    //! @include example/optional/monad.cpp
    //!
    //! 6. `MonadPlus`\n
    //! The `Optional` MonadPlus makes it easy to choose the first valid value
    //! of two optional values. If both optional values are `nothing`s, then
    //! `concat` will return `nothing`.
    //! Example:
    //! @include example/optional/monad_plus.cpp
    //!
    //! 7. `Foldable`\n
    //! Folding an `Optional` is equivalent to folding a `List` containing
    //! either no elements (for `nothing`) or `x` (for `just(x)`).
    //! Example:
    //! @include example/optional/foldable.cpp
    //!
    //! 8. `Searchable`\n
    //! Searching an `Optional` is equivalent to searching a list containing
    //! `x` for `just(x)` and an empty list for `nothing`.
    //! Example:
    //! @include example/optional/searchable.cpp
    struct Optional { };

    //! Create an optional value.
    //! @relates Optional
    //!
    //! Specifically, `make<Optional>()` is equivalent to `nothing`, and
    //! `make<Optional>(x)` is equivalent to `just(x)`. This is provided
    //! for consistency with the other `make<...>` functions.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <>
    constexpr auto make<Optional> = []([auto&& x]) {
        return unspecified-type{forwarded(x)};
    };
#endif

    //! Alias to `make<Optional>`; provided for convenience.
    //! @relates Optional
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/make.cpp
    constexpr auto make_optional = make<Optional>;

    //! Create an optional value containing `x`.
    //! @relates Optional
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/just.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto just = [](auto&& x) {
        return unspecified-type;
    };
#else
    template <typename T>
    struct just_t;

    struct make_just_t {
        template <typename T>
        constexpr auto operator()(T&&) const;
    };

    constexpr make_just_t just{};
#endif

    //! An empty optional value.
    //! @relates Optional
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/nothing.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr unspecified-type nothing{};
#else
    struct nothing_t : operators::adl {
        static constexpr bool is_just = false;
        using hana = nothing_t;
        using datatype = Optional;
    };

    constexpr nothing_t nothing{};
#endif

    //! Create an `Optional` with the result of a function, but only if a
    //! predicate is satisfied.
    //! @relates Optional
    //!
    //! Specifically, returns `just(f(x))` if `predicate(x)` is a true-valued
    //! `Logical`, and `nothing` otherwise.
    //!
    //!
    //! @param predicate
    //! A function called as `predicate(x)` and returning a true-valued
    //! `Logical` if `just(f(x))` should be the resulting value, and a
    //! false-valued one if `nothing` should be the resulting value.
    //! Since the types of `just` and `nothing` differ, the result of
    //! `predicate` has to be a compile-time `Logical`.
    //!
    //! @param f
    //! A function called as `f(x)` if the `predicate` returns a true-valued
    //! `Logical`, and not called at all otherwise. If the `predicate` returns
    //! a false-valued `Logical`, the `f(x)` expression is not even required
    //! to be well-formed.
    //!
    //! @param x
    //! The value to either transform and put in a `just`, or discard.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/only_when.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto only_when = [](auto&& predicate, auto&& f, auto&& x) -> decltype(auto) {
        if (forwarded(predicate)(x))
            return just(forwarded(f)(forwarded(x)));
        else
            return nothing;
    };
#else
    struct only_when_t {
        template <typename Pred, typename F, typename X>
        constexpr decltype(auto) operator()(Pred&& pred, F&& f, X&& x) const;
    };

    constexpr only_when_t only_when{};
#endif

    //! Apply a function to the contents of an `Optional`, with a fallback
    //! result.
    //! @relates Optional
    //!
    //! Specifically, `maybe` takes a default value, a function and an
    //! optional value. If the optional value is `nothing`, the default
    //! value is returned. Otherwise, the function is applied to the
    //! content of the `just`.
    //!
    //!
    //! @param default_
    //! A default value returned if `m` is `nothing`.
    //!
    //! @param f
    //! A function called as `f(x)` if and only if `m` is an optional value
    //! of the form `just(x)`. In that case, the result returend by `maybe`
    //! is the result of `f`.
    //!
    //! @param m
    //! An optional value.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/maybe.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto maybe = [](auto&& default_, auto&& f, auto&& m) -> decltype(auto) {
        if (m is a just(x)) {
            return forwarded(f)(forwarded(x));
        else
            return forwarded(default_);
        }
    };
#else
    struct maybe_t {
        template <typename Def, typename F, typename T>
        constexpr decltype(auto) operator()(Def&&, F&& f, just_t<T> const& m) const
        { return static_cast<F&&>(f)(m.val); }

        template <typename Def, typename F, typename T>
        constexpr decltype(auto) operator()(Def&&, F&& f, just_t<T>& m) const
        { return static_cast<F&&>(f)(m.val); }

        template <typename Def, typename F, typename T>
        constexpr decltype(auto) operator()(Def&&, F&& f, just_t<T>&& m) const
        { return static_cast<F&&>(f)(std::move(m).val); }

        template <typename Def, typename F>
        constexpr Def operator()(Def&& def, F&&, nothing_t) const
        { return static_cast<Def&&>(def); }
    };

    constexpr maybe_t maybe{};
#endif

    //! Return whether an `Optional` contains a value.
    //! @relates Optional
    //!
    //! Specifically, returns a compile-time true-valued `Logical` if `m` is
    //! of the form `just(x)` for some `x`, and a false-valued one otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/is_just.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_just = [](auto const& m) {
        return m is a just(x);
    };
#else
    struct is_just_t {
        template <typename M>
        constexpr auto operator()(M const&) const;
    };

    constexpr is_just_t is_just{};
#endif

    //! Return whether an `Optional` is empty.
    //! @relates Optional
    //!
    //! Specifically, returns a compile-time true-valued `Logical` if `m` is
    //! a `nothing`, and a false-valued one otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/is_nothing.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_nothing = [](auto const& m) {
        return m is a nothing;
    };
#else
    struct is_nothing_t {
        template <typename M>
        constexpr auto operator()(M const&) const;
    };

    constexpr is_nothing_t is_nothing{};
#endif

    //! Return the contents of an `Optional`, with a fallback result.
    //! @relates Optional
    //!
    //! Specifically, returns `x` if `m` is `just(x)`, and `default_`
    //! otherwise.
    //!
    //!
    //! @param default_
    //! The default value to return if `m` is `nothing`.
    //!
    //! @param m
    //! The optional value to try to retrieve the value from.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/from_maybe.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto from_maybe = [](auto&& default_, auto&& m) -> decltype(auto) {
        return maybe(forwarded(default_), id, forwarded(m));
    };
#else
    struct from_maybe_t {
        template <typename Default, typename M>
        constexpr decltype(auto) operator()(Default&& default_, M&& m) const;
    };

    constexpr from_maybe_t from_maybe{};
#endif

    //! Extract the content of an `Optional` or fail at compile-time.
    //! @relates Optional
    //!
    //! Specifically, returns `x` if the optional value is `just(x)`, and
    //! triggers a static assertion otherwise. For convenience, the pointer
    //! dereference operators (`*` and `->`)  can be used as an equivalent
    //! way of calling this method or calling this method and accessing a
    //! member of the returned object, respectively.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/from_just.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto from_just = [](auto&& m) -> decltype(auto) {
        static_assert(m is a just(x),
        "can't use boost::hana::from_just on a boost::hana::nothing");
        return forwarded(x);
    };
#else
    struct from_just_t {
        template <typename M>
        constexpr decltype(auto) operator()(M&& m) const;
    };

    constexpr from_just_t from_just{};
#endif

    //! Calls a function if the call expression is well-formed.
    //! @relates Optional
    //!
    //! Given a function `f`, `sfinae` returns a new function applying `f`
    //! to its arguments and returning `just` the result if the call is
    //! well-formed, and `nothing` otherwise. In other words, `sfinae(f)(x...)`
    //! is `just(f(x...))` if that expression is well-formed, and `nothing`
    //! otherwise. Note, however, that it is possible for an expression
    //! `f(x...)` to be well-formed as far as SFINAE is concerned, but
    //! trying to actually compile `f(x...)` still fails. In this case,
    //! `sfinae` won't be able to detect it and a hard failure is likely
    //! to happen.
    //!
    //!
    //! @note
    //! The function given to `sfinae` must not return `void`, since
    //! `just(void)` does not make sense. A compilation error is
    //! triggered if the function returns void.
    //!
    //!
    //! Example
    //! -------
    //! @include example/optional/sfinae.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto sfinae = [](auto&& f) {
        return [perfect-capture](auto&& ...x) {
            if (decltype(forwarded(f)(forwarded(x)...)) is well-formed)
                return just(forwarded(f)(forwarded(x)...));
            else
                return nothing;
        };
    };
#else
    struct sfinae_t {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const;
    };

    constexpr sfinae_t sfinae{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_OPTIONAL_HPP