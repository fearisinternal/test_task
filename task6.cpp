#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::pair<int64_t, int64_t>> nums = {};
    int64_t n = nums.size();
    std::sort(nums.begin(), nums.end());
    int64_t x0 = (nums[0].first + nums[n - 1].first);
    for (auto i = 0; i <= n / 2; i++)
    {
        if (nums[i] == nums[n - 1 - i])
            continue;
        if ((nums[i].first + nums[n - 1 - i].first) != x0)
            std::cout << "ERR: x" << std::endl;
        if (nums[i].second != nums[n - 1 - i].second)
            std::cout << "ERR: y" << std::endl;
    }
    std::cout << "OK";
}