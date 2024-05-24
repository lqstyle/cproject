#include <iostream>
#include <thread>
#include<mutex>

std::mutex mtx1;
std::timed_mutex mtx2;


void testLockWithDefer();


void processDefault() {

    std::unique_lock<std::mutex> ul1(mtx1);
    if (ul1.owns_lock()) {
        ::std::cout << std::this_thread::get_id() << " get lock success" << ::std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    } else {
        ::std::cout << std::this_thread::get_id() << " get lock fail" << ::std::endl;
    }

}

void processWithDefer() {

    std::unique_lock<std::mutex> ul1(mtx1, std::defer_lock);
    if (ul1.owns_lock()) {
        ::std::cout << std::this_thread::get_id() << " get lock success" << ::std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    } else {
        ::std::cout << std::this_thread::get_id() << " no get lock,need defer" << ::std::endl;
    }

    ul1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << std::this_thread::get_id() << " has acquired the lock." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    ul1.unlock();
    std::cout << std::this_thread::get_id() << " has released the lock." << std::endl;

}

void process() {

    std::unique_lock<std::mutex> ul1(mtx1, std::try_to_lock);
    if (ul1.owns_lock()) {
        printf("%d get lock success\n",std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::seconds(2));
    } else {
        printf("%d get lock fail\n",std::this_thread::get_id());
    }

}


void processWithTime() {
    std::unique_lock<std::timed_mutex> ul1(mtx2, std::chrono::seconds(3));
    if (ul1.owns_lock()) {
        ::std::cout << std::this_thread::get_id() << " get lock success" << ::std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
    } else {
        ::std::cout << std::this_thread::get_id() << " get lock fail" << ::std::endl;
    }

}

void testLockDefault() {
    std::thread th1(processDefault);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread th2(processDefault);
    th1.join();
    th2.join();
}

void testTryLock() {
    std::thread th1(process);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread th2(process);
    th1.join();
    th2.join();
}


void testTryLockTime() {
    std::thread th1(processWithTime);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread th2(processWithTime);
    th1.join();
    th2.join();
}


int main() {

    //1、默认获取锁
//    testLockDefault();
    //2、默认不获取锁，根据条件获取
//    testLockWithDefer();
    // 尝试获得锁，获取不到则失败
    //3、 尝试获取锁
//    testTryLock();
    //4、 等待一定时间获取锁
    testTryLockTime();
    return 0;
}

void testLockWithDefer() {
    std::thread th1(processWithDefer);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread th2(processWithDefer);
    th1.join();
    th2.join();
}


