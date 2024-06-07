#include <bits/stdc++.h>

using namespace std;

const long long INF = INT64_MAX;
int n, m, p;

struct Path {
    long long days_count;
    long long balance;
};

struct Base {
    Path params;
    int node_number;
    int best;
};

bool operator==(const Path &a, const Path &b) {
    return tie(a.days_count, a.balance) == tie(b.days_count, b.balance);
}

bool operator!=(const Path &a, const Path &b) {
    return !(a == b);
}

bool operator<(const Path &a, const Path &b) {
    if (a.days_count != b.days_count) return a.days_count < b.days_count;
    return a.balance > b.balance;
}

bool operator<(const Base &a, const Base &b) {
    return tie(a.params, a.node_number, a.best) < tie(b.params, b.node_number, b.best);
}

bool operator>(const Base &a, const Base &b) {
    return !(a < b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p;
    vector<vector<pair<int, int>>> g(n);
    vector dp (n,vector<Path>(n, {INF, 0}));
    vector<int> w (n);
    for (int i{0}; i < n; ++i) {
        cin >> w[i];
    }
    for (int i{0}; i < m; ++i) {
        int a,b,t;
        cin >> a >> b >> t;
        g[--a].emplace_back(--b, t);
    }

    dp[0][0] = {0, p};

    priority_queue<Base, vector<Base>, greater<>> pq;
    pq.push({.params = {.days_count = 0, .balance = p}, .node_number = 0 , .best = 0});

    while (!pq.empty()) {
        Base cur = pq.top();
        pq.pop();
        int cur_node = cur.node_number;
        int cur_best = cur.best;
        if (dp[cur_node][cur_best] != cur.params) {
            continue;
        }
        for (auto& [to, cost]: g[cur_node]) {
            Base temp_base = cur;
            Path& temp_path = temp_base.params;
            if (temp_path.balance < cost) {
                long long days_need = (cost - temp_path.balance + w[cur_best] - 1) / w[cur_best];
                temp_path.days_count += days_need;
                temp_path.balance += (days_need * w[cur_best]);
                assert(temp_path.balance < cost + w[cur_best]);
            }
            temp_path.balance -= cost;
            temp_base.node_number = to;
            if (w[to] > w[temp_base.best]) {
                temp_base.best = to;
            }
            if (temp_path < dp[to][temp_base.best]) {
                dp[to][temp_base.best] = temp_path;
                pq.push(temp_base);
            }
        }
    }

    long long ans = INF;
    for (int i{0}; i < n; ++i) {
        ans = min(ans, dp[n - 1][i].days_count);
    }
    if (ans == INF) {
        cout << -1;
    } else {
        cout << ans;
    }
}