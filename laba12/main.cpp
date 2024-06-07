#include <iostream>
#include <vector>

void f(int a,const std::string& b) {
    printf("%d, %s", a, b.c_str());
    std::vector<unsigned long long> n(10000000000);
}

template <typename Function, typename... Args>
void log(const Function& f, const Args&... args) {
    try {
        f(args...);
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

int main() {
    log(f, 1, "10");
    return 0;
}
