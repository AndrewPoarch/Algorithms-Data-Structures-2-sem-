
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;
using m_int = unsigned long long;

const m_int INF = UINT64_MAX;
int n, m;


int main() {
    cin >> n >> m;
    vector<vector<m_int>> g(n, vector<m_int>(n, INF));

    for (int i{0}; i < m; ++i) {
        m_int a, b, c;
        cin >> a >> b >> c; --a; --b;
        g[a][b] = min(c, g[a][b]);
        g[b][a] = min(c, g[b][a]);
    }

    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (g[i][k] != INF && g[k][j] != INF) {
                    g[i][j] = min(g[i][j], g[k][j] + g[i][k]);
                }
            }
        }
    }

    m_int min_sum = INF;
    int min_index = 1;
    for (int i = 0; i < n; ++i) {
        m_int sum = 0;
        for (int j = 0; j < n; ++j) {
            if (sum + g[i][j] > INF)
                sum = INF;
            else
                sum += (g[i][j]);
        }
        if (sum < min_sum) {
            min_sum = sum;
            min_index = i + 1;
        }
    }

    cout << min_index;



    return 0;
}