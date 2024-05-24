#include <iostream>
#include <thread>
#include<mutex>
#include<condition_variable>

std::mutex mtx;

std::condition_variable cv;

int flag = 0;

bool ready = false;

void wait();

bool condition() {
    return flag != 0;
}

void consume(int n) {

    for (int i = 0; i < n; i++) {

        std::unique_lock<std::mutex> lck(mtx);
        std::cout << std::this_thread::get_id() << " :obtain lock process one step: " << flag << ::std::endl;
        cv.wait(lck, condition);
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout << std::this_thread::get_id() << " :obtain lock process two step continue : " << flag << ::std::endl;
        flag = 0;
    }
}


void wait() {
    std::thread t1(consume, 1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    for (int i = 0; i < 1; i++) {

        while (condition()) {
            std::this_thread::yield();
        }

        std::unique_lock<std::mutex> lck(mtx);
        flag = i + 1;
        std::cout << std::this_thread::get_id() << " :main obtain: " << flag << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << std::this_thread::get_id() << " : notify  : " << flag << std::endl;
        cv.notify_one();
    }
    t1.join();
}


void doWork() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::unique_lock<std::mutex> lck(mtx);
        ::std::cout << std::this_thread::get_id() << " obtain lock " << flag << ::std::endl;
        ready = true;
    }
    ::std::cout << std::this_thread::get_id() << " obtain notify other " << flag << ::std::endl;
    cv.notify_one();

}

void waitFor() {
    std::thread t1(doWork);
    std::unique_lock<std::mutex> lck(mtx);
    ::std::cout << std::this_thread::get_id() << " obtain lock " << flag << ::std::endl;
    if (cv.wait_for(lck, std::chrono::seconds(2), [] { return ready; })) {
        std::cout << "Work is done" << std::endl;
    } else {
        std::cout << "Work is not done" << std::endl;
    }
    t1.join();

}

int main() {

//    wait();
    waitFor();
    return 0;
}