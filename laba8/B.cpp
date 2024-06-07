#include <iostream>

#include <vector>
#include <algorithm>

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

int main() {
    int n, m, q;

    std::cin >> n >> m >> q;
    vector<vector<int>> graph (n + 1);
    vector<vector<int>> rgraph(n + 1);
    vector<int> family(n + 1, -1);
    std::vector<bool> mark (n + 1);
    vector<int> tout;

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[x].push_back(y);
        rgraph[y].push_back(x);
    }

    for (int i = 1; i <= n; ++i) {
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

    vector<int> fam_mins(type + 1, 1000000);
    for (int i = 0; i < family.size(); ++i) {
        if (family[i] == -1) {
            continue;
        }
        fam_mins[family[i]] = std::min(fam_mins[family[i]], i);
    }

    for (int i = 0; i < q; ++i) {
        int start, end;
        std::cin >> start >> end;
        if (fam_mins[family[start]] == fam_mins[family[end]]) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }

    return 0;
}