/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/power.hpp>
namespace hana = boost::hana;


BOOST_HANA_CONSTANT_CHECK(hana::power(hana::int_<3>, hana::int_<2>) == hana::int_<3 * 3>);
static_assert(hana::power(2, hana::int_<4>) == 16, "");

int main() { }