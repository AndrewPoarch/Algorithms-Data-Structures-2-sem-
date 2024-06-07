
#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;
const int MINUS_INF = INT_MIN;
int n, m, K;

struct path{
    path() = default;
    path(int _a,int _b,int _w) :
    a(_a), b(_b), w(_w) {};
    int a, b, w;
};

bool ford_solution(vector<path>& paths) {
    vector<int> distances(n);
    vector<int> parents(n);
    int last_visited = -1;

    for (int i = 0; i < n; ++i) {
        bool is_changed = false;
        last_visited = -1;
        for (const auto& [a, b, w]: paths) {
            if (distances[b] > distances[a] + w) {
                distances[b] = distances[a] + w;
                is_changed = true;
                parents[b] = a;
                last_visited = b;
            }
        }
        if (!is_changed)
            break;
    }

    if (last_visited != -1) {
        int temp_vis = last_visited;
        for (int i = 0; i < n; ++i) {
            temp_vis = parents[temp_vis];
        }
        vector<int> route;
        for (int curv = temp_vis;; curv = parents[curv]) {
            route.push_back(curv);
            if (curv != temp_vis && route.size() > 1)
                break;
        }

        if (route.size() <= K) {
            return false;
        }
        return true;
    }

    return false;
}

int main() {
    int N;
    cin >> N >> K;

    for (int i = 0; i < N; ++i) {

        cin >> n >> m;
        vector<path> paths;
        for (int j = 0; j < m; ++j) {
            int a,b,w; cin >> a >> b >> w; --b; --a;
            paths.emplace_back(a, b, w);
        }
        if (!ford_solution(paths))
            cout << "YES\n";
        else
            cout << "NO\n";

    }

    return 0;
}