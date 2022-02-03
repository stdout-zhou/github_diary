#include <iostream>
#include <string>
#include <thread>
#include <vector>

std::vector<std::thread> pool;

namespace n1 {
    void download() {
        for (int i = 1; i <= 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "download " << i * 10 << "%\n";
        }
        std::cout << "Finish download.\n";
    }

    void interact() {
        std::string s;
        std::cin >> s;
        std::cout << "hi, " << s << std::endl;
    }

    void func() {
        // 在func函数退出时，由于thread对象解构，会销毁线程。
        std::thread t1([&] {
            download();
        });
        // detach可以分离thread对象和线程
        t1.detach();
    }

    void func2() {
        std::thread t1([&] {
            download();
        });
        // 为了不让thread析构，可以把它放到一个全局的池子里延长生命周期
        // thead没有拷贝构造，要用移动构造。
        pool.push_back(std::move(t1));
    }

    void go1() {
        std::thread t1([&] {
            download();
        });
        interact();
        std::cout << "wait child thread...\n";
        // join会让主线程阻塞，直到t1线程运行完毕
        t1.join();
        std::cout << "main thread exit.\n";
    }

    void go2() {
        func();
        interact();
    }

    void go3() {
        func2();
        interact();
        for (auto &t : pool) {
            t.join();
        }
    }
}

int main() {
    // go1让子线程join，主线程会等待子线程运行完，但是这样可能会死锁
    //n1::go1();

    // go2,子线程detach,这样做在函数退出后线程可以继续后台执行，
    // 但是主线程不会等待子线程运行完。
    //n1::go2();

    // go3
    n1::go3();

    // go4, go3是显式地join所有线程，我们可以自定义一个thead_pool类，
    // 让它在析构函数里join,这样主函数将要退出时会调用析构函数。

    // go5, c++20里使用jthead代替了thead,jthread在析构时会自动join
}
