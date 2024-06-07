#include<bits/stdc++.h>
using namespace std;

using ll = long long;

struct Edge {
    ll dest, index;
};

ll n, m;

bool compare(Edge lrh, Edge rhs) {
    return lrh.index < rhs.index;
}

vector<vector<Edge>> g;
vector<bool> visited;
vector<ll> degs;

void dfs(int v) {
    visited[v] = true;
    for (auto to : g[v]) {
        if (!visited[to.dest]) {
            dfs(to.dest);
        }
    }
}

vector<ll> solution() {
    vector<bool> used(m, false);
    stack<ll> s;
    s.push(0);

    vector<ll> path;
    while (!s.empty()) {
        bool flag = false;
        ll cur = s.top();
        for (auto [dest, index] : g[cur]) {
            if (!used[index]) {
                used[index] = true;
                s.push(dest);
                flag = true;
                break;
            }
        }
        if (!flag) {
            s.pop();
            path.push_back(cur + 1);
        }
    }
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    visited.resize(n, false);
    g.resize(n);

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    degs.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        degs[i] = g[i].size();
    }

    dfs(0);

    for (int i = 0; i < n; ++i) {
        if (degs[i] % 2 != 0 || (!visited[i] && degs[i] != 0)) {
            cout << ":(";
            return 0;
        }
    }

    for (auto v : solution())
        cout << v << ' ';

    return 0;
}