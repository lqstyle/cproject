#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void do_something() {
    // 假设这里有一些操作可能会抛出异常
    ::std::cout << "process do_something" << ::std::endl;
    throw std::runtime_error("Something went wrong do_something");
}

void not_exception_safe() {
    mtx.lock(); // 锁定互斥量
    try {
        do_something(); // 可能会抛出异常
    } catch (...) {
        ::std::cout << "process not_exception_safe" << ::std::endl;
        mtx.unlock(); // 如果发生异常，需要解锁
        throw ; // 重新抛出异常
    }
    mtx.unlock(); // 如果没有异常，需要解锁
}

int main() {
    std::thread t(not_exception_safe);
    t.join();
    ::std::cout << "process main" << ::std::endl;
    return 0;
}