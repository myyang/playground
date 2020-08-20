#include<vector>

// #35
int search_insert_position(std::vector<int>& nums, int target)
{
    int l = 0, r = nums.size();
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
    int l = 0, r = nums.size();
    while (l < r )
    {
        int m = l + (r-l) / 2;
        if (nums[m] < target)
            l = m + 1;
        else
            r = m;
    }
    res.push_back((l == nums.size() || nums[l] != target) ? -1 : l);

    // last
    l = 0;
    r = nums.size();
    while (l < r)
    {
        int m = l + (r-l) / 2;
        if (nums[m] > target)
            r = m;
        else
            l = m + 1;
    }
    --l;
    res.push_back((l == 0 || nums[l] != target) ? -1 : l);

    return res;
}

// #153,154
int search_min_in_rotated_array(std::vector<int>& nums)
{
    int l = 0, r = nums.size()-1;
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
