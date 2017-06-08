// The MIT License (MIT)

// Copyright (c) 2017 Daniel Feist

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MEDIAN_OF_MEDIANS_H_
#define MEDIAN_OF_MEDIANS_H_

#include <algorithm>
#include <iostream>
#include <cassert>

namespace detail
{

template<typename Iter,
         typename Difference_type = typename Iter::difference_type,
         typename Sorter = decltype(std::sort<Iter>)>
Iter
median_of_medians(Iter first, Iter last, Difference_type s = 5, Sorter sorter = std::sort<Iter>)
{
    assert(s > 2);

    using std::next;
    using std::prev;
    using std::distance;

    auto begin = first;
    Difference_type n = distance(first, last);
    Difference_type median = s/2;

    if (n <= s)
    {
        sorter(first, last);
        return next(first, (n-1)/2);
    }

    for (; next(first, s-1) <= prev(last); std::advance(first, s))
    {
        sorter(first, next(first, s));
        std::iter_swap(next(first, median), next(begin, distance(begin, first)/s));
    }

    auto end_of_medians = next(begin, (distance(begin, first)/s));

    if (first < last)
    {
        sorter(first, last);

        if (distance(first, last) <= 2)
            std::iter_swap(first, next(begin, distance(begin, first)/s));
        else
            std::iter_swap(next(first), next(begin, distance(begin, first)/s));

        ++end_of_medians;
    }

    median_of_medians(begin, end_of_medians, s, sorter);
}

} // namespace detail

#endif // header guard
