#include <functional>
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

// #120
//    [2],             [2],
//   [3,4],           [5,6],
//  [5,6,1],         [10,11,7],
// [8,9,10,11]      [18,19,17,18],
int min_total(std::vector<std::vector<int>>& t) {
    int n = t.size();

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            if (i == 0 && j == 0) continue;
            if (j == 0) t[i][j] += t[i-1][j];
            else if (i == j) t[i][j] += t[i-1][j-1];
            else t[i][j] += std::min(t[i-1][j], t[i-1][j-1]);
        }
    }

    return *std::min_element(std::begin(t.back()), std::end(t.back()));
}

// #174
int min_hp(std::vector<std::vector<int>>& t) {
    int m = t.size(), n = t[0].size();

    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1, INT_MAX));
    dp[m][n-1] = dp[m-1][n] = 1;

    for (int i = m-1; i > -1; --i)
        for (int j = n -1; j > -1; --j)
            dp[i][j] = std::max(1, std::min(dp[i+1][j], dp[i][j+1]) - t[i][j]);

    return dp[0][0];
}

// #85
int max_rectangle(std::vector<std::vector<int>>& t) {
    int m = t.size();
    if (m == 0) return 0;
    int n = t[0].size();


    std::vector<std::vector<int>> dp(m, std::vector<int>(n));

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            dp[i][j] = t[i][j] ? (j == 0 ? 1 : dp[i][j-1] + 1) : 0;

    int ans = 0;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int len = INT_MAX;
            for (int k = i; k < n; ++k)
            {
                len = std::min(len, dp[k][j]);
                if (len == 0) break;
                ans = std::max(len * (k - i + 1), ans);
            }
        }
    }

    return ans;
}

// #221
// [1, 0]
// [2, 3]
//
// [0, 0, 0]
// [0, 1, 0]
// [0, 3, 6]
RangeQuery2D::RangeQuery2D(std::vector<std::vector<int>>& t) {
    int m = t.size();
    if (m == 0) return;
    int n = t[0].size();

    std::vector<std::vector<int>> tmp(m+1, std::vector<int>(n+1));
    dp = tmp;

    // NOTE this iteration loop
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            dp[i][j] = t[i-1][j-1] - dp[i-1][j-1] + dp[i-1][j] + dp[i][j-1];
        }
    }

}

int RangeQuery2D::get_sum(int x1, int y1, int x2, int y2)  {
    return dp[x1][y1] - dp[x1][y2+1] - dp[x2+1][y1] + dp[x2+1][y2+1];
}

// #1277
int count_sqr(std::vector<std::vector<int>>& t) {
    int m = t.size();
    int n = t[0].size();

    std::vector<std::vector<int>> dp(m, std::vector<int>(n));

    int ans = 0;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            dp[i][j] = t[i][j];
            if (i && j && dp[i][j])
                dp[i][j] = std::min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
            ans += dp[i][j];
        }
    }

    return ans;
}
