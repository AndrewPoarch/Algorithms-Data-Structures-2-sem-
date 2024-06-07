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
#define INF M7 * M7
#define CONST 1000000000;
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()

auto Zfunction(const string& s) {
    size_t n = s.length();
    vector<int> z_vec(n);
    int l = 0;
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (i <= r) {
            z_vec[i] = min(r - i + 1, z_vec[i - l]);
        }
        while (i + z_vec[i] < n && s[z_vec[i]] == s[i + z_vec[i]]) {
            ++z_vec[i];
        }
        if (i + z_vec[i] - 1 > r) {
            l = i;
            r = i + z_vec[i] - 1;
        }
    }

    return z_vec;
}

signed main() {
//    string T, X;
//    cin >> T >> X;
//    string S = X + "#" + T;
//    auto z = Zfunction(S);
//    vector<int> ans;
//    for (int i = X.size() + 1; i < S.size(); ++i) {
//        if (z[i] == X.size()) {
//            ans.push_back(i);
//        }
//    }
//    cout << ans.size() << '\n';
//    for (const auto& i : ans) {
//        cout << i - X.size() - 1 << ' ';
//    }

string s;
    cin >> s;
    vector<int> z = Zfunction(s);
    for (long long i : z) {
        cout << i << ' ';
    }
    return 0;
}