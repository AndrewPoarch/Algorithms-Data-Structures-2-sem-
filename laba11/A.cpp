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
vector<vector<char>> field;
vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool check(int i, int j) {
    if (0 <= i && i < n && j >= 0 && j < m && field[i][j] != '#')
        return true;
    return false;
}


void make_graph() {
    cin >> n >> m;
    int q;
    cin >> q;

    field = vector<vector<char>>(n, vector<char>(m, '*'));

    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        field[x][y] = '#';
    }

    g.resize(n * m);

    vector<pair<int, int>> prs;
    prs.emplace_back(-1, 0);
    prs.emplace_back(1, 0);
    prs.emplace_back(0, -1);
    prs.emplace_back(0, 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (auto [x, y] : prs) {
                if (check(i, j) && check(i + x, j + y)) {
                    g[i * m + j].push_back((i + x) * m + (j + y));
                }
            }
        }
    }

}

bool dfs(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (const auto& u : g[v]) {
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    make_graph();

    int ans = 0;

    mt = vector<int>(m * n, -1);
    for (int i = 0; i < n * m; i++) {
        used = vector<bool>(n * m, false);
        if (dfs(i))
            ++ans;
    }

    cout << ans;

    return 0;
}
