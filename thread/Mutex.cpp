#include <iostream>
#include <thread>
#include<mutex>

std::mutex mtx;

void print() {

    try {
        std::this_thread::sleep_for(std::chrono::seconds(2));

//        std::cout << "锁的临界区" << std::this_thread::get_id() << ::std::endl;
        mtx.lock();

        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << std::this_thread::get_id() << "获得锁，访问共享资源" << ::std::endl;
        return;
//        throw std::runtime_error("error");
    } catch (const std::exception &e) {
        std::cerr << "error: " << e.what() << std::endl;
    }
//    throw std::runtime_error("error1");
//    mtx.unlock();
}

int main() {

    std::thread thread1(print);
    std::thread thread2(print);
    try {
        thread1.join();
        thread2.join();
    } catch (const std::exception &e) {
        std::cerr << "error2: " << e.what() << std::endl;
    }
    std::cout << std::this_thread::get_id() << "main线程执行结束" << ::std::endl;
    return 0;
}