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
#define inf 1000000000
#define ALL(a) a.begin(), a.end()
#define eps 1e-6

int n, m;

vector<vector<int>> g;
vector<bool> used;
vector<int> tin;
int temp_ans = 1;
vector<int> vvv;
vector<int> cycle;
bool f = false;
bool f1 = false;
int start;
int timer = 0;


void dfs(int v, int prev = -1){
    if (!used[v]) {
        tin[v] = timer;
        timer++;
        used[v] = true;
        for (auto x: g[v]) {
            if (x != prev) {
                if (tin[x] < tin[v]) {
                    start = x;
                    vvv.push_back(tin[v] - tin[x] + 1);
                    f = true;
                    f1 = true;
                }
                if (!f)
                    dfs(x, v);
            }
        }
    }
    if (f1) {
        cycle.push_back(v);
        if (v == start)
            f1 = false;
    }
}


signed main() {

    cin >> n >> m;
    if (n > 100000 || m > 100000)
        exit(3);

    g.resize(n);
    tin.resize(n, inf);

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
            dfs(i);
            if (cycle.size() > 2) {
                ans.push_back(cycle.size());
                used = vector<bool> (n ,false);
                for (auto el: cycle)
                    used[el] = true;

                break;
            }
        }
    }



    cout << '\n';
    timer = 0;
    tin = vector<int>(n, inf);
    f1 = false;
    f = false;

    auto temp = used;
    cycle.clear();
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            if (i == 14)
                int y = 1;
            dfs(i);
            if (cycle.size() > 2) {
                ans.push_back(cycle.size());
                break;
            }
            used = temp;
            tin = vector<int>(n, inf);
            timer = 0;
            cycle.clear();
        }
    }

    sort(ALL(ans));
    cout << ans[0];

    return 0;
}
