#include <iostream>

template <typename T>
void fobj(T, T) {
    std::cout << "Run fobj function" << std::endl;
}

template <typename T>
void fref(const T&, const T&) {
    std::cout << "Run fref function" << std::endl;
}

template <typename T>
void f1(T, T) {

}
int main() {
    // The type conversation is ok.
    std::string s1("s1 string");
    const std::string s2("s2 string");
    fobj(s1, s2);
    fref(s1, s2);

    int a1[10], a2[20];
    // ok.
    // a1 and a2 will be derived to points.
    fobj(a1, a2);

    // The compiler will complain type error.
    // Why?
    // When pass the arguments to the template function, a1 is an ref to a array
    // size 10 but a2 is an ref variable to an array size 20.
    // fref(a1, a2);

    //fref("hi", "world");
    // ok, they are both char[5].
    fref("hello", "world");

    // 模板参数推导时会忽略实参本身的常量性
    int i = 0, j = 42;
    const int *cp1 = &i;
    int *cp2 = &j;
    // 报错，因为cp1是一个指向常量的指针,它们类型不一致
    //f1(cp1, cp2);
}