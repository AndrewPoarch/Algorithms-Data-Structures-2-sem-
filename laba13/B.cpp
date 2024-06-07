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

vector<int> PrefixFunction(const string& str) {
    int n = str.length();
    vector<int> pref(n);
    for (int i = 1; i < n; ++i) {
        int j = pref[i - 1];
        while (j > 0 && str[i] != str[j]) {
            j = pref[j - 1];
        }
        if (str[i] == str[j])
            ++j;

        pref[i] = j;
    }
    return pref;
}

signed main() {
    string T;
    cin >> T;

    vector<int> ans = PrefixFunction(T);
    cout << ans.size() << '\n';
    for (const auto& el: ans) {
        cout << el << ' ';
    }

    return 0;
}