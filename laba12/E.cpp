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

int ans = 0;

class Table {
  public:
    explicit Table(int sz) :
        size(sz) {
        table_.resize(size);
    }

    void add(int x, int i) {
        ans += table_[hash(x, i)];
        table_[hash(x, i)]++;
    }


    int hash(int x, int i) {
        return (x - i) + size/2;
    }

    int size;
    vector<int> table_;
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    Table t1(2*n);

    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        t1.add(x, i);
    }


    cout << ans;

    return 0;
}
