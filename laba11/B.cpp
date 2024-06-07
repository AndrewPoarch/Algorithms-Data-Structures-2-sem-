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

struct Edge {
  public:
    Edge(int a, int b, int c, int f, int w, int sz, int id)
        : from_(a), to_(b), cap_(c), flow_(f), cost_(w), size_(sz), idx(id) {}
    int from_, to_, cap_, flow_, cost_;
    size_t size_, idx;

    int get_cap() {
        return cap_ - flow_;
    }
};

vector<vector<Edge>> graph;
vector<int> dist;
vector<int> id;
vector<Edge*> par;

void solution() {
    int Mcost = 0, Mflow = 0;
    for (;;) {
        deque<int> q;
        id = vector<int>(n, 0);
        dist = vector<int>(n, INF);
        par.resize(n);

        dist[0] = 0;
        q.push_back(0);

        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            id[v] = 2;

            for (const auto& [from, to, cap, flow, cost, size, idx] : graph[v]) {
                if (flow < cap && dist[to] > dist[from] + cost) {
                    dist[to] = dist[from] + cost;

                    if (!id[to]) {
                        q.push_back(to);
                    } else if (id[to] == 2) {
                        q.push_front(to);
                    }

                    id[to] = 1;
                    par[to] = &graph[from][idx];
                }
            }
        }

        int delta = INF;

        if (dist[t] == INF)
            break;
        else {
            for (auto v = t; v != s; v = par[v]->from_) {
                auto edge = par[v];
                delta = min(delta, edge->cap_ - edge->flow_);
            }
            for (auto v = t; v != s; v = par[v]->from_) {
                auto edge = par[v];
                auto reversed = &graph[edge->to_][edge->size_];

                edge->flow_ += delta;
                reversed->flow_ -= delta;

                Mcost += delta * edge->cost_;
            }

            Mflow += delta;
        }
    }

    cout << Mflow << ' ' << Mcost;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m >> s >> t;
    --s;
    --t;

    graph.resize(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c, p;
        cin >> a >> b >> c >> p;
        --a;
        --b;
        graph[a].emplace_back(a, b, c, 0, p, -1, graph[a].size());
        graph[b].emplace_back(b, a, 0, 0, -p, -1, graph[a].size());

        graph[a].back().size_ = graph[b].size() - 1;
        graph[b].back().size_ = graph[a].size() - 1;
    }

    solution();

    return 0;
}
