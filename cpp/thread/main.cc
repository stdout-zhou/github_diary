#include <iostream>
#include <string>
#include <thread>

void download() {
    for (int i = 1; i <= 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "download " << i * 10 << "%\n";
    }
    std::cout << "Finish download.\n";
}

void interact(std::string s) {
    std::cout << "hi, " << s << std::endl;
}

int main() {
    std::thread t1([&] {
        download();
    });
    std::string s;
    std::cin >> s;
    interact(s);
    std::cout << "wait child thread...\n";
    t1.join();
    std::cout << "main thread exit.\n";
    return 0;
}