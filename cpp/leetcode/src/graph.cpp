#include <vector>
#include <functional>


// #200
int number_of_islands(std::vector<std::vector<int>>& nums)
{
    int ans = 0;

    std::function<void(int, int, int, int)> dfs = [&](int i, int j, int m, int n)
    {
        if (i < 0 || j < 0 || i >= m || j >= n || !nums[i][j]) return;

        nums[i][j] = 0;
        dfs(i-1, j, m, n);
        dfs(i+1, j, m, n);
        dfs(i, j-1, m, n);
        dfs(i, j+1, m, n);
    };

    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = 0; j < nums[0].size(); ++j)
        {
            if (!nums[i][j]) continue;
            ++ans;
            dfs(i, j, nums.size(), nums[0].size());
        }
    }

    return ans;
}

// #547
int find_circule_number(std::vector<std::vector<int>>& nums)
{
    int ans = 0;
    if (nums.empty()) return ans;

    int n = nums.size();

    std::function<void(int)> dfs = [&](int cur)
    {
        // be careful this range
        for (int i = 0; i < n; ++i)
        {
            if (!nums[cur][i]) continue;
            nums[cur][i] = nums[i][cur] = 0;
            dfs(i);
        }
    };

    for (int i = 0; i < nums.size(); ++i)
    {
        if (!nums[i][i]) continue;
        ++ans;
        // pass start point is enough
        dfs(i);
    }

    return ans;
}

// #733
std::vector<std::vector<int>>& flood_fill(std::vector<std::vector<int>>& nums, int sc, int sr, int new_color)
{

    // suppose nums is not empty;
    int old_color = nums[sc][sr];
    int m = nums.size(), n = nums[0].size();

    std::function<void(int c, int r)> dfs = [&](int c, int r)
    {
        if (c < 0 || r < 0 || c >= m || r >= n || nums[c][r] != old_color) return;

        nums[c][r] = new_color;
        dfs(c-1, r);
        dfs(c+1, r);
        dfs(c, r-1);
        dfs(c, r+1);
    };

    dfs(sc, sr);
    return nums;
}
