#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;

using m_int = unsigned long long;
using mtree = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;


const m_int INF = UINT64_MAX;
int n, q;
vector<int> unions;
vector<int> weights;
vector<mtree> galaxies;


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
        weights[y] += weights[x];
        unions[x] = y;
        for (auto galaxy: galaxies[x]) {
            galaxies[y].insert(galaxy);
        }
    }
}

int find_median(int num) {
    int index = (weights[num] - 1) / 2;
    auto ans = galaxies[num].find_by_order(index);

    return *ans;
}

void start(int x) {
    weights.resize(x);
    unions.resize(x);
    galaxies.resize(x);
    for (int i = 0; i < n; ++i) {
        unions[i] = i;
        galaxies[i].insert(i);
        weights[i] = 1;
    }
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;

    start(n);
    for (int i = 0; i < q; ++i) {
        int t; cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b; --a; --b;
            m_union(a, b);
        } else {
            int a; cin >> a; --a;
            a = find_set(a);
            cout << find_median(a) + 1 << '\n';
        }
    }

    return 0;
}