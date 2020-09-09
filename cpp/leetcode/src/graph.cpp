#include <vector>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <queue>
#include <tuple>


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

// #827
int making_a_large_land(std::vector<std::vector<int>>& nums)
{
    int ans = 0;
    if (nums.empty()) return ans;

    int color = 1, m = nums.size(), n = nums[0].size();
    std::unordered_map<int, int> areas;

    std::function<void()> print_nums = [&](){
        for (auto r: nums)
        {
            for (auto n: r) printf("%d ", n);
            printf("\n");
        }
    };

    std::function<void()> print_areas = [&](){
        for (auto kv: areas)
            printf("%d: %d\n", kv.first, kv.second);
    };

    // count land area and render
    std::function<int(int, int)> count_area = [&](int i, int j)
    {
        if (i < 0 || j < 0 || i >= m || j >= n || nums[i][j] != 1) return 0;

        nums[i][j] = color;
        return 1 + count_area(i-1, j) + count_area(i+1, j) + count_area(i, j-1) + count_area(i, j+1);
    };

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            ++color;
            areas[color] = count_area(i, j);
            // this comparsion is required to prevent no connect point works, (all lands, all sea)
            // get max island directly.
            ans = std::max(ans, areas[color]);
        }
    }
    //print_nums();
    //print_areas();

    // try connect
    std::function<int(int, int)> get_color = [&](int i, int j)
    {
        return (i < 0 || j < 0 || i >= m || j >= n) ? 0 : nums[i][j];
    };
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // be careful this condition
            if (nums[i][j] == 0) {
                int area = 1;
                // vector doesn't works, check 2nd test render as follow:
                // 2 2 0 5
                // 0 0 5 5
                // 10 0 0 5
                // nums[0][2] would add island 5 twice.
                // std::vector<int> colors =  {get_color(i-1, j), get_color(i+1, j), get_color(i, j-1), get_color(i, j+1)};
                std::set<int> colors = {get_color(i-1, j), get_color(i+1, j), get_color(i, j-1), get_color(i, j+1)};
                for (int c: colors)
                {
                    area += areas[c];
                }
                ans = std::max(ans, area);
            }
        }
    }
    return ans;
}

// #1162
int as_far_as_possible_from_land(std::vector<std::vector<int>>& nums)
{
    int ans = -1;
    if (nums.empty()) return ans;

    int m = nums.size(), n = nums[0].size();

    std::queue<std::tuple<int, int, int>> walks;
    // visited matrix is required to prevent still re visited.
    std::vector<std::vector<bool>> visited(m, std::vector(n, false));


    // insert land
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (nums[i][j] == 1) walks.emplace(std::make_tuple(i, j, 0));
        }
    }

    // search with bfs
    while (walks.size())
    {
        int i, j, walk;
        std::tie(i, j , walk) = walks.front();
        walks.pop();

        if (i < 0 || j < 0 || i >= m || j >= n || visited[i][j]) continue;

        visited[i][j] = true;

        if (nums[i][j] == 0) ans = std::max(ans, walk);

        walks.emplace(std::make_tuple(i-1, j, walk+1));
        walks.emplace(std::make_tuple(i+1, j, walk+1));
        walks.emplace(std::make_tuple(i, j-1, walk+1));
        walks.emplace(std::make_tuple(i, j+1, walk+1));
    }

    return ans;
}

// #841
bool keys_and_rooms(std::vector<std::vector<int>>& nums)
{
    if (nums.empty()) return false;

    std::set<int> visited;

    std::function<void(int)> dfs = [&](int i)
    {
        if (visited.count(i)) return;

        visited.emplace(i);

        for (auto n: nums[i]) dfs(n);
    };

    dfs(0);
    return visited.size() == nums.size();
}

// #207
bool can_finish_course(int courseNum, std::vector<std::vector<int>>& nums)
{
    if (courseNum <= 0) return false;

    // build graph
    std::vector<std::vector<int>> graph(courseNum); // NOTE this graph init way
    for (auto num: nums)
        graph[num[0]].push_back(num[1]);

    // state: 0 = not_visit, 1 = visting, 2 = visited
    std::vector<int> visit(courseNum, 0);

    std::function<bool(int)> cycle = [&](int course)
    {
        if (visit[course] == 1) return true;
        if (visit[course] == 2) return false;

        visit[course] = 1;

        // be careful this for loop cycle graph retrieve
        for (auto n: graph[course])
            if (cycle(n)) return true;

        visit[course] = 2;
        return false;
    };

    for (int i = 0; i < courseNum; ++i)
        if (cycle(i)) return false;

    return true;
}
