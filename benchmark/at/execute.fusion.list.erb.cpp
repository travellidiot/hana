/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

<% if input_size > 10 %>
    #define FUSION_MAX_LIST_SIZE <%= ((input_size + 9) / 10) * 10 %>
<% end %>

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/make_list.hpp>

#include "measure.hpp"
#include <cstdlib>
namespace fusion = boost::fusion;


int main () {
    boost::hana::benchmark::measure([] {
        unsigned long long result = 0;
        for (int iteration = 0; iteration < 1 << 10; ++iteration) {
            auto values = fusion::make_list(
                <%= input_size.times.map { 'std::rand()' }.join(', ') %>
            );

            <% (0..(input_size-1)).each { |n| %>
                result += fusion::at_c<<%= n %>>(values);
            <% } %>
        }
    });
}
