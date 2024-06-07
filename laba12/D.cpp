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

class Table {
  public:
    explicit Table(int sz) :
        size(sz) {
        table_.resize(size);
    }

    void add(int g, int n, int p) {
        table_[hash(g)].emplace_back(n, p);
    }

    void del(int x, int n) {
        for (auto it = table_[hash(x)].begin(); it != table_[hash(x)].end(); ++it) {
            if (it->first == n) {
                table_[hash(x)].erase(it);
                return;
            }
        }
    }

    int mid(int x) {
        int sum = 0;
        for (const auto & [a, b]: table_[hash(x)]) {
            sum += b;
        }

        return sum / table_[hash(x)].size();
    }


    int max(int x) {
        int mx = 0;
        for (const auto & [a, b]: table_[hash(x)]) {
            if (b > mx) {
                mx = b;
            }
        }

        return mx;
    }



    int hash(int x) {
        return (x * 241) % size;
    }

    int size;
    std::vector<vector<pair<int, int>>> table_;
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    Table t1(n);

    for (int i = 0; i < q; ++i) {
        string a;
        cin >> a;
        int group;
        cin >> group;

        if (a == "+") {
            int isu, points;
            cin >> isu >> points;
            t1.add(group, isu, points);
        }
        if (a == "-") {
            int isu;
            cin >> isu;
            t1.del(group, isu);
        }
        if (a == "m") {
            cout << t1.max(group) << '\n';
        }
        if (a == "a") {
            cout << t1.mid(group) << '\n';
        }
    }

    return 0;
}
