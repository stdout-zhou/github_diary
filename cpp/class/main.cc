#include <iostream>
#include <string>

class Pig {
public:
    int weight_;
    std::string name_;
    explicit Pig(int weight, std::string name) : weight_(weight), name_(name) {

    }

    Pig(int weight) : weight_(weight), name_("test") {

    }
    // 自定义构造函数以后，编译期不再生成无参构造函数
    // 可以用这种办法仍然生成一个无参构造函数。
    Pig() = default;

    // 编译器会默认生成拷贝构造函数，可以删除它
    // 默认的拷贝构造都是深拷贝，我们可以删除它以后用智能指针管理（浅拷贝）
    //Pig(Pig const &pig) = delete;

    // 第一个调拷贝构造，第二个先调用无参构造再调用赋值构造，第一个效率高一点。
    // Pig pig1 = pig2;
    // Pig pig1; pig1 = pig2;
};

void show(Pig pig) {
    std::cout << "name: " << pig.name_ << std::endl;
    std::cout << "weight" << pig.weight_ << std::endl;
}

int main() {
    // modern c++支持使用列表初始化对象，但是这种转换是隐式的
    // 如果构造函数只有一个参数，那么你甚至可以省略{},这种code style
    // 其实很不好
    // Pig pig = {80, "peiki"};
    // show({90, "peiki"});
    Pig pig2 = 80;


    // 构造函数加了explict关键字以后只能显式初始化
    // {} 和 (), {}不会发生强制类型转换
    // Pig pig{80f, "peiki"}; 会报错
    // Pig pig(80f, "peiki"); 不会报错
    // 使用{}初始化对象是好的工程习惯，遵循google code style
    Pig pig{80, "peiki"};
    show(Pig{90, "peiki"});

    // c++ 20支持打乱列表参数来构造对象
    // Pig pig3{.name_="pig3", .weight_=10};

    Pig pig3;
}
