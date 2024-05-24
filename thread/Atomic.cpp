#include <iostream>
#include <thread>
#include<atomic>

int a = 0;
std::atomic_int b(0);

void add() {
    for (int i = 0; i < 100000; i++) {
        a++;
    }
}

void addAtomic() {
    for (int i = 0; i < 100000; i++) {
//        a++;
        b.fetch_add(1);
    }

}

int main() {

    std::thread t1(addAtomic);
    std::thread t2(addAtomic);
    t1.join();
    t2.join();
    ::std::cout << b << ::std::endl;
    ::std::cout << "support useless lock: " << b.is_lock_free() << ::std::endl;
    return 0;
}