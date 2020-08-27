#include<vector>
#include<algorithm>
#include<numeric>

// #35
int search_insert_position(std::vector<int>& nums, int target)
{
    int l = 0, r = nums.size(); // [l, r)
    while (l < r)
    {
        int m = l + (r-l) / 2;
        if (nums[m] > target)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

// #34
std::vector<int> search_range(std::vector<int>& nums, int target)
{
    std::vector<int> res;
    // first
    // [l, r)
    int l = 0, r = nums.size();
    while (l < r )
    {
        int m = l + (r-l) / 2;
        if (nums[m] < target) // move to first equal
            l = m + 1;
        else
            r = m; // remove duplicated greater equal
    }
    res.push_back((l == nums.size() || nums[l] != target) ? -1 : l);

    // last
    // [l, r)
    l = 0;
    r = nums.size();
    while (l < r)
    {
        int m = l + (r-l) / 2;
        if (nums[m] > target) // move to first greater
            r = m;
        else
            l = m + 1;  // remove duplicated equal
    }
    --l;
    res.push_back((l == 0 || nums[l] != target) ? -1 : l);

    return res;
}

// #153,154
int search_min_in_rotated_array(std::vector<int>& nums)
{
    int l = 0, r = nums.size()-1; // [l, r]
    while (l < r)
    {
        int m = l + (r -l) / 2;
        if (nums[m] > nums[r])
            l = m + 1;
        else
            r = m;
    }
    return l;
}

// #875
int koko_eating_bananas(std::vector<int>& nums, int H)
{
    int l = 1, r = *max_element(nums.begin(), nums.end()) + 1; // [l, r)
    while (l < r) {
        int h = 0;
        int m = l + (r-l) / 2;
        for (int n: nums)
            h += (n + m -1) / m;  // == ceil(n/m)
        if (h > H)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

// #1011
int capacity_to_ship_pkgs(std::vector<int>& nums, int D)
{
    // [l, r)
    int l = *std::max_element(nums.begin(), nums.end()),
        r = std::accumulate(nums.begin(), nums.end(), 0) + 1;

    while (l < r)
    {
        int m = l + (r-l) / 2;
        int t = 0;
        int d = 1;
        for (int n: nums)
        {
            if ((t += n) > m)
            {
                t = n; // the execeed part can't be ship in same date, set next day base as whole package
                ++d;
            }
        }

        if (d > D)
            l = m + 1;
        else
            r = m;
    }
    return l;
}
