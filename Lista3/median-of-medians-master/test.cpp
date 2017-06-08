#include <vector>
#include <iostream>
#include <algorithm>

#include "median_of_medians.h"

int main()
{
    std::vector<int> vec {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    // sorter=std::sort and group-size=5 are default anyway
    auto result = detail::median_of_medians(vec.begin(), vec.end(), std::sort, 5);

    std::cout << "median of medians=" << *result << "\n";
}
