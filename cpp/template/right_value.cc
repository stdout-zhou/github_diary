#include <iostream>

template <typename T>
void f1(T&) {

}

template <typename T>
void f2(const T&) {

}

template <typename T>
void f3(T&&) {

}

int main() {
    // 不能把一个右值绑定到T&
    // f1(5);
    f2(5);

    f3(5);
    int x = 5;
    // 把一个右值引用绑定到左值也是可以的
    f3(x);
}