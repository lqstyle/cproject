#include <iostream>
#include <thread>
#include<mutex>

std::mutex mtx;
std::mutex mtx1;

void print(std::mutex &mtx, int time) {

    try {
        mtx.lock();

        std::this_thread::sleep_for(std::chrono::seconds(time));
        printf("获得锁：%d\n", std::this_thread::get_id());
    } catch (const char *error) {
        std::cerr << "error: " << error << std::endl;
    }
    //throw "error";
    mtx.unlock();
}


int main() {

    std::thread thread1(print, std::ref(mtx), 2);
    std::thread thread2(print, std::ref(mtx1), 2);
    thread1.join();
    thread2.join();
    std::cout << std::this_thread::get_id() << ::std::endl;
    return 0;
}