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
#define INF M7 * M7
#define CONST 1000000000;
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()

bool goodName(const string& word) {
    if (std::islower(word[0])) {
        return false;
    }

    return all_of(word.begin(), word.end(), ::isalpha);;
}

bool isAge(const string& age) {
    if (age.length() > 2) {
        return false;
    }

    return all_of(age.begin(), age.end(), ::isdigit);
}

bool is_phone(const string& phone) {
    std::size_t size = phone.size();
    if (phone[0] != '7' && phone[0] != '8' && !(phone.substr(0, 2) == "+7")) {
        return false;
    }
    if (size == 11) {
        if (!all_of(phone.begin(), phone.end(), ::isdigit)) {
            return false;
        }
    } else if (size == 12) {
        if (!all_of(phone.begin() + 1, phone.end(), ::isdigit)) {
            return false;
        }
    } else if (size == 15) {
        if (!(phone[2] == '(' && isdigit(phone[3]) && isdigit(phone[4]) && isdigit(phone[5])
            && phone[6] == ')' && isdigit(phone[7]) && isdigit(phone[8]) && isdigit(phone[9]) &&
            phone[10] == '-' && isdigit(phone[11]) && isdigit(phone[12]) && isdigit(phone[13]) && isdigit(phone[14])
        )) {
            return false;
        }
    } else if (size == 17) {
        if (!(phone[2] == '(' && isdigit(phone[3]) && isdigit(phone[4]) && isdigit(phone[5])
            && phone[6] == ')' && phone[7] == '-' && isdigit(phone[8]) && isdigit(phone[9]) && isdigit(phone[10]) &&
            phone[11] == '-' && isdigit(phone[12]) && isdigit(phone[13]) && phone[14] == '-' && isdigit(phone[15])
            && isdigit(phone[16])
        )) {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

bool full_name(const string& str) {
    std::istringstream iss(str);
    string name, surname, patronymic;
    iss >> name >> surname >> patronymic;

    return goodName(name) && goodName(surname) && goodName(patronymic);
}

bool full_address(const string& address) {
    size_t city_pos = address.find("g.");
    size_t comma_pos = address.find(',');
    if (comma_pos == string::npos) {
        return false;
    }
    string city = address.substr(city_pos + 2, comma_pos - city_pos - 2);
    if (!all_of(city.begin(), city.end(), ::isupper)) {
        return false;
    }
    size_t pos_ul = address.find("ul.");
    size_t comma_pos2 = address.find(',', comma_pos + 1);
    if (comma_pos2 == string::npos) {
        return false;
    }
    string street = address.substr(pos_ul + 3, comma_pos2 - pos_ul - 3);
    if (!(std::isupper(street[0]) && all_of(street.begin() + 1, street.end(), ::isalpha))) {
        return false;
    }
    size_t pos_d = address.find("d.");
    string house = address.substr(pos_d + 2);
    if (house.length() < 2 || !all_of(house.begin(), house.end(), ::isdigit)) {
        return false;
    }

    return true;
}

signed main() {
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        string data;
        getline(cin, data);
        size_t space1 = data.find(' ');
        size_t space2 = data.find(' ', space1 + 1);
        size_t space3 = data.find(' ', space2 + 1);
        size_t space4 = data.find(' ', space3 + 1);

        if (space1 == string::npos ||  space2 == string::npos ||  space3 == string::npos || space4 == string::npos) {
            cout << "NO\n";
            continue;
        }

        string name = data.substr(0, space3);
        string age = data.substr(space3 + 1, 2);
        string phone = data.substr(space4 + 1, data.find(' ', space4 + 1) - space4 - 1);
        string address = data.substr(space4 + phone.length() + 2);

        if (!full_name(name) || !isAge(age) || !is_phone(phone) || !full_address(address)) {
            cout << "NO\n";

        } else {
            cout << "YES\n";
        }
    }
    return 0;
}