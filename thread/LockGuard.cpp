#include <iostream>
#include <thread>
#include<mutex>

int number = 0;

std::mutex gmtx;


void safe_increment() {
    std::lock_guard<std::mutex> guard(gmtx);
    for (int i = 0; i < 1000; i++) {
        ++number;
    }
    std::cout << std::this_thread::get_id() << ": " << number << '\n';
}

int main() {
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);

    t1.join();
    t2.join();
    std::cout << "main: " << number << '\n';

    return 0;
}