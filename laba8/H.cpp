#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs1(int x, vector<bool>& mark, vector<vector<int>>& graph, vector<int>& tout) {
    mark[x] = true;
    for (int i = 0; i < graph[x].size(); ++i) {
        int current = graph[x][i];
        if (!mark[current]) {
            dfs1(current, mark, graph, tout);
        }
    }
    tout.push_back(x);
}

void dfs2(int x, int type, vector<vector<int>>& rgraph, vector<int>& family) {
    family[x] = type;
    for (int i = 0; i < rgraph[x].size(); ++i) {
        int current = rgraph[x][i];
        if (family[current] == -1) {
            dfs2(current, type, rgraph, family);
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    vector<vector<int>> graph(n*2);
    vector<vector<int>> rgraph(n*2);
    vector<bool> mark(n*2);

    for (int i = 0; i < m; ++i) {
        while (cin.peek() != '!' && !isdigit(cin.peek())) {
            auto c = cin.get();a
        }
        if (cin.peek() == '!') {
            char c; cin >> c;
            int x; cin >> x; --x;
            graph[x].push_back(x + n);
        } else {
            int x, y;
            string symbol;
            cin >> x >> symbol >> y;
            --x, --y;
            if (symbol[0] == '&') {
                graph[x + n].push_back(x);
                graph[y + n].push_back(y);
            } else if (symbol == "->") {
                graph[x].push_back(y);
                graph[x + n].push_back(y + n);
            } else if (symbol == "||") {
                graph[x + n].push_back(y);
                graph[y + n].push_back(x);
            } else if (symbol == "^") {
                graph[x + n].push_back(y);
                graph[y + n].push_back(x);
                graph[x].push_back(y + n);
                graph[y].push_back(x + n);
            }
        }
    }

    for (int i = 0; i < n * 2; ++i) {
        for (int j : graph[i]) {
            rgraph[j].push_back(i);
        }
    }

    vector<int> topord;
    for (int i = 0; i < n; ++i) {
        if (!mark[i])
            dfs1(i, mark, graph, topord);
        if (!mark[i + n])
            dfs1(i + n, mark, graph, topord);
    }

    vector<int> family(n * 2, -1);
    reverse(topord.begin(), topord.end());
    int type = 0;
    for (int i: topord) {
        if (family[i] == -1)
            dfs2(i, type++, rgraph, family);
    }


    for (int i = 0; i < n; ++i) {
        if (family[i] == family[i + n] && family[i] != -1) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}