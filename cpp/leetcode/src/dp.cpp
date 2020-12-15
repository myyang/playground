#include <unordered_map>
#include <vector>
#include <algorithm>

#include "dp.h"

// #70
int climbing_stairs(int n)
{
    if (n <= 0) return 0;
    int dp1 = 1, dp2 = 1, cur = 1;
    for (int i = 2; i <= n; ++i)
    {
        cur = dp1 + dp2;
        dp1 = dp2;
        dp2 = cur;
    }
    return cur;
}

// #1137
int tribonacci(int n)
{
    if (n <= 0) return 0;
    int dp0 = 0, dp1 = 1, dp2 = 1, cur = 1;
    for (int i = 3; i <= n; ++i)
    {
        cur = dp0 + dp1 + dp2;
        dp0 = dp1;
        dp1 = dp2;
        dp2 = cur;
    }
    return cur;
}

// #303
RangeQuery::RangeQuery(std::vector<int>& nums): sums(nums) {
    if (sums.empty()) return;
    for (int i = 1; i < sums.size(); ++i) sums[i] = sums[i-1] + sums[i];
};

int RangeQuery::get_sum_between(int i, int j) {
    if (i == 0) return sums[j];
    return sums[j] - sums[i-1];
}

// #1218
int longest_subsequence(std::vector<int>& nums, int diff) {
    int max_dp = 1;
    /* Brute Force
       std::vector<int> dp(nums.size(), 1);

       for (int i = 1; i < nums.size(); ++i)
       {
       for (int j = 0; j < i; ++j)
       {
       if (nums[i] == nums[j] + diff)
       {
       dp[i] = std::max(dp[i], dp[j] + 1);
       max_dp = std::max(dp[i], max_dp);
       }
       }
       }
       */

    std::unordered_map<int, int> dp;
    for (int i: nums)
    {
        if (dp.count(i-diff)) dp[i] = dp[i-diff] + 1;
        else dp[i] = 1;
        max_dp = std::max(dp[i], max_dp);
    }
    return max_dp;
}

// #53
int maximum_subarray(std::vector<int>& nums) {
    int max_dp = nums[0];
    std::vector<int> dp(nums.begin(), nums.end());

    for (int i = 1; i < dp.size(); ++i)
    {
        dp[i] = std::max(dp[i], dp[i-1] + dp[i]);
        max_dp = std::max(dp[i], max_dp);
    }
    return max_dp;
}
