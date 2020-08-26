#include <vector>
#include <iostream>
#include <algorithm> // std::max, std::min

// #11
int contain_most_water(std::vector<int>& nums)
{
    int n = nums.size();

    if (n == 0) return 0;

    int l = 0, r = n-1;

    int most = 0;

    while (l < r)
    {
        most = std::max(most, std::min(nums[l], nums[r]) * (r-l));
        if (nums[l] > nums[r]) --r;
        else ++l;
    }

    return most;
}

// #42
int trap_most_water(std::vector<int>& nums)
{
    int n = nums.size();
    if (n == 0) return 0;

    int l = 0, l_max = nums[l], r = n-1, r_max = nums[r], trapped = 0;

    while (l < r)
    {
        if (nums[l] < nums[r])
        {
            ++l;
            l_max = std::max(l_max, nums[l]);
            trapped += (l_max - nums[l]);

        }
        else
        {
            --r;
            r_max = std::max(r_max, nums[r]);
            trapped += (r_max - nums[r]);
        }
    }

    return trapped;
}
