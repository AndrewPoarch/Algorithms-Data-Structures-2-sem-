#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000000;

int n, m;
vector<vector<int>> g;
vector<size_t> degrees;
vector<int> parent;

void dfs(int v) {
    for (size_t i = 0; i < g[v].size(); ++i) {
        int el = g[v][i];
        if (el != parent[v]) {
            parent[el] = v;
            dfs(el);
        }
    }
}

[[noreturn]] vector<int> solution() {

    parent[n - 1] = -1;
    dfs(n - 1);

    int ptr = -1;
    for (int i = 0; i < n; ++i) {
        degrees[i] = g[i].size();
        if (degrees[i] == 1 && ptr == -1)
            ptr = i;
    }

    vector<int> prufer;
    int l = ptr;
    for (int i = 0; i < (n - 2); ++i) {
        int next = parent[l];
        prufer.push_back(next);
        --degrees[next];
        if (degrees[next] == 1 && next < ptr)
            l = next;
        else {
            ++ptr;
            while ( ptr < n && degrees[ptr] != 1)
                ++ptr;
            l = ptr;
        }
    }

    return prufer;
}


int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    g.resize(n);
    degrees.resize(n);
    parent.resize(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b; --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto ans = solution();

    for (auto c: ans)
        cout << ++c << ' ';


    return 0;
}