#include<vector>
#include <iostream>
#define ALL(a) a.begin(), a.end()
#define int long long
using namespace std;

using ll = long long;

struct Edge {
    ll src, dest, weight;
};
vector<Edge> edges;

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}
vector<ll> unions;
vector<ll> weights;

ll find(ll v) {
    if (v == unions[v])
        return v;
    return unions[v] = find(unions[v]);
}

void m_union(ll x, ll y) {
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    weights.resize(n, 0);
    unions.resize(n);
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w; --u; --v;
        edges.push_back({u, v, w});
    }

    for (int i = 0; i < n; ++i) {
        unions[i] = i;
    }

    std::sort(edges.begin(), edges.end(), compare);
    ll mst_w = 0;
    for (auto edge: edges) {
        if (find(edge.dest) != find(edge.src)) {
            mst_w +=edge.weight;
            m_union(edge.dest, edge.src);
        }
    }
    cout << mst_w;

    return 0;
}