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
#define int long long
#define ALL(a) a.begin(), a.end()
#define eps 1e-6

int n, m;

vector<pair<int, int>> par;

struct Edge{
    Edge(int to, int w, int id)
    : to_(to), w_(w), id_(id){};
    int to_, w_, id_;
};

vector<vector<Edge>> g;

auto dkstr(int s) {
    vector<int> d(n, inf);

    vector<bool> used(n + m, false);
    d[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto [weight, from] = q.top();
        q.pop();
        if (weight > d[from])
            continue;
        for (auto [to, w, id] : g[from]) {
            if (!used[id] && d[to] > d[from] + w) {
                used[id] = true;
                par[to] = {from, id};
                d[to] = d[from] + w;
                q.emplace(d[to], to);
            }
        }
    }

    return d;
}

signed main() {
    cin >> n >> m;
    g.resize(n);
    par.resize(n ,{-1, -1});
    for (int i{0}; i < m; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        g[--a].emplace_back(--b, t, i);
        g[b].emplace_back(a, t, i);
    }

    auto ans = dkstr(0);

    cout << ans[n -1] << ' ';

    vector<int> path;
    auto v = par[n-1];
    while (v.first != -1) {
        path.push_back(v.second);
        v = par[v.first];
    }

    int sec_min = inf;
    for (auto idx: path) {
        vector<int> d(n, inf);

        vector<bool> used(n + m, false);
        d[0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.push({0, 0});
        while (!q.empty()) {
            auto [weight, from] = q.top();
            q.pop();
            if (weight > d[from])
                continue;
            for (auto [to, w, id] : g[from]) {
                if (id != idx && !used[id] && d[to] > d[from] + w) {
                    used[id] = true;
                    d[to] = d[from] + w;
                    q.emplace(d[to], to);
                }
            }
        }
        if (d[n-1] < sec_min)
            sec_min = d[n-1];
    }

    cout << sec_min;

    return 0;
}