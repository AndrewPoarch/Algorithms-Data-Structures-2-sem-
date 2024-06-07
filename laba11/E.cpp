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
#define M7 1'000'000'007LL;
#define INF M7 * M7
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define eps 1e-6

struct partner {
    partner(int num_, char type_) :
        num(num_), condition(type_) {};

    int num;
    char condition;
};

int N;
vector<vector<partner>> males;
vector<vector<partner>> females;


int find_free_man(vector<bool>& in_pair) {
    for (int i = 0; i < in_pair.size(); ++i) {
        if (!in_pair[i]) {
            return i;
        }
    }

    return -1;
}

bool has_pair(vector<partner>& v) {
    for (const auto& man: v) {
        if (man.condition == 'M') {
            return true;
        }
    }

    return false;
}

void make_marked(vector<partner>& v, int x) {
    for (auto & i : v) {
        if (i.num == x) {
            i.condition = 'M';
            return;
        }
    }
}
void make_free(vector<partner>& v, int x) {
    for (auto & i : v) {
        if (i.num == x) {
            i.condition = 'F';
            return;
        }
    }
}

int choose_man(vector<partner>& v, int x) {
    for (const auto& man: v) {
        if (man.num == x) {
            return x;
        }
        if (man.condition == 'M') {
            return man.num;
        }
    }
}

int fem_find(vector<partner>& v) {
    for (auto& f: v) {
        if (f.condition == 'X')
            continue;
        return f.num;
    }
}

void printc(vector<bool>& v) {
    int ans = 0;
    for (auto el: v) {
        if (el) ++ans;
    }

    cout << ans << '\n';
}

int index_find(vector<partner>& v, int x) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i].num == x) {
            return i;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    males.resize(N);
    females.resize(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            cin >> x;
            males[i].emplace_back(x, 'F');
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            cin >> x;
            females[i].emplace_back(x, 'F');
        }
    }

    vector<bool> male_has_pair(N, false);

    vector<pair<int, int>> ans;



    while (find_free_man(male_has_pair) != -1) {
        int man = find_free_man(male_has_pair);
        int fem = fem_find(males[man]);
        if (!has_pair(females[fem])) {
            male_has_pair[man] = true;
            make_marked(males[man], fem);
            make_marked(females[fem], man);
        } else if (choose_man(females[fem], man) == man) {
            int looser = -1;
            for (auto& m: females[fem]) {
                if (m.condition == 'M') {
                    looser = m.num;
                    m.condition = 'F';
                }
            }

            if (looser != -1) {
                male_has_pair[looser] = false;
                males[man][index_find(males[man], fem)].condition = 'X';
            }

            make_marked(males[man], fem);
            make_marked(females[fem], man);
            male_has_pair[man] = true;
        } else {
            males[man][index_find(males[man], fem)].condition = 'X';
        }
    }

    for (int i = 0; i < males.size(); ++i) {
        for (const auto& fem: males[i]) {
            if (fem.condition == 'M') {
                ans.emplace_back(i, fem.num);
                continue;
            }
        }
    }

    for (auto [a, b]: ans) {
        cout << a << ' ' << b << '\n';
    }

    return 0;
}
