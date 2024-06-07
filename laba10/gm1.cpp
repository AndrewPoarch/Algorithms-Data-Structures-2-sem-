#include <vector>
#include <queue>
#include <iostream>

#define int long long
using namespace std;

struct road {
    road(int a, int b, int w, int t)
        : a_(a), b_(b), w_(w), t_(t) {};
    int a_, b_, w_, t_;
};

bool operator>(const road& x, const road& y) {
    return x.w_ > y.w_;
}

int n, m, k;

vector<vector<road>> g;
priority_queue<road, vector<road>, greater<road>> q;

signed main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    g.resize(n);

    int a, b, w, balance = 0;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> w;
        --a;
        --b;
        g[a].emplace_back(a, b, w, 1);
        g[b].emplace_back(b, a, w, 1);
        balance += w;
    }
    for (int i = 0; i < k; ++i) {
        cin >> a >> b >> w;
        --a;
        --b;
        g[a].emplace_back(a, b, w, 0);
        g[b].emplace_back(b, a, w, 0);
    }
    q.emplace(0, 1, -1, -1);

    vector<bool> used(n, 0);
    int ans = 0;

    while (!q.empty()) {
        auto r = q.top();
        q.pop();
        int weight = r.w_;
        int v = r.b_;
        if (used[v]) continue;
        used[v] = 1;
        if (r.t_ == 1)
            balance -= weight;
        else if (r.t_ == 0)
            ans += weight;
        for (auto el : g[v]) {
            int to = el.b_;
            int cost = el.w_;
            int type = el.t_;
            if (!used[to]) {
                q.emplace(-1, to, cost, type);
            }
        }
    }

    if (balance > ans)
        cout << 0;
    else
        cout << ans - balance;

    return 0;
}