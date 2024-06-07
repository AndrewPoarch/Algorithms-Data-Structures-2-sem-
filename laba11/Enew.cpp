#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <math.h>
#include <iomanip>
#include <map>
#include <string>
#include <stack>
#include <numeric>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <cctype>
#include <fstream>
using namespace std;
#define int long long
#define M7 1'000'000'007LL;
#define INF M7 * M7
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define eps 1e-6

int n, k, m;
vector<vector<char>> field;
vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

vector<int> L;
vector<int> R;


void make_graph() {
    cin >> n >> k >> m;

    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        g[x].push_back(y);
        L.push_back(x);
        R.push_back(y);
    }
}

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (const auto& u : g[v]) {
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

void dfs1(int v, vector<bool>& vis, vector<set<int>>& new_g) {
    vis[v] = true;
    for (const auto& u : new_g[v]) {
        if (!vis[u])
            dfs1(u, vis, new_g);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    make_graph();

    mt = vector<int>(k, -1);
    for (int i = 0; i < n; i++) {
        used = vector<bool>(n, false);
        dfs(i);
    }

    vector<set<int>> new_g(n + k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
            new_g[i].insert(g[i][j] + n);
        }
    }

    vector<bool> has_pair(n, false);

    for (int i = 0; i < mt.size(); ++i) {
        if (mt[i] == -1)
            continue;

        new_g[mt[i]].erase(n + i);
        new_g[n + i].insert(mt[i]);
        has_pair[mt[i]] = true;
    }

    vector<bool> vis(n + k, false);
    for (int i{0}; i < n; ++i) {
        if (!has_pair[i])
            dfs1(i, vis, new_g);
    }

    vector<int> ver_left;
    vector<int> ver_right;
    for (int i = 0; i < n; ++i) {
        if (!vis[i])
            ver_left.push_back(i + 1);
    }

    for (int i = n; i < n + k; ++i) {
        if (vis[i])
            ver_right.push_back(i - n + 1);
    }

    cout << ver_left.size() << '\n';
    for ( auto el: ver_left) {
        cout << el << ' ';
    }
    cout << '\n';
    cout << ver_right.size() << '\n';
    for ( auto el: ver_right) {
        cout << el << ' ';
    }


    return 0;
}
