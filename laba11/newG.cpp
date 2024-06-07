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
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define eps 1e-6

int n, m;

int timer = 0;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(n, 0));
    set<int> ver;
    vector<int> start;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a][b] = 1;
        g[b][a] = 1;
        start.push_back(a);
        start.push_back(b);
    }

    queue<int> q;
    vector<bool> used(start.size(), false);
    vector<int> v;
    for ( auto el: start)
        if (!used[el]) {
            used[el] = true;
            v.push_back(el);
        }

    for (int i = 0; i < n * (n - 1); ++i) {
        if (g[v[0]][v[1]] != 1) {
            int j = 2;
            while (g[v[0]][v[j]] != 1 || g[v[1]][v[j + 1]] != 1) {
                ++j;
            }
            reverse(v.begin() + 1, v.begin() + j);
        }
        v.push_back(v.front());
        v.erase(v.begin());
    }


  for (auto el: v)
      cout << el << ' ';






    return 0;
}
