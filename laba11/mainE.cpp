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

int n, m;
struct Edge {
    int from_, to_, w_;

    Edge(int to, int w) :
        to_(to), w_(w) {}
    Edge(int from, int to, int w) :
        from_(from), to_(to), w_(w) {}
};

vector<vector<char>> field;
vector<vector<Edge>> g;
vector<int> mt;
vector<bool> used;

vector<int> res;

vector<Edge> edges;

bool compare(Edge a, Edge b) {
    return a.w_ < b.w_;
}
vector<int> unions;
vector<int> weights;

int find(int v) {
    if (v == unions[v])
        return v;
    return unions[v] = find(unions[v]);
}

void m_union(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (weights[x] > weights[y]) {
            swap(x, y);
        }
        weights[x] += weights[y];
        unions[y] = x;
    }
}



auto prima() {
    std::sort(edges.begin(), edges.end(), compare);
    for (auto [from, to, w]: edges) {
        if (find(to) != find(from)) {
            m_union(to, from);
            g[from].emplace_back(to, w);
            g[to].emplace_back(from, w);
        }
    }
}

vector<int> a;
vector<int> b;
vector<int> c;
vector<int> parent;

void dfs(int v) {
    for (const auto& [from, to, w] : g[v]) {
        if (to == parent[v])
            continue;
        parent[to] = v;
        dfs(to);
        a[v] = max(a[v], b[to] + w - c[to]);
        b[v] += c[to];
    }
    a[v] += b[v];
    c[v] = max(a[v], b[v]);
}

signed main() {

    cin >> n >> m;
    weights.resize(n, 0);
    unions.resize(n);

    g.resize(n);
    a = vector<int>(n, 0);
    b = vector<int>(n, 0);
    c = vector<int>(n, 0);
    parent.resize(n ,-1);
    for (int i = 0; i < n; ++i) {
        unions[i] = i;
    }


    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        --x;
        --y;

        edges.emplace_back(x, y, w);
    }

    prima();

    dfs(0);

    cout << c[0];

    return 0;
}
