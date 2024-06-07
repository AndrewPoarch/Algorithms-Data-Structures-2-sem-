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
#include <iostream>
#define ALL(a) a.begin(), a.end()
#define int long long
#define inf 100000000000000
using namespace std;

using namespace std;

const int m_max = 1000000;

int n, m, q;

struct edge {
    edge(int _a, int _b, int _w) :
    a(_a), b(_b), w(_w) {};
    int a, b, w;
    bool operator<(const edge& other) const {
        return w < other.w;
    }

    bool operator==(const edge& other) const {
        return a == other.a && b == other.b && w == other.w;
    }
};

int timer = 1;
vector<int> tin, fup;
vector<pair<int, int>> bridges;
vector<edge> edges;

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


signed main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    vector<vector<int>> g(n);
    unions.resize(n, -1);
    weights.resize(n, 1);
    for (int i{0}; i < n; ++i) {
        unions[i] = i;
    }
    vector<bool> used(n, false);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w; --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
        edges.emplace_back(a, b, w);
    }

    sort(ALL(edges));

    int ans = 0;
    for (const auto& e: edges) {
        if (find_set(e.a) != find_set(e.b)) {
            ans += e.w;
            m_union(e.a, e.b);
        }
    }
    
    int min_= inf;
    for (int i = 0; i < n - 2; ++i) {
        vector<edge> copy_ = edges;
        copy_.erase(copy_.begin() + i);
        int second_ans = 0;
        unions.resize(n, -1);
        weights.resize(n, 1);
        for (int j{0}; j < n; ++j) {
            unions[j] = j;
        }
        for (const auto& edge: copy_) {
            if (find_set(edge.a) != find_set(edge.b)) {
                second_ans += edge.w;
                m_union(edge.a, edge.b);
            }
        }
        min_ = min(min_, second_ans);
    }
    cout << ans << ' ' << min_;

    return 0;
}