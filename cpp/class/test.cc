#include <iostream>

constexpr char s[] = "hello";

int main() {
    *(++s) = 'w';
    std::cout << s;
}
