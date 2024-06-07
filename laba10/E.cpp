#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

const int m_max = 1000000;

int n, m, q;

int timer = 1;
vector<int> tin, fup;
vector<pair<int, int>> bridges;
set<pair<int, int>> edges;

vector<int> unions;
vector<int> weights;

int find_set(int v) {
    if (v == unions[v])
        return v;
    return unions[v] = find_set(unions[v]);
}

void m_union(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        if (weights[x] > weights[y]) {
            swap(x, y);
        }
        weights[x] += weights[y];
        unions[y] = x;
    }
}

void dfs(int v, vector<vector<int>>& g, vector<bool>& used, int p = -1) {
    used[v] = true;
    tin[v] = timer;
    fup[v] = timer;
    ++timer;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p) continue;
        if (used[to])
            fup[v] = min(fup[v], tin[to]);
        else {
            dfs(to, g, used, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] > tin[v])
                bridges.emplace_back(min(v, to), max(v, to));
        }
    }
}

void find_bridges(vector<vector<int>>& g, vector<bool>& used) {
    timer = 1;
    tin.resize(n);
    fup.resize(n);
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i, g, used);
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> q;
    ++n;
    vector<vector<int>> g(n);
    unions.resize(n, -1);
    weights.resize(n, 1);
    for (int i{0}; i < n; ++i) {
        unions[i] = i;
    }
    vector<bool> used(n, false);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        edges.insert({min(a, b), max(a, b)});
    }

    find_bridges(g, used);

    for (auto& i : bridges) {
        edges.erase(i);
    }

    for (auto& i : edges) {
        m_union(i.first, i.second);
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (find_set(a) == find_set(b))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}