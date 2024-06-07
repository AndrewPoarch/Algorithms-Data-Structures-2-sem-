#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
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
};

signed main() {
    cin >> n >> m >> q; -- q;

    vector<vector<int>> g(n + m);
    vector<edge> edges;
    int k, t;
    for (int i = 0; i < m; ++i) {
        cin >> k >> t;
        for (int j = 0; j < k; ++j) {
            int v;cin >> v;--v;

            g[v].push_back(edges.size());
            edges.emplace_back(v, n + i, t);
            g[n + i].push_back(edges.size());
            edges.emplace_back(n + i, v, t);
        }
    }

    set<pair<int, int>> s;
    s.insert({ 0, 0 });
    vector<int> dist(m + n, inf);
    dist[0] = 0;

    while(!s.empty()) {
        auto [r, v] = *s.begin();
        s.erase(s.begin());
        for (const auto& el : g[v]) {
            int to = edges[el].b;
            int weight = edges[el].w;
            if (dist[v] + weight < dist[to]) {
                s.erase({ dist[to], to });
                dist[to] = dist[v] + weight;
                s.insert({ dist[to], to });
            }
        }
    }

    if (dist[q] != inf)
        cout << dist[q] / 2;
    else
        cout << -1;

    return 0;
}