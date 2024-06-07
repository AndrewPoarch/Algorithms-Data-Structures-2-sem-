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
#define INF 100000000000000
#define ALL(a) a.to_egin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define eps 1e-6

int n, m, s, t;

struct edge {
    edge(int a, int b, int c, int f, int w, size_t sz) : from_(a), to_(b), cap_(c), flow_(f), cost_(w), size_(sz) {}
    int from_, to_, cap_, flow_, cost_;
    size_t size_;

    int get_cap() {
        return cap_ - flow_;
    }
};

vector<vector<edge>> g;
vector<vector<int>> graph;
vector<edge> edges;

vector<int> used;

int timer = 0;

int dfs(int v, int Mcap) {
    if (v == t)
        return Mcap;

    used[v] = timer;

    for (int index : graph[v]) {
        if (edges[index].get_cap() == 0)
            continue;

        if (used[edges[index].to_] == timer) continue;

        int x = dfs(edges[index].to_, min(Mcap, edges[index].get_cap()));

        if (x) {
            edges[index].flow_ += x;
            edges[index ^ 1].flow_ -= x;

            return x;
        }
    }

    return 0;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> s >> t;
    --s;
    --t;

    used.resize(n, -1);
    g.resize(n);
    graph.resize(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c, p;
        cin >> a >> b >> c >> p;
        --a;
        --b;
        graph[a].push_back(edges.size());
        edges.emplace_back(a, b, c, 0, p, -1);
        edge r1 = {a, b, c, 0, p, g[b].size()};
        edge r2 = {b, a, 0, 0, -p, g[a].size()};
        g[a].push_back(r1);
        graph[b].push_back(edges.size());
        g[b].push_back(r2);
        edges.emplace_back(b, a, 0, 0, -p, -1);
    }

    int flow = 0;
    int cost = 0;
    int K = INF;
//    while (dfs(s, INF))
//        ++timer;

//    for (int index : graph[s])
//        K += edges[index].flow_;

    while (flow < K) {
        vector<int> id(n, 0);
        vector<int> d(n, INF);
        vector<int> q(n);
        vector<int> p(n);
        vector<size_t> p_rib(n);
        int qh = 0, qt = 0;
        q[qt++] = s;
        d[s] = 0;
        while (qh != qt) {
            int v = q[qh];
            qh++;
            id[v] = 2;
            if (qh == n)
                qh = 0;
            for (auto i = 0; i < g[v].size(); ++i) {
                edge& r = g[v][i];
                if (r.flow_ < r.cap_ && d[v] + r.cost_ < d[r.to_]) {
                    d[r.to_] = d[v] + r.cost_;
                    if (id[r.to_] == 0) {
                        q[qt] = r.to_;
                        qt++;
                        if (qt == n) qt = 0;
                    } else if (id[r.to_] == 2) {
                        if (--qh == -1) qh = n - 1;
                        q[qh] = r.to_;
                    }
                    id[r.to_] = 1;
                    p[r.to_] = v;
                    p_rib[r.to_] = i;
                }
            }
        }
        if (d[t] == INF)
            break;
        int addflow = K - flow;
        for (int v = t; v != s; v = p[v]) {
            int pv = p[v];
            size_t pr = p_rib[v];
            addflow = min(addflow, g[pv][pr].cap_ - g[pv][pr].flow_);
        }
        for (int v = t; v != s; v = p[v]) {
            int pv = p[v];
            size_t pr = p_rib[v];
            size_t r = g[pv][pr].size_;
            g[pv][pr].flow_ += addflow;
            g[v][r].flow_ -= addflow;
            cost = cost + (g[pv][pr].cost_ * addflow);
        }
        flow += addflow;
    }

    cout << flow << ' ' << cost;

    return 0;
}
