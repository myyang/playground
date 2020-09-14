#include <vector>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <queue>
#include <tuple>
#include <string>
#include <numeric>
#include <string>
#include <unordered_set>


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

// #210
std::vector<int> can_finish_course_order(int courseNum, std::vector<std::vector<int>>& nums)
{
    if (courseNum <= 0) return {};

    std::vector<std::vector<int>> graph(courseNum);
    for (auto num: nums)
        graph[num[0]].push_back(num[1]);

    // state: 0 = not_visit, 1 = visting, 2 = visited
    std::vector<int> visit(courseNum);
    std::vector<int> ans;

    std::function<bool(int)> cycle = [&](int course)
    {
        if (visit[course] == 1) return true;
        if (visit[course] == 2) return false;

        visit[course] = 1;
        for (auto i: graph[course])
            if (cycle(i)) return true;

        visit[course] = 2;
        ans.push_back(course);
        return false;
    };

    for (int i = 0; i < courseNum; ++i)
        if (cycle(i)) return {};

    std::reverse(ans.begin(), ans.end());

    return ans;
}

// #1202
std::string swap_to_smallest_string(std::string s, std::vector<std::vector<int>>& pairs)
{
    if (s.empty() || pairs.empty()) return s;

    int n = s.length();
    std::vector<int> group(n, 0);

    for (int i = 0; i < n; ++i)
        group[i] = i;

    std::function<int(int)> find = [&](int i)
    {
        if (group[i] != i)
            group[i] = find(group[i]);
        return group[i];
        // union find oneline
        //return group[i] == i ? i : group[i] == find(group[i]);
    };

    for (auto pair: pairs)
    {
        // first find funcion is correct
        group[find(pair[0])] = find(pair[1]);
        //group[pair[0]] = find(pair[1]);
    }

	/*
	printf("group: ");
	for (int i = 0; i < n; ++i) printf("%d ", group[i]);
	printf("\n");
	*/

    std::vector<std::vector<char>> chars(n);
    std::vector<std::vector<int>> idxs(n);

    for (int i = 0; i < n; ++i)
    {
		// XXX: get id with find is important
		int id = find(i);
        chars[id].push_back(s[i]);
        idxs[id].push_back(i);
    }

    for (int i = 0; i < n; ++i)
    {
        std::sort(chars[i].begin(), chars[i].end());
        for (int j = 0; j < idxs[i].size(); ++j)
            s[idxs[i][j]] = chars[i][j];
    }

    return s;
}

// #399
std::vector<double> calcEq_dfs(
        std::vector<std::vector<std::string>> eqs,
        std::vector<double>& values,
        std::vector<std::vector<std::string>> queries)
{
    std::unordered_map<std::string, std::unordered_map<std::string, double>> g;
    for (int i = 0; i < eqs.size(); ++i)
    {
        std::string a = eqs[i][0], b = eqs[i][1];
        double k = values[i];
        g[a][b] = k;
        g[b][a] = 1.0 / k;
    }

    std::function<double(std::string, std::string, std::unordered_set<std::string>&)> divide = [&](
            std::string a, std::string b, std::unordered_set<std::string>& visited)
                {
                    if (a == b) return 1.0;
                    visited.emplace(a);

                    for (auto pair: g[a])
                    {
                        std::string c = pair.first;
                        if (visited.count(c)) continue;
                        double d = divide(c, b, visited);
                        if (d > 0) return d * g[a][c];
                    }
                    return -1.0;
                };

    std::vector<double> res;
    for (int i = 0; i < queries.size(); ++i)
    {
        std::string x = queries[i][0], y = queries[i][1];
        if (!g.count(x) || !g.count(y))
        {
            res.push_back(-1.0);
            continue;
        }

        std::unordered_set<std::string> visited;
        res.push_back(divide(x, y, visited));
    }

    return res;
}

std::vector<int> find_final_state_nodes(std::vector<std::vector<int>>& graph)
{
    std::vector<int> res;
    if (graph.empty()) return res;

    enum State {UNKNOWN, VISITING, SAFE, UNSAFE};

    std::vector<State> states(graph.size(), UNKNOWN);

    std::function<State(int)> dfs = [&](int i)
    {
        if (states[i] == VISITING) return states[i] = UNSAFE;
        if (states[i] != UNKNOWN) return states[i];

        states[i] = VISITING;
        for (int j = 0; j < graph[i].size(); ++j)
        {
            if (dfs(graph[i][j]) == UNSAFE) return states[i] = UNSAFE;
        }

        return states[i] = SAFE;
    };

    for (int i = 0; i < graph.size(); ++i)
    {
        if (dfs(i) == SAFE) res.push_back(i);
    }
    return res;
}

// #684
std::vector<int> redundant_connection_dfs(std::vector<std::vector<int>>& edges)
{
    std::vector<int> res;
    if (edges.empty()) return res;

    std::unordered_map<int, std::vector<int>> g;

    std::function<bool(int, int, std::unordered_set<int>&)> cycle = [&](int from ,int to, std::unordered_set<int>& visited)
    {
        if (from == to) return true;
        if (!g.count(from) || !g.count(to)) return false;
        visited.emplace(from);
        for (int tt: g.at(from))
        {
            if (visited.count(tt)) continue;
            if (cycle(tt, to, visited)) return true;
        }
        return false;
    };

    for (std::vector<int> e: edges)
    {
        int from = e[0], to = e[1];

        std::unordered_set<int> visited;
        if (cycle(from, to, visited)) return e;

        g[from].push_back(to);
        g[to].push_back(from);
    }

    return res;
}

// #684
std::vector<int> redundant_connection_union_find(std::vector<std::vector<int>>& edges)
{
    std::vector<int> res;
    if (edges.empty()) return res;

    int n = edges.size();
    // vertex start from 1 and be careful init value.
    std::vector<int> parents(n+1, 0);
    std::vector<int> sizes(n+1, 1);

    std::function<int(int)> find = [&](int i) {
        // union find with path compression
        while (parents[i] != i)
        {
            parents[i] = parents[parents[i]];
            i = parents[i];
        }
        return i;
    };

    for (std::vector<int> edge: edges)
    {
        int from = edge[0], to = edge[1];
        // init parents here
        if (parents[from] == 0) parents[from] = from;
        if (parents[to] == 0) parents[to] = to;

        int pf = find(from), pt = find(to);
        if (pf == pt) return edge;

        // union two point/tree, join smaller to bigger one
        if (sizes[to] > sizes[from]) std::swap(from, to);
        parents[to] = parents[from];
        sizes[from] += sizes[to];
    }

    return res;
}

// #685
std::vector<int> redundant_connection_2_union_find(std::vector<std::vector<int>>& edges)
{
    if (edges.empty()) return {};

    int n = edges.size();
    std::vector<int> parents(n+1, 0);
    std::vector<int> roots(n+1, 0);
    std::vector<int> sizes(n+1, 1);

    std::vector<int> ans1;
    std::vector<int> ans2;

    // case1 cycle
    // case2 two parents, return the first edge

    for (auto& edge: edges)
    {
        int from = edge[0], to = edge[1];

        // two parente case
        if (parents[to] > 0) {
            ans1 = {parents[to], to};  // get previous edge
            ans2 = edge;

            // temp delete second edge
            edge[0] = edge[1] = -1;
        }

        parents[from] = to;
    }

    std::function<int(int)> find = [&](int i)
    {
        while (roots[i] != i)
        {
            roots[i] = roots[roots[i]];
            i = roots[i];
        }
        return i;
    };

    for (auto& edge: edges)
    {
        int from = edge[0], to = edge[1];

        // the deleted edge
        if (from < 0 || to < 0) continue;

        // init union find
        if (roots[from] == 0) roots[from] = from;
        if (roots[to] == 0) roots[to] = to;

        int pf = find(from), pt = find(to);

        if (pf == pt) return (ans1.empty()) ? edge : ans1;

        if (sizes[to] > sizes[from]) std::swap(from, to);
        roots[to] = from;
        sizes[from] += sizes[to];

    }

    return ans2;
}
