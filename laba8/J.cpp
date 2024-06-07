#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct door {
    door() = default;

    door (int tto) {
        to = tto;
    }

    door(int tto, int l, int r) {
        to = tto;
        a = l;
        b = r;
    }

    int to, a, b{};
};

bool bfs_check(int n, vector<vector<door>>& g, int frank_bottom, int frank_top) {
    vector<bool> mark(n, false);
    mark[0] = true;

    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto& el : g[cur]) {
            if (el.a <= frank_bottom && frank_top <= el.b && !mark[el.to]) {
                mark[el.to] = true;
                q.push(el.to);
            }
        }
    }

    return mark[n - 1];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> prs(m);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        prs[i] = {--x, --y};
    }

    vector<vector<door>> g(n, vector<door>());
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        g[prs[i].first].push_back({prs[i].second, l, r});
        g[prs[i].second].push_back({prs[i].first, l, r});
    }

    int dmax = -1;
    int answer = -1;
    vector<int> min_doors;

    for (int i = 0; i < n; ++i) {
        for (auto& le: g[i]) {
            min_doors.push_back(le.a);
            dmax = max(dmax, le.b);
        }

    }
    sort(min_doors.begin(), min_doors.end());
    min_doors.resize(unique(min_doors.begin(), min_doors.end()) - min_doors.begin());


    for (auto& el: min_doors) {
        if (!bfs_check(n, g, el, el)) {
            continue;
        }
        int l = el, r = dmax + 1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (bfs_check(n, g, el, mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        answer = max(answer, l - el + 1);
    }

    std::cout << answer;

    return 0;
}