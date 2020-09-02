#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <functional>
#include <cctype>
#include <numeric>  // std::accumulate
#include <unordered_map>

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
        // check cur is not empty
        if (cur != "") res.push_back(cur);
        return;
    }

    if (digits[idx] == '1') // note that '1' is empty
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

    // check size not empty because there maybe 0 elements
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
        std::set<std::vector<int>>& res)  // use set to remove de deuplicated
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
            // prevent use same nums
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

// #784
std::vector<std::string> letter_case_permutation(std::string raw)
{
    std::vector<std::string> res;
    if (raw.size() == 0) return res;

    std::function<void(int)> dfs = [&](int d)
    {
        if (d == raw.size())
        {
            res.push_back(raw);
            return;
        }

        dfs(d+1); // dfs first make less wrong

        // don't check alpha before walk deeper
        // such as
        // if ( std::isalpha(raw[d] )
        // {
        //  raw[d] ^= (1 << 5);
        //  dfs(d+1);
        //  raw[d] ^= (1 << 5);
        //  dfs(d+1);  // this should move out of block as follow
        // }
        //  //dfs(d+1);

        if ( !std::isalpha(raw[d]) ) return;

        raw[d] ^= (1 << 5);
        dfs(d+1);
        raw[d] ^= (1 << 5);
    };

    dfs(0);

    return res;
}

// #22
std::vector<std::string> generate_parenthes(int n)
{
    std::vector<std::string> res;
    if (n == 0) return res;

    std::string cur;

    std::function<void(int, int)> dfs = [&](int l, int r)
    {
        if (l == 0 && r == 0)
        {
            res.push_back(cur);
            return;
        }

        if (l > r) return; // pruning invalid case

        if (l > 0)
        {
            cur += "(";
            dfs(l-1, r);
            cur.pop_back();
        }

        if (r > 0)
        {
            cur += ")";
            dfs(l, r-1);
            cur.pop_back();
        }
    };

    dfs(n, n);

    return res;
}

// #301
std::vector<std::string> remove_invalid_parenthes(std::string raw)
{
    std::vector<std::string> res;
    if (raw.size() == 0) return res;

    int lp = 0, rp = 0;
    for (auto c: raw)
    {
        lp += (c == '(');
        if (lp == 0)
            rp += (c == ')');
        else
            lp -= ( c == ')');
    }

    std::function<bool(std::string)> is_valid = [](std::string s) {
        int p = 0;
        for (char c: s)
        {
            if (c == '(') ++p;
            if (c == ')') --p;
            if (p < 0) return false;
        }

        return p == 0 ? true: false;
    };

    std::function<void(std::string, int, int, int)> dfs = [&](std::string s, int start, int l, int r)
    {

        if (l == 0 && r == 0) {
            // check valid result is required
            // the "()())()" case would get
            //  { "(())()", "()()()", "()())(" } with an extra wrong answers
            if (is_valid(s)) res.push_back(s);
            return;
        }

        for (int i = start; i < s.size(); ++i)
        {
            if (i != start && s[i] == s[i-1]) continue;

            if (s[i] == '(' || s[i] == ')')
            {
                std::string curr = s;
                curr.erase(i, 1);
                if (r > 0 && s[i] == ')')
                    dfs(curr, i, l, r-1);
                if (l > 0 && s[i] == '(')
                    dfs(curr, i, l-1, r);
            }
        }
        // following is wrong implementation with correct idea
        // check:
        //  * std::string erase usage
        //  * the dfs next start value should be related to i
        //  * the next start doesn't need +1 because we erase the string
        //
        //if (l > 0 && cur[i] == '(')
        //{
        //    std::string tmp = cur;
        //    tmp.erase(i, i);
        //    dfs(tmp, start+1, l-1, r);
        //}

        //if (r > 0 && cur[i] == ')')
        //{
        //    std::string tmp = cur;
        //    tmp.erase(i, i);
        //    dfs(tmp, start+1, l, r-1);
        //}

    };

    dfs(raw, 0, lp, rp);

    return res;
}

// #79
bool search_word(std::vector<std::vector<char>>& board, std::string word)
{
    std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    std::function<bool(int, int, int)> msearch = [&](int x, int y, int i)
    {
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size()) return false;

        if (i == word.size()) return true;

        if (board[x][y] == word[i]) {
            char tmp = board[x][y];
            board[x][y] = '#'; // set invalid char to prevent repeatly visiting

            bool r = msearch(x + dirs[0][0], y + dirs[0][1], i + 1) ||
            msearch(x + dirs[1][0], y + dirs[1][1], i + 1) ||
            msearch(x + dirs[2][0], y + dirs[2][1], i + 1) ||
            msearch(x + dirs[3][0], y + dirs[3][1], i + 1);

            board[x][y] = tmp;
            return r;
        }

        return false;
    };

    for (int i = 0; i < board.size(); ++i)
        for (int j = 0; j < board[0].size(); ++j)
            if (msearch(i, j, 0)) return true;
    return false;
}

// #698
bool partition_k_equal_sum_subset(std::vector<int>& nums, int k)
{
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if ((sum % k) != 0) return false;

    std::sort(nums.begin(), nums.end());

    int target = sum / k;

    std::function<bool(int, int, int, int)> dfs = [&](int cur, int idx, int k, int used)
    {
        // if nums size is 3
        // all used would be 1000 (bin) - 1, 0111
        if (k == 0) return used == (1 << nums.size()) - 1;

        for (int i = 0; i < nums.size(); ++i)
        {
            // careful this & not &&
            if (used & (1 << i)) continue;

            int t = cur - nums[i];
            if (t < 0) break;

            int new_used = used | (1 << i);

            if (t == 0 && dfs(target, 0, k-1, new_used)) return true;
            else if (dfs(t, 0, k, new_used)) return true;
        }

        return false;
    };

    return dfs(target, 0, k, 0);
}

// #201
std::vector<int> diff_ways_to_add_parentheses(std::string input)
{
    std::vector<int> res;
    if (input.size() == 0) return res;

    std::function<int(int, int)> add = [](int a, int b) { return a + b; };
    std::function<int(int, int)> sub = [](int a, int b) { return a - b; };
    std::function<int(int, int)> mul = [](int a, int b) { return a * b; };

    std::unordered_map<std::string, std::vector<int>> m_;

    std::function<std::vector<int>(std::string&)> dfs = [&](std::string& raw)
    {
        if (m_.count(raw)) return m_[raw];

        std::vector<int> ans;

        for (int i = 0; i < raw.size(); ++i)
        {
            char op = raw[i];

            if (op == '+' || op == '-' || op == '*')
            {
                std::string left = raw.substr(0, i);
                std::string right = raw.substr(i+1);

                std::vector<int> l = dfs(left);
                std::vector<int> r = dfs(right);

                std::function<int(int, int)> f;

                switch(op)
                {
                    case '+': f = add; break;
                    case '-': f = sub; break;
                    case '*': f = mul; break;
                }

                for (int a: l)
                    for (int b: r)
                        ans.push_back(f(a,b));
            }

        }

        if (ans.empty())
            ans.push_back(stoi(raw));

        m_[raw].swap(ans);
        return m_[raw];
    };

    return dfs(input);
}

// #93
std::vector<std::string> restore_ip_addresses(std::string input)
{
    std::vector<std::string> res;
    if (input.size() == 0) return res;

    std::function<void(int, std::string, std::string)> dfs = [&](int d, std::string left, std::string cur)
    {
        if (d == 4)
        {
            if (left.size() == 0) res.push_back(cur);
            return;
        }

        int l = left.length();
        // empty length would not enter loop
        for (int i = 1; i <= std::min(3, left[0] == '0' ? 1 : l); ++i)
        {
            std::string sub = left.substr(0, i);
            // pruning to reduce redundant computing
            if (i == 3 && stoi(sub) > 255) return;
            dfs(d+1, left.substr(i), cur + (d==0 ? "" : ".") + sub);

        }
    };

    dfs(0, input, "");

    return res;
}

// #131
std::vector<std::vector<std::string>> palindrome_partition(std::string input)
{
    std::vector<std::vector<std::string>> res;
    if (input.size() == 0) return res;

    std::function<bool(std::string)> is_palindrome = [](std::string s)
    {
        if (s.size() <= 1) return true;

        int l = 0, r = s.size()-1;
        while (l < r)
            if (s[l++] != s[r--]) return false;
        return true;
    };

    std::vector<std::string> cur;

    std::function<void(int)> dfs = [&](int start)
    {
        if (start == input.size())
        {
            res.push_back(cur);
            return;
        }

        // count left length
        for (int i = 0; i < input.size() - start + 1; ++i)
        {
            std::string sub = input.substr(start, i);
            if (sub == "" || !is_palindrome(sub)) continue;

            cur.push_back(sub);
            dfs(start+i);
            cur.pop_back();
        }
    };

    dfs(0);

    return res;
}

// #282
std::vector<std::string> expression_add_operator(std::string input, int target)
{
    std::vector<std::string> res;
    if (input.size() == 0) return res;

    long l_target = target;
    std::function<void(int, long, long, std::string)> dfs = [&](int start, long pre, long cur, std::string exp)
    {
        if (start == input.size())
        {
            //printf("start: %d, pre: %ld, cur: %ld, exp: %s\n", start, pre, cur, exp.c_str());
            if (cur == l_target) res.emplace_back(exp);
            return;
        }

        for (int i = 0; i < input.size() - start + 1; ++i)
        {
            std::string sub = input.substr(start, i);
            if (sub == "") continue;
            if (sub[0] == '0' && sub.size() > 1) break; // 0[1-9]+ is invalid

            long sub_num = stol(sub);

            // first is corner case
            if (start == 0)
            {
                dfs(i, sub_num, sub_num, sub);
                continue;
            }

            dfs(start+i, sub_num, cur + sub_num, exp + '+' + sub);
            dfs(start+i, -sub_num, cur - sub_num, exp + '-' + sub);
            dfs(start+i, pre * sub_num, cur - pre + pre * sub_num, exp + '*' + sub);
        }

    };

    dfs(0, 0, 0, "");

    return res;
}

// #842
std::vector<int> fib_seq(std::string input)
{
    std::vector<int> res;
    if (input.size() == 0) return res;

    std::vector<int> cur;

    std::function<void()> print_cur = [&]() {
        std::cout << "size: " << cur.size() << " cur: ";
        for (auto c: cur) std::cout << c << ", ";
        std::cout << std::endl << std::endl;
    };

    std::function<bool()> is_valid_cur = [&]() {
        if (cur.size() < 3) return false;

        for (int i = 2; i < cur.size(); ++i)
        {
            if (cur[i] != cur[i-1] + cur[i-2]) return false;
        }
        return true;
    };

    std::function<void(int)> dfs = [&](int start)
    {

        if (start == input.size())
        {
            if (is_valid_cur()) res = cur;
            return;
        }

        for (int i = 1; i <= input.size() - start; ++i)
        {
            std::string sub = input.substr(start, i);
            int sub_num = std::stoi(sub);

            cur.push_back(sub_num);
            if (cur.size() < 3) dfs(start + i);
            else
            {
                int n = cur.size()-1;
                if (cur[n-1] + cur[n-2] == sub_num) dfs(start+i);
            }
            cur.pop_back();

        }
    };

    dfs(0);

    return res;
}
