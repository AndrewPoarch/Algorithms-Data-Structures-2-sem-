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

std::mt19937_64 rnd(std::time(nullptr));

class Table {
  public:
    explicit Table(unsigned long long sz) :
        size(sz) {
        table_.resize(size);
    }

    void put(unsigned long long x) {
        table_[hash(x)].push_back(x);
    }

    unsigned long long get(unsigned long long x) {
        return *std::find(table_[hash(x)].begin(), table_[hash(x)].end(), x);
    }

    bool contains(unsigned long long x) {
        auto hs = hash(x);
        for (unsigned long long i : table_[hs]) {
            if (i == x)
                return true;
        }

        return false;
    }

    [[nodiscard]] unsigned long long hash(unsigned long long x) const {
        return ((6295 * x + 451780) % (unsigned long long)(1e9 + 9)) % size;
    }

    unsigned long long size;
    vector<vector<unsigned long long>> table_;
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n;

    vector<unsigned long long> alpha(100000, 0);
    for (int i = 0; i < 100000; ++i) {
        alpha[i] = rnd();
    }

    unsigned long long sum1 = 0;
    unsigned long long sum2 = 0;


    vector<unsigned long long> v1(n + 1);
    v1[0] = 0;

    vector<unsigned long long > str1;
    vector<unsigned long long > str2;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        str1.push_back(alpha[x]);
    }

    for (int i = 0; i < n; ++i) {
        v1[i + 1] = v1[i] + str1[i];
    }

    cin >> m;
    vector<unsigned long long> v2(m + 1);
    v2[0] = 0;

    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        str2.push_back(alpha[x]);
    }

    for (int i = 0; i < m; ++i) {
        v2[i + 1] = v2[i] + str2[i];
    }

    int mmm = min(n,m);
    Table t1(mmm * mmm);

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            t1.put(v1[j + 1] - v1[i]);
        }
    }

    int ans = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = i; j < m; ++j) {
            if (t1.contains(v2[j + 1] - v2[i])) {
                ans = max(ans, j - i + 1);
            }
        }
    }

    cout << ans;


    return 0;
}
