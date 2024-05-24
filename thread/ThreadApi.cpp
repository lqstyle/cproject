#include <iostream>
#include <thread>

void run() {

    std::this_thread::yield();
    std::cout << "thread sleep " << std::this_thread::get_id() << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "thread end " << std::this_thread::get_id() << ::std::endl;
}


void run1() {
    // 获取当前时间点
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "Sleeping ... " << std::this_thread::get_id() << " " << std::ctime(&now_c) << std::endl;

    // 设置目标时间点
    std::chrono::system_clock::time_point target = now + std::chrono::seconds(10); // 10秒后

    // 使当前线程暂停执行直到目标时间点
    std::this_thread::sleep_until(target);
    time_t now_c1 = std::chrono::system_clock::to_time_t(target);

    // 线程在目标时间点之后恢复执行
    std::cout << "Sleeping 10 seconds... " << std::this_thread::get_id() << " " << std::ctime(&now_c1)
              << std::endl;
}

int main() {

    ::std::cout << std::this_thread::get_id() << ::std::endl;

    std::thread mythread(run);
    std::thread mythread1(run1);

    mythread.join();
    mythread1.join();
    ::std::cout << "main end" << ::std::endl;
    return 0;
}
