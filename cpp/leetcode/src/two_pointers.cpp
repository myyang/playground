#include <vector>
#include <iostream>
#include <algorithm> // std::max, std::min
#include <string>
#include <locale> // std::isalpha
#include <utility> // std::swap

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
        else if (j > 0 && typed[j-1] == typed[j])
            ++j;
        else
            return false;
    }

    while (j < typed.size() && typed[j] == typed[j-1]) ++j;
    return i == name.size() && j == typed.size();
}
