#include <iostream>
#include <vector>

static int Stairs(std::vector<int> nums, int A)
{
    int answer = 0;
    int n = nums.size();

    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            if (nums[j] != j - i + 1)
            {
                break;
            }
            if (j - i + 1 == A)
            {
                answer++;
                break;
            }
        }
    }

    return answer;
}

int main()
{
    int A = 4;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 1, 2, 3, 1, 2, 4, 1, 2, 3, 4};
    std::cout << Stairs(nums, A);
    return 0;
}