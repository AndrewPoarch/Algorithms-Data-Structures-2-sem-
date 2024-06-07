// Андрей Глига

#include <iostream>

#include <algorithm>
#include <vector>

using std::vector;

void dfs1(int x, vector<bool>& mark, vector<vector<int>>& graph) {
    mark[x] = true;
    for (int i = 0; i < graph[x].size(); ++i) {
        int current = graph[x][i];
        if (!mark[current]) {
            dfs1(current, mark, graph);
        }
    }
}

int main() {
    int n, m;

    std::cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<bool> mark(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int type = 0;
    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            dfs1(i, mark, graph);
            type++;
        }
    }


    std::cout << type;

    return 0;
}