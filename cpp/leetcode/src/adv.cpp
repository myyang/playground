#include <vector>
#include <deque>

std::vector<int> sliding_maximum(std::vector<int>& nums, int k)
{
    std::deque<int> idx;
    std::vector<int> res;

    for (int i = 0; i < nums.size(); ++i)
    {
        while (!idx.empty() && nums[i] > nums[idx.back()]) idx.pop_back();
        idx.push_back(i);

        if (i-k+1 >= 0) res.push_back(nums[idx.front()]);

        // this should put after push, or the first window would be cleared.
        // remember to check empty queue if using while
        while (!idx.empty() && idx.front() <= i-k+1) idx.pop_back();
        // or use if as:
        // if (idx.front() <= i-k+1) idx.pop_back();
    }

    return res;
}
