#include <vector>
#include <iostream>
#include <algorithm> // std::max, std::min
#include <string>
#include <locale> // std::isalpha
#include <utility> // std::swap
#include <cstdlib> // std::abs(int)
#include <map>
#include <functional> // std::function

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
        // remember to move pointer every run
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

// #917
std::string reverse_only_letters(std::string raw)
{
    int n = raw.size();
    if (n == 0) return "";

    int l = 0, r = n-1;
    while (l < r)
    {

        if (std::isalpha(raw[l]) && std::isalpha(raw[r]))
        {
            std::swap(raw[l++], raw[r--]);
        }
        else
        {
            // don't use while for continuous moving
            // correctly move 1 step each time
            if (!std::isalpha(raw[l])) ++l;
            if (!std::isalpha(raw[r])) --r;
        }
    }

    return raw;
}

// #925
bool long_pressed_name(std::string name, std::string typed)
{
    int i = 0, j = 0;
    while (i < name.size() && j < typed.size())
    {
        if (name[i] == typed[j])
        {
            ++i;
            ++j;
        }
        // this is second condition so compare typed for repeated is ok
        else if (j > 0 && typed[j-1] == typed[j])
            ++j;
        else
            return false;
    }

    // last repeated
    while (j < typed.size() && typed[j] == typed[j-1]) ++j;
    return i == name.size() && j == typed.size();
}

// #977
std::vector<int> squares_of_sorted_array(std::vector<int>& nums)
{
    int n = nums.size();
    std::vector<int> res;
    if (n == 0) return res;

    int l = 0, r = n-1;
    while (l < r)
    {
        if (std::abs(nums[l]) > std::abs(nums[r]))
        {
            res.push_back(nums[l] * nums[l]);
            ++l;
        }
        else
        {
            res.push_back(nums[r] * nums[r]);
            --r;
        }
    }
    res.push_back(nums[l] * nums[l]);

    std::reverse(res.begin(), res.end());
    return res;
}

// #992
int subarray_with_k_diff(std::vector<int>& nums, int k)
{
   int n = nums.size();
   if (n == 0) return n;

   // count subarray numbers with distinct ik numbers
   std::function<int(int)> subarrays = [&](int ik)
   {
       std::vector<int> count(n+1);
       int ans = 0, i = 0;

       for (int j = 0; j < n; ++j)
       {
           if (count[nums[j]]++ == 0) --ik;

           while (ik < 0)
           {
               if (--count[nums[i++]] == 0) ++ik;
           }

           ans += j - i + 1;
       }

       return ans;
   };

   return subarrays(k) - subarrays(k-1);
}

// #885
int boats_to_save_people(std::vector<int>& nums, int k)
{
    int n = nums.size();
    if (n == 0) return n;

    std::sort(nums.begin(), nums.end());
    int l = 0, r = n-1, res = 0;

    while (l <= r)
    {
        int c = k;
        // not that l <= r is required to prevent over counting
        while (c-nums[r] >= 0 && l <= r) c -= nums[r--];
        while (c-nums[l] >= 0 && l <= r) c -= nums[l++];
        ++res;
    }

    return res;
}

// #986
std::vector<std::vector<int>> intersections_of_lists(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B)
{
    std::vector<std::vector<int>> res;
    int i = 0, j = 0;
    while (i < A.size() && j < B.size())
    {
        // find directly with min max
        int start = std::max(A[i][0], B[j][0]);
        int end = std::min(A[i][1], B[j][1]);

        // equal is acceptable
        if (start <= end) res.push_back({start, end});

        // move smaller list forward
        if (A[i][1] < B[j][1]) ++i;
        else ++j;
    }
    return res;
}

// #167
std::vector<int> two_sum_2(std::vector<int> nums, int k)
{
    std::vector<int> res;
    int l = 0, r = nums.size()-1;

    while (l < r)
    {
        int s = nums[l] + nums[r];
        if (s == k)
        {
            res.push_back(l);
            res.push_back(r);
            break;
        }

        if (s < k) ++l;
        else --r;
    }

    return res;
}

// #15
std::vector<std::vector<int>> three_sum(std::vector<int> nums, int k)
{
    std::vector<std::vector<int>> res;

    std::sort(nums.begin(), nums.end());

    int n = nums.size();
    for (int i = 0; i < n-2; ++i) // 1st impl n-2 is written as n-3
    {
        int l = i+1, r = n-1, t = k - nums[i];
        while (l < r)
        {
            int s = nums[l] + nums[r];

            if (s == t)
            {
                res.push_back({i, l++, r--});
                while (l < r && nums[l] == nums[l-1]) ++l;
                while (l < r && nums[r] == nums[r+1]) --r;
            }
            else if (s < t) ++l;  // 1st implementation t is written as k,
            else --r;
        }
    }

    return res;
}
