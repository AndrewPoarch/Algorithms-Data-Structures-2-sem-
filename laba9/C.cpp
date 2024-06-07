#include <iostream>
#include <vector>

using namespace std;

const int INF = INT_MAX;
int n, m;

vector<int> dkstr(int s, vector<vector<pair<int, int>>>& g) {
    vector<int> d (n, INF);
    vector<bool> a (n, false);
    d[s] = 0;

    for (int i{0}; i < n; ++i) {
        int v{-1};
        for (int j{0}; j < n; ++j) {
            if (!a[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }
        a[v] = true;
        for (auto& [to, weight]: g[v]) {
            d[to] = min(d[to], d[v] + weight);
        }
    }

    return d;
}

int main() {
    cin >> n >> m;
    if (n > (int)1e5 + 1 || m > 2 * (int)1e5) {
        return 1;
    }
    vector<vector<pair<int, int>>> g(n);
    for (int i{0}; i < m; ++i) {
        int a,b,t;
        cin >> a >> b >> t;
        if (a > n || b > n || t > (int)1e6 + 1 || t < 1) {
            return 1;
        }
        g[--a].emplace_back(--b, t);
    }

    vector<int> ans = dkstr(0, g);
    if (ans[n - 1] == INF) [[unlikely]]
        cout << -1;
    else [[likely]]
        cout << ans[n - 1];
}