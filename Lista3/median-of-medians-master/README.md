# median-of-medians
a selection algorithm based on quickselect.

## Example Usage

1. download `median_of_medians.h`
2. create file `test.cpp`:

``` cpp
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
 ```

3. compile & execute: `g++ -o test -std=c++1z test.cpp ; ./test`

## Dependencies

none.

## License 

(c) 2017 Daniel Feist. Licensed under the MIT license.
