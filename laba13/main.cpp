#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string zToStr(const std::vector<int>& slc) {
    int k = slc.size();
    std::vector<char> res(k, ' ');
    res[0] = 'a';

    char curSym = 'b';
    int notThis = 0;
    int last = 0;

    for (int i = 1; i < k; i++) {
        int z = slc[i];
        if (z > k - i) {
            return "!";
        }
        if (z > 0) {
            for (int j = std::max(last - i, 0); j < z; j++) {
                res[i + j] = res[j];
                last = i + j;
            }
            notThis = z;
        } else {
            if (last >= i) {
                continue;
            }
            if (res[notThis] == curSym) {
                curSym = (curSym + 1 - 'a') % 26 + 'a';
            }
            res[i] = curSym;
            curSym = (curSym + 1 - 'a') % 26 + 'a';
            if (curSym == 'a') {
                curSym = 'b';
            }
            last = i;
        }
    }

    std::string str(res.begin(), res.end());

    auto zFunc = [](const std::string& s) {
      int n = s.length();
      std::vector<int> z(n);
      int l = 0, r = 0;
      for (int i = 1; i < n; i++) {
          if (i <= r) {
              z[i] = std::min(r - i + 1, z[i - l]);
          }
          while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
              z[i]++;
          }
          if (i + z[i] - 1 > r) {
              l = i;
              r = i + z[i] - 1;
          }
      }
      return z;
    };

    std::vector<int> z_values = zFunc(str);
    for (int i = 0; i < k; i++) {
        if (z_values[i] != slc[i]) {
            return "!";
        }
    }

    return str;
}

int main() {
    std::vector<int> z = {0, 0, 1, 0, 3, 0, 1, 0, 7, 0, 1, 0, 3, 0, 1};
    std::string result = zToStr(z);
    std::cout << "Восстановленная строка: " << result << std::endl;
    return 0;
}