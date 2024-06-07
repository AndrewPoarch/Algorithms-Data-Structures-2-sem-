// Андрей Глига

#include <iostream>

#include <algorithm>
#include <vector>
#include <set>

using std::vector;

void dfs1(int x, vector<bool>& mark, vector<vector<int>>& graph, vector<int>& tout) {
    mark[x] = true;
    for (int i = 0; i < graph[x].size(); ++i) {
        int current = graph[x][i];
        if (!mark[current]) {
            dfs1(current, mark, graph, tout);
        }
    }
    tout.push_back(x);
}

void dfs2(int x, int type, vector<vector<int>>& rgraph, vector<int>& family) {
    family[x] = type;
    for (int i = 0; i < rgraph[x].size(); ++i) {
        int current = rgraph[x][i];
        if (family[current] == -1) {
            dfs2(current, type, rgraph, family);
        }
    }
}

void dfs3(int x, vector<bool>& mark, vector<vector<int>>& graph, vector<int>& family, vector<int>& fam_mins, std::set<std::pair<int, int>>& result) {
    mark[x] = true;
    for (int i = 0; i < graph[x].size(); ++i) {
            int cur = graph[x][i];
            if (fam_mins[family[x]] != fam_mins[family[cur]]) {
//                result.insert(std::make_pair(fam_mins[family[x]] + 1, fam_mins[family[cur]] + 1));
                result.emplace(fam_mins[family[x]] + 1, fam_mins[family[cur]] + 1);
            }
            if (!mark[graph[x][i]]) {
                dfs3(cur, mark, graph, family, fam_mins, result);
            }
    }
}

int main() {
    int n, m, q;

    std::cin >> n >> m >> q;
    vector<vector<int>> graph(n);
    vector<vector<int>> rgraph(n);
    vector<bool> mark(n);
    vector<int> tout;
    vector<int> family(n, -1);
    std::set<std::pair<int, int>> result;

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[--x].push_back(--y);
        rgraph[y].push_back(x);
    }

    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            dfs1(i, mark, graph, tout);
        }
    }

    int type = 0;
    std::reverse(tout.begin(), tout.end());
    for (int& x : tout) {
        if (family[x] == -1) {
            dfs2(x, type++, rgraph, family);
        }
    }

    vector<int> fam_mins(type + 1, INT_MAX);
    for (int i = 0; i < family.size(); ++i) {
        if (family[i] == -1) {
            continue;
        }
        fam_mins[family[i]] = std::min(fam_mins[family[i]], i);
    }

    vector<bool> mark1(n );
    for (int i = 0; i < n; i++) {
        if (!mark1[i]) {
            dfs3(i, mark1, graph, family, fam_mins, result);
        }
    }
//    std::sort(begin(result), end(result));
    std::cout << type << ' ' << result.size() << '\n';
    auto sz = result.size();
    for (int i = 0; i < sz; ++i) {
        std::pair<int, int> temp = result.extract(result.begin()).value();
        std::cout << temp.first << ' ' << temp.second << '\n';
    }


    return 0;
}