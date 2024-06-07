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
#define int long long
#define M7 1'000'000'007LL;
#define INF M7 * M7
#define CONST 1000000000;
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define eps 1e-6

struct Name {
    bool v_[3]{false, false, false};
    string name_ = "#";
};

class Table {
  public:
    explicit Table(int sz) :
        size(sz) {
        table_1.assign(size, Name{});
        table_2.assign(size, Name{});
    }

    void add(string& x, int id) {
        auto hs = get_polH(x);
        auto h1 = hash1(hs);
        auto h2 = hash2(hs);
        if (table_1[h1].name_ == "#") {
            table_1[h1].name_ = x;
            table_1[h1].v_[id] = true;
        } else if (table_2[h2].name_ == "#") {
            table_2[h2].name_ = x;
            table_2[h2].v_[id] = true;
        } else {
            auto nm = table_1[h1];
            table_1[h1].name_ = x;
            table_1[h1].v_[id] = true;
            auto nhs = get_polH(nm.name_);
            table_2[hash2(nhs)] = nm;
        }
    }

    void update(string& x, int id) {
        auto hs = get_polH(x);
        auto h1 = hash1(hs);
        auto h2 = hash2(hs);
        if (table_1[h1].name_ == x) {
            table_1[h1].v_[id] = true;
        } else if (table_2[h2].name_ == x) {
            table_2[h2].v_[id] = true;
        }
    }

    int get_polH(string& str) {
        int h = 0;

        for (int i = 0; i < str.length(); ++i) {
            h = (h * 97 + str[i]) % mod1;
        }

        return h;
    }

    bool contains(string& x) {
        auto hs = get_polH(x);
        auto h1 = hash1(hs);
        auto h2 = hash2(hs);

        if (table_1[h1].name_ == x)
            return true;
        if (table_2[h2].name_ == x)
            return true;

        return false;
    }

    int hash1(int x) {
        return ((6295 * x + 451780) % mod2) % size;
    }

    int hash2(int x) {
        return ((1246 * x + 627032) % (mod1)) % size;
    }

    int mod1 = 1e9 + 7;
    int mod2 = 1e9 + 9;
    int size;
    vector<Name> table_1;
    vector<Name> table_2;
};

void Count(Name& name, vector<int>& ans) {
    if (name.v_[0]) {
        if (name.v_[1]) {
            if (!name.v_[2]) {
                ans[0] += 1;
                ans[1] += 1;
            }
        } else if (name.v_[2]) {
            ans[0] += 1;
            ans[2] += 1;
        } else {
            ans[0] += 3;
        }
    } else {
        if (name.v_[1]) {
            if (name.v_[2]) {
                ans[1] += 1;
                ans[2] += 1;
            } else {
                ans[1] += 3;
            }
        } else if (name.v_[2]) {
            ans[2] += 3;
        }
    }
}

signed main() {
    int n;

    cin >> n;

    Table t1(1000000);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            string lab_name;
            cin >> lab_name;

            if (!t1.contains(lab_name)) {
                t1.add(lab_name, i);
            } else {
                t1.update(lab_name, i);
            }
        }
    }

    vector<int> sums{0, 0, 0};

    for (auto& el : t1.table_1) {
        if (el.name_ == "#")
            continue;
        Count(el, sums);
    }
    for (auto& el : t1.table_2) {
        if (el.name_ == "#")
            continue;
        Count(el, sums);
    }

    for (int sum : sums) {
        cout << sum << ' ';
    }

    return 0;
}
