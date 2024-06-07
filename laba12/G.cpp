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
#define M7 1'000'000'007LL;
#define INF M7 * M7
#define CONST 1000000000;
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define eps 1e-6

int ans = 0;

vector<vector<int>> g1;
vector<vector<int>> g2;
int n;

map<vector<int>, int> table;
vector<int> children_hashes;

int getHash(vector<int>& v) {
    if (table.find(v) == table.end())
        table[v] = (int) table.size();
    return table[v];
}

int dfs(int v, int p, vector<vector<int>>& g) {
    vector<int> children;
    for (auto u : g[v]) {
        if (u != p) {
            children.push_back(dfs(u, v, g));
        }
    }
    sort(ALL(children));
    return children_hashes[v] = getHash(children);
}

void dfs1(vector<vector<int>>& graph, vector<int>& size, vector<bool>& used, int v) {
    used[v] = true;
    size[v] = 1;
    for (int u : graph[v]) {
        if (!used[u]) {
            dfs1(graph, size, used, u);
            size[v] += size[u];
        }
    }
}

int centroid(vector<bool>& used, vector<vector<int>>& graph, vector<int>& size, int v) {
    used[v] = true;
    for (int u : graph[v]) {
        if (!used[u] && size[u] > n / 2) {
            return centroid(used, graph, size, u);
        }
    }

    return v;
}

signed main() {

    cin >> n;

    g1.resize(n + 1);
    g2.resize(n + 1);

    int l1, l2;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g1[u].push_back(v);
        g1[v].push_back(u);
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g2[u].push_back(v);
        g2[v].push_back(u);
    }

    int c1, c2;
    vector<bool> used1(n + 1, false);
    vector<bool> used2(n + 1, false);
    vector<int> size1(n + 1, 0);
    vector<int> size2(n + 1, 0);
    dfs1(g1, size1, used1, 1);
    dfs1(g2, size2, used2, 1);
    used1.assign(n + 1, false);
    used2.assign(n + 1, false);
    c1 = centroid(used1, g1, size1, 1);
    c2 = centroid(used2, g2, size2, 1);

    children_hashes.assign(n + 1, -1);
    int h1 = dfs(c1, -1, g1);

    table.clear();
    children_hashes.assign(n + 1, -1);
    int h2 = dfs(c2, -1, g2);

    if (h1 == h2) cout << "YES";
    else cout << "NO";

    return 0;
}
