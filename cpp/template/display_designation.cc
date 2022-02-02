#include <iostream>

template <typename T1, typename T2, typename T3>
T1 sum(T2 a, T3 b) {
    return static_cast<T1>(a + b);
}

template <typename T1, typename T2, typename T3>
T3 fuck_sum(T1 a, T2 b) {
    return static_cast<T3>(a + b);
}

int main() {
    // 因为模板参数推导时不能根据传的实参推导出形参T1的类型，
    // 所以只能在尖括号里显示指定。
    std::cout << sum<int>(10, 2.5) << std::endl;
    std::cout << sum<double>(10, 2.5) << std::endl;

    std::cout << fuck_sum<int, double, double>(10, 2.5) << std::endl;

    // 错误，因为第一个参数推导出int类型，第二个参数推导出double类型
    // std::cout << std::max(10, 11.5) << std::endl;

    // 显示指定模板参数推导类型。
    std::cout << std::max<double>(10, 11.5) << std::endl;
}