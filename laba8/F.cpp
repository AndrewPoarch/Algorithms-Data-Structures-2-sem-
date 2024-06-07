// Андрей Глига

#include <iostream>

#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


vector<int> bfs_solution(int n, int k, vector<vector<int>>& graph) {
    queue<int> q;
    vector<int> mark(n, -1);
    mark[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int& i : graph[v]) {
            if (mark[i] == -1) {
                q.push(i);
                mark[i] = mark[v] + 1;
            }
        }
    }
    vector<int> answer;
    for (int i = 0; i < n; ++i) {
        if (mark[i] == k) answer.push_back(i + 1);
    }

    return answer;
}


int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        graph[--x].push_back(--y);
        graph[y].push_back(x);
    }

    vector<int> ans = bfs_solution(n, k, graph);
    if (ans.empty()) cout << "NO";
    else {
        for (auto& el: ans) cout << el << '\n';
    }


    return 0;
}