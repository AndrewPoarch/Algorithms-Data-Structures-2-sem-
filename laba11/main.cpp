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
#define ALL(a) a.begin(), a.end()
#define eps 1e-6

int n, m;

vector<vector<int>> g;
vector<bool> used;
vector<int> dist;
int temp_ans = 1;
vector<int> vvv;
bool f = false;
int start;

void dfs(int v, int prev = -1){
    if (!used[v]) {
        used[v] = true;
        for (auto x: g[v]) {
            if (x != prev && !f)
                dfs(x, v);
        }
        if (f)
            vvv.push_back(v);
    } else {
        if (v == start)
            f = true;
    }
}

signed main() {

    cin >> n >> m;

    g.resize(n);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;

        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    vector<int> ans;
    used.resize(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            start = i;
            f = false;
            dfs(i);
            if (vvv.size() != 0) {
                ans.push_back(vvv.size());
                vvv.clear();
            } else {
                used = vector<bool>(n, false);
            }
        }
    }

    sort(ALL(ans));
    cout << ans[0];




    return 0;
}
