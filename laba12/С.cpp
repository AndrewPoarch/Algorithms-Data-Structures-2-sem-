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


class Table{
  public:
    Table() {
        table_.resize(size, 0);
    }

    void put(int x) {
        table_[hash(x)] = x;
    }

    int get(int x) {
        return table_[hash(x)];
    }

    int hash(int x) {
        return x % size;
    }

    const int size = 1'000'000'000;
    std::vector<int> table_;
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    Table t1;
    Table t2;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        t1.put(x);
    }

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        t2.put(x);
    }

    cout << equal(t1.table_.begin(), t1.table_.end(), t2.table_.begin());

    return 0;
}
