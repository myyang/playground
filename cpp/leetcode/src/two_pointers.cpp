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
        while (c-nums[r] >= 0 && l <= r) c -= nums[r--];
        while (c-nums[l] >= 0 && l <= r) c -= nums[l++];
        ++res;
    }

    return res;
}
