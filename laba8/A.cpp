// Андрей Глига

#include <iostream>

#include <algorithm>
#include <vector>

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




int main() {
    int n, m;

    std::cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<bool> mark(n + 1);
    vector<int> tout;

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[x].push_back(y);
    }

    for (int i = 1; i <= n; ++i) {
        if (!mark[i]) {
            dfs1(i, mark, graph, tout);
        }
    }

    std::reverse(tout.begin(), tout.end());

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[tout[i] - 1] = i + 1;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
}