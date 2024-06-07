#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;
int n, m;

set<pair<int, int>> edges;

vector<int> unions;
vector<int> weights;
struct request {
    request() = default;
    request(char _c, int _a, int _b) :
    c(_c), a(_a), b(_b) {};
    char c;
    int a, b;
};
vector<request> info;

int find_set (int v) {
    if (v == unions[v])
        return v;
    return unions[v] = find_set (unions[v]);
}


void m_union(int x, int y){
    x = find_set(x);
    y = find_set(y);
    if (x != y ) {
        if (weights[x]> weights[y]) {
            swap(x, y);
        }
        weights[x] += weights[y];
        unions[y] = x;
    }
}



int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int q;
    cin >> n >> m >> q;
    unions.resize(n);
    weights.resize(n);
    for (int i{0}; i < n; ++i) {
        unions[i] = i;
        weights[i] = 1;
    }
    for (int i{0}; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a > b) {
            swap(a, b);
        }
        edges.insert({--a, --b});
    }


    for (int i{0}; i < q; ++i) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        info.emplace_back(c, --a, --b);
    }

    for (auto& [c, a, b]: info) {
        if (c == '-') {
            if (a > b) {
                swap(a, b);
            }
           edges.erase({a, b});
        }
    }

    for (auto& [a, b]: edges) {
        m_union(a, b);
    }

    vector<string> ans;

    reverse(info.begin(), info.end());
    for (auto& [c, a, b]: info) {
        if (c == '?') {
            if (find_set(a) == find_set(b)) {
                ans.emplace_back("YES\n");

            } else {
                ans.emplace_back("NO\n");
            }
        } else {
            m_union(a, b);
        }
    }

    reverse(ans.begin(), ans.end());
    for (auto& s: ans) {
        cout << s;
    }

}