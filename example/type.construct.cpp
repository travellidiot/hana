/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/type.hpp>

#include <initializer_list>
#include <string>
#include <vector>
using namespace boost::hana;


//! [construct]
struct Person {
    std::string name;
    unsigned int age;
};

bool operator==(Person x, Person y)
{ return x.name == y.name && x.age == y.age; }

int main() {
    Person john{"John Doe", 30};
    BOOST_HANA_RUNTIME_ASSERT(type<Person>("John Doe", 30u) == john);

    std::vector<int> v{1, 2, 3};
    auto u = type<std::vector<int>>(std::initializer_list<int>{1, 2, 3});
    BOOST_HANA_RUNTIME_ASSERT(u == v);
}
//! [construct]
