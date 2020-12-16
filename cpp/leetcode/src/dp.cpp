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

// #62
int unique_paths(int m, int n) {
    std::vector<int> dp(m, 1);
    for (int i = 0; i < n-1; ++i)
        for (int j = 1; j < m; ++j)
            dp[j] = dp[j-1] + dp[j];
    return dp[m-1];
}

// #63
int unique_paths_2(std::vector<std::vector<int>>& grids) {
    int n = grids.size();
    int m = grids[0].size();
    /* space optimized
       std::vector<int> dp(m, INT_MIN);
       dp[0] = 1;
       for (int i = 1; i < m; ++i) dp[i] = (grids[0][i] == 1 || dp[i-1] == 0) ? 0: 1;

       for (int i = 1; i < n; ++i)
       {
       if (grids[i][0] == 1) dp[0] = 0;

       for (int j = 1; j < m; ++j)
       if (grids[i][j] == 1) dp[j] = 0;
       else dp[j] = dp[j-1] + dp[j];
       }

       for (auto i: dp) printf("%d ", i); printf("\n");
       return dp[dp.size()-1];
       */
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
    dp[0][0] = 1;
    for (int i = 1; i < n; ++i) dp[i][0] = (dp[i-1][0] == 0 || grids[i][0] == 1) ? 0 : 1;
    for (int i = 1; i < m; ++i) dp[0][i] = (dp[0][i-1] == 0 || grids[0][i] == 1) ? 0 : 1;

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (grids[i][j] == 1) dp[i][j] = 0;
            else dp[i][j] = dp[i][j-1] + dp[i-1][j];
        }
    }

    return dp[n-1][m-1];
}

// #64
int min_path_sum(std::vector<std::vector<int>>& grids) {
    int m = grids.size();
    if (m == 0) return 0;

    int n = grids[0].size();

    // note: padding may lead to wrong cost at row 1 and column 1
    //std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1, 0));
    //for (int i = 1; i <=m; ++i)
    //  for (int j = 1; j <= n; ++j)
    //      dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + grids[i-1][j-1];
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

    dp[0][0] = grids[0][0];
    for (int i = 1; i < m; ++i) dp[i][0] = dp[i-1][0] + grids[i][0];
    for (int i = 1; i < n; ++i) dp[0][i] = dp[0][i-1] + grids[0][i];

    for (int i = 1; i < m; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + grids[i-1][j-1];
        }
    }

    return dp[m-1][n-1];
}
