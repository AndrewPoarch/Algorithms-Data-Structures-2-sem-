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


signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> vec;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        vec.push_back(x);
    }

    for (int i = vec.size() / 2; i >= 0; --i) {
        int id1 = i;
        int id2 = i - 1;

        bool f1 = true;
        while (id1 < vec.size() && id2 >= 0) {
            if (vec[id1] != vec[id2]) {
                f1 = false;
            }
            ++id1;
            --id2;
        }
        if (f1) {
            ans.push_back(n - i);
        }
    }


    for (long long an : ans) {
        cout << an << ' ';
    }



    return 0;
}