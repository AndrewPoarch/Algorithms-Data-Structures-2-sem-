#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int lim = INT_MAX;
const int s_size = 110;

int space[s_size][s_size][s_size];
int distances[s_size][s_size][s_size];

int main() {
    int k, e;
    cin >> k >> e;
    int x, y, z;
    cin >> x >> y >> z;
    vector<int> start{x, y, z};
    cin >> x >> y >> z;
    vector<int> finish{x, y, z};

    for (int i = 0; i < k; ++i) {
        int h;
        cin >> x >> y >> z >> h;
        for (int j = 0; j < h; ++j)
            space[x][y][z + j] = -1;
    }

    for (auto& distance : distances) {
        for (auto& i : distance) {
            for (int& j : i) {
                j = lim;
            }
        }
    }

    distances[start[0]][start[1]][start[2]] = 0;
    queue<vector<int>> q;
    q.push(start);

    while (!q.empty()) {
        vector<int> top = q.front();
        q.pop();
        for (int axis = 0; axis < 3; ++axis) {
            vector<int> cur = top;
            ++cur[axis];
            cur[axis] = min(max(cur[axis], 0), 102);

            if (space[cur[0]][cur[1]][cur[2]] != -1 && distances[cur[0]][cur[1]][cur[2]] == lim) {
                distances[cur[0]][cur[1]][cur[2]] = distances[top[0]][top[1]][top[2]] + 1;
                q.push(cur);
            }

            vector<int> minus_cur = top;
            --minus_cur[axis];
            minus_cur[axis] = min(max(minus_cur[axis], 0), 102);

            if (space[minus_cur[0]][minus_cur[1]][minus_cur[2]] != -1 && distances[minus_cur[0]][minus_cur[1]][minus_cur[2]] == lim) {
                distances[minus_cur[0]][minus_cur[1]][minus_cur[2]] = distances[top[0]][top[1]][top[2]] + 1;
                q.push(minus_cur);
            }
        }
    }

    int distance = distances[finish[0]][finish[1]][finish[2]];
    if (distance <= e) {
        cout << distance;
    } else {
        cout << -1;
    }


    return 0;
}