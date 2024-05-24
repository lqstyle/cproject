#include <iostream>
#include <thread>
#include<mutex>


std::mutex mtx;
std::recursive_mutex mtx1;
std::recursive_mutex mtx2;
std::recursive_mutex mtx3;

void process() {
//    mtx.unlock();
    mtx.lock();

    ::std::cout << std::this_thread::get_id << " : first lock" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx.lock();
    ::std::cout << std::this_thread::get_id << "：second lock" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx.unlock();
    ::std::cout << std::this_thread::get_id << "：first unlock" << ::std::endl;
    mtx.unlock();
    ::std::cout << std::this_thread::get_id << "：second unlock" << ::std::endl;
}

void processWithReCursive() {
    mtx1.lock();
    ::std::cout << std::this_thread::get_id << " :first lock recursive" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx1.lock();
    ::std::cout << std::this_thread::get_id << " :second lock recursive" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mtx1.unlock();
    ::std::cout << std::this_thread::get_id << " :first unlock recursive" << ::std::endl;
    mtx1.unlock();
    ::std::cout << std::this_thread::get_id << " :second unlock recursive" << ::std::endl;
//    mtx1.unlock();
//    ::std::cout << std::this_thread::get_id << " :third unlock recursive" << ::std::endl;
}

void processLgWithReCursive1() {
    std::lock_guard<std::recursive_mutex> guard(mtx2);
    ::std::cout << std::this_thread::get_id << " :second lock recursive lock_guard" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

}

void processLgWithReCursive() {
    std::lock_guard<std::recursive_mutex> guard(mtx2);
    ::std::cout << std::this_thread::get_id << " :first lock recursive lock_guard" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    processLgWithReCursive1();
}


void processulWithReCursive1() {
    std::unique_lock<std::recursive_mutex> guard(mtx2);
    ::std::cout << std::this_thread::get_id << " :second lock recursive unique_lock" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

}

void processUlWithReCursive() {
    std::unique_lock<std::recursive_mutex> lck(mtx3,std::defer_lock);
//    lck.unlock();
    ::std::cout << std::this_thread::get_id << " :first lock recursive unique_lock" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    processulWithReCursive1();
}


void processLgWithMtx1() {
    std::lock_guard<std::mutex> guard(mtx);
    ::std::cout << std::this_thread::get_id << " :second lock  lock_guard" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

}

void processLgWithMtx() {
    std::lock_guard<std::mutex> guard(mtx);
    ::std::cout << std::this_thread::get_id << " :first lock  lock_guard" << ::std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    processLgWithMtx1();
}


int main() {
    // mutex
//    std::thread thread1(process);
    //  recursive_mutex
//    std::thread thread1(processWithReCursive);
    //lock_guard
//    std::thread thread1(processLgWithReCursive);
    //lock_guard
//    std::thread thread1(processLgWithMtx);
    // unique_lock
    std::thread thread1(processUlWithReCursive);
    thread1.join();

    return 0;
}