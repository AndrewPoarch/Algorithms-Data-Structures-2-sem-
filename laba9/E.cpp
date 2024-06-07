
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = INT_MAX;
int n, m;


int timer;
vector<int> tin, fup;
vector<pair<int, int>> bridges;

void dfs (int v, vector<vector<int>>& g, vector<bool>& used, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs (to, g, used, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v])
                bridges.emplace_back(min(v, to),max(v, to));
        }
    }
}

void find_bridges(vector<vector<int>>& g, vector<bool>& used) {
    timer = 0;
    tin.resize(n);
    fup.resize(n);
    for (int i=0; i<n; ++i)
        if (!used[i])
            dfs (i, g, used);
}

int main() {
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<bool> used(n, false);
    for (int i{0}; i < m; ++i) {
        int a,b;
        cin >> a >> b;
        g[--a].emplace_back(--b);
        g[b].emplace_back(a);
    }
    find_bridges(g, used);
    std::sort(bridges.begin(), bridges.end());
    for (auto& [a, b]: bridges) {
        cout << ++a << ' ' << ++b << '\n';
    }
}