#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000000;

int n, m;
vector<vector<int>> g(MAX);
vector<int> prufer;
vector<int> degrees(MAX, 0);
priority_queue<int, vector<int>, greater<>> leaves;
vector<bool> visited(MAX, false);



int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b; --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < n; ++i) {
        int cur_deg = g[i].size();
        degrees[i] = cur_deg;
        if (cur_deg == 1)
            leaves.push(i);
    }

    for (int i = 0; i < n - 2; ++i) {
        int cur_leaf = leaves.top();
        leaves.pop();
        visited[cur_leaf] = true;
        int parent;
        for (auto el: g[cur_leaf]) {
            if (!visited[el]) {
                parent = el;
            }
        }
        prufer.push_back(parent);
        --degrees[parent];
        if (degrees[parent] == 1)
            leaves.push(parent);

    }


    for (auto c: prufer)
        cout << ++c << ' ';


    return 0;
}