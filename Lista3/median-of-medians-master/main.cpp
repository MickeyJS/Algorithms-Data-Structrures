#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

#include "median_of_medians.h"

namespace sorter
{

template<class It, class Cmp>
void insertion_sort(It first, It last, Cmp cmp)
{
    for (auto begin = first; begin != last; ++begin)
    {
        const auto insertion = std::upper_bound(first, begin, *begin, cmp);
        std::rotate(insertion, begin, std::next(begin));
    }
}

template<class It>
void insertion_sort(It first, It last)
{
	insertion_sort(first, last, std::less<>());
}

} // namespace sorter

int main()
{
    std::vector<int> input {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int groupsize[] = {3,4,5,6,7,10,15};

    for (int i : groupsize)
    {
        auto result = detail::median_of_medians(input.begin(), input.end(), i, sorter::insertion_sort);
        std::cout << "groupsize=" << i << " ,median of medians=" << *result << "\n";
    }

    std::cout << '\n';

    std::vector<int> input2(100);
    std::iota(input2.begin(), input2.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(input2.begin(), input2.end(), g);

    for (int i : groupsize)
    {
        auto result = detail::median_of_medians(input2.begin(), input2.end(), i);
        std::cout << "groupsize=" << i << " ,median of medians=" << *result << "\n";
    }
}
