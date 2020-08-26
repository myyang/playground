#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <functional>

// #17
void letter_combination_dfs(
        int idx,
        std::string digits,
        std::string cur,
        std::vector<std::vector<int>>& char_map,
        std::vector<std::string>& res)
{
    if (idx == digits.size())
    {
        if (cur != "") res.push_back(cur);
        return;
    }

    if (digits[idx] == '1')
    {
        letter_combination_dfs(idx+1, digits, cur, char_map, res);
        return;
    }

    for (auto c: char_map[digits[idx]-'0'])
    {
            cur += c;
            letter_combination_dfs(idx+1, digits, cur, char_map, res);
            cur.pop_back();
    }
}

std::vector<std::string> letter_combination(std::string digits)
{
    std::vector<std::string> res;
    if (digits.empty()) return res;

    std::vector<std::vector<int>> char_map(10);
    char_map[0] = {' '};
    char_map[1] = {};
    char_map[2] = {'a', 'b', 'c'};
    char_map[3] = {'d', 'e', 'f'};
    char_map[4] = {'g', 'h', 'i'};
    char_map[5] = {'j', 'k', 'l'};
    char_map[6] = {'m', 'n', 'o'};
    char_map[7] = {'p','q','r','s'};
    char_map[8] = {'t','u','v'};
    char_map[9] = {'w','x','y','z'};

    letter_combination_dfs(0, digits, "", char_map, res);

    return res;
}

// #39
void combination_sum_dfs(
        int idx,
        int target,
        std::vector<int>& nums,
        std::vector<int>& cur,
        std::vector<std::vector<int>>& res)
{

    if (target == 0 && cur.size() != 0) {
        res.push_back(cur);
        return;
    }

    for (int i = idx; i < nums.size(); ++i)
    {
        cur.push_back(nums[i]);
        combination_sum_dfs(i+1, target - nums[i], nums, cur, res);
        cur.pop_back();
    }
}

std::vector<std::vector<int>> combination_sum(std::vector<int>& nums, int target)
{
    std::vector<std::vector<int>> res;
    if (nums.size() == 0) return res;

    std::sort(nums.begin(), nums.end());

    std::vector<int> cur;
    combination_sum_dfs(0, target, nums, cur, res);

    return res;
}

// #40
void combination_sum_dfs_de_dup(
        int idx,
        int target,
        std::vector<int>& nums,
        std::vector<int>& cur,
        std::set<std::vector<int>>& res)
{
    if (target == 0 && cur.size() != 0)
    {
        res.emplace(cur);
        return;
    }

    for (int i = idx; i < nums.size(); ++i)
    {
        cur.push_back(nums[i]);
        combination_sum_dfs_de_dup(i+1, target - nums[i], nums, cur, res);
        cur.pop_back();
    }
}

std::vector<std::vector<int>> combination_sum_de_dup(std::vector<int>& nums, int target)
{
    std::vector<std::vector<int>> res;
    if (nums.size() == 0) return res;

    std::sort(nums.begin(), nums.end());

    std::set<std::vector<int>> res2;

    std::vector<int> cur;
    combination_sum_dfs_de_dup(0, target, nums, cur, res2);

    for (auto r: res2) res.push_back(r);

    return res;
}

// #216
std::vector<std::vector<int>> combination_sum_3(int k, int n)
{
    std::vector<std::vector<int>> res;
    if (k == 0 || n == 0) return res;

    std::vector<int> cur;
    std::function<void(int, int)> dfs = [&](int d, int target)
    {
        if (target <= 0)
        {
            if (target == 0 && cur.size() == k) res.push_back(cur);
            return;
        }

        for (int i = d; i < 10; ++i)
        {
            cur.push_back(i);
            dfs(i+1, target - i);
            cur.pop_back();
        }
    };

    dfs(1, n);
    return res;
}

// #46
std::vector<std::vector<int>> permutations(std::vector<int>& nums)
{
    std::vector<std::vector<int>> res;
    int n = nums.size();
    if (n == 0) return res;

    std::vector<bool> used(n, false);
    std::vector<int> cur;

    std::function<void()> dfs = [&]()
    {
        if (cur.size() == n)
        {
            res.push_back(cur);
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            if (used[i]) continue;

            cur.push_back(nums[i]);
            used[i] = true;

            dfs();

            cur.pop_back();
            used[i] = false;
        }
    };

    dfs();
    return res;
}

// #47
std::vector<std::vector<int>> permutations_de_dup(std::vector<int>& nums)
{
    std::vector<std::vector<int>> res;
    int n = nums.size();
    if (n == 0) return res;

    std::vector<bool> used(n, false);
    std::vector<int> cur;

    std::function<void()> dfs = [&]()
    {
        if (cur.size() == n)
        {
            res.push_back(cur);
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;

            cur.push_back(nums[i]);
            used[i] = true;

            dfs();

            cur.pop_back();
            used[i] = false;
        }
    };

    dfs();
    return res;
}
