// Андрей Глига

#include <iostream>

#include <algorithm>
#include <vector>

using std::vector;

bool flag = false;

void dfs1(int x, vector<bool>& mark, vector<vector<int>>& graph, vector<int>& parent) {
    mark[x] = true;
    for (int i = 0; i < graph[x].size(); ++i) {
        int current = graph[x][i];
        if (!mark[current]) {
            parent[current] = x;
            dfs1(current, mark, graph, parent);
        } else if (current != parent[x]){
            flag = true;
        }
    }
}

int main() {
    int n, m;

    std::cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<int> parent(n + 1);
    vector<bool> mark(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for (int i = 0; i < n; ++i) {
        if (!mark[i]) {
            parent[i] = -1;
            dfs1(i, mark, graph, parent);
        }
    }


    if (flag) std::cout << "YES";
    else std::cout << "NO";

    return 0;
}