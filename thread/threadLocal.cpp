#include<iostream>
#include<thread>

thread_local int x = 10;
//int x = 10;
//static int x = 10;


int main() {
    auto f = [&](int a) {
        x += a;
        printf("value is %d \n", x);
    };

    std::thread t1(f, 10);
    std::thread t2(f, 20);
    t1.join();
    t2.join();
    return 0;
}