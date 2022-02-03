#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace n1 {
    void go1() {
        std::vector<int> v;
        std::mutex mtx;
        std::thread t1([&] {
            for (int i = 1; i <= 1000; ++i) {
                mtx.lock();
                v.push_back(1);
                mtx.unlock();
            }
        });

        std::thread t2([&] {
            for (int i = 1; i <= 1000; ++i) {
                mtx.lock();
                v.push_back(2);
                mtx.unlock();
            }
        });

        t1.join();
        t2.join();
    }


    void go2() {
        std::vector<int> v;
        std::mutex mtx;
        std::thread t1([&] {
            for (int i = 1; i <= 1000; ++i) {
                // c++17可以不用显示指定模板参数类型，析构时会自动释放锁
                std::lock_guard grd(mtx);
                v.push_back(1);
            }
        });

        std::thread t2([&] {
            for (int i = 1; i <= 1000; ++i) {
                std::lock_guard grd(mtx);
                v.push_back(2);
            }
        });

        t1.join();
        t2.join();
    }

    void go3() {
        std::mutex mtx;
        if (mtx.try_lock()) {
            std::cout << "success1.\n";
        } else {
            std::cout << "fail1.\n";
        }

        if (mtx.try_lock()) {
            std::cout << "success2.\n";
        } else {
            std::cout << "fail2.\n";
        }
    }


}
int main() {
    n1::go3();
    return 0;
}
