#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


void findSizes(int node, int parent, const vector<vector<int>>& graph, vector<int>& sizes) {
    sizes[node] = 1;
    for (int child: graph[node]) {
        if (child != parent) {
            findSizes(child, node, graph, sizes);
            sizes[node] += sizes[child];
        }
    }
}

int findCentroid(int node, int parent, int n, const vector<vector<int>>& graph, const vector<int>& sizes) {
    bool is_centroid = true;
    int heavy_child = -1;
    for (int child: graph[node]) {
        if (child != parent && sizes[child] > n / 2) {
            is_centroid = false;
            heavy_child = child;
            break;
        }
    }
    if (is_centroid && n - sizes[node] <= n / 2) return node;
    return findCentroid(heavy_child, node, n, graph, sizes);
}

string canonicalForm(int node, int parent, const vector<vector<int>>& graph) {
    vector<string> children;
    for (int child: graph[node]) {
        if (child != parent) {
            children.push_back(canonicalForm(child, node, graph));
        }
    }
    sort(children.begin(), children.end());
    string result = "(";
    for (const string& s: children) result += s;
    result += ")";
    return result;
}

bool compareTrees(const vector<vector<int>>& tree1, const vector<vector<int>>& tree2) {
    int n = tree1.size() - 1;
    vector<int> sizes1(n + 1, 0), sizes2(n + 1, 0);

    findSizes(1, -1, tree1, sizes1);
    findSizes(1, -1, tree2, sizes2);

    int centroid1 = findCentroid(1, -1, n, tree1, sizes1);
    int centroid2 = findCentroid(1, -1, n, tree2, sizes2);

    string form1 = canonicalForm(centroid1, -1, tree1);
    string form2 = canonicalForm(centroid2, -1, tree2);

    return form1 == form2;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> tree1(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree1[u].push_back(v);
        tree1[v].push_back(u);
    }
    vector<vector<int>> tree2(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree2[u].push_back(v);
        tree2[v].push_back(u);
    }

    if (compareTrees(tree1, tree2)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
