#include<iostream>
#include<thread>
#include<mutex>

class Singleton {

public:
    static Singleton *getInstance() {
        std::call_once(flag, []() {
            singleton = new Singleton();
        });
        return singleton;
    }

    Singleton(const Singleton &singleton) = delete;

    Singleton &operator=(const Singleton &singleton) = delete;

    void show() {
        printf("Address of this object: %p\n", (void *) this);
    }


private:
    Singleton() = default;

    static Singleton *singleton;
    static std::once_flag flag;
};

void showSingleton() {
    Singleton::getInstance()->show();
}

Singleton *Singleton::singleton = nullptr;
std::once_flag  Singleton::flag;

int main() {
    std::thread th1(showSingleton);
    std::thread th2(showSingleton);
    std::thread th3(showSingleton);
    std::thread th4(showSingleton);
    std::thread th5(showSingleton);
    std::thread th6(showSingleton);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    return 0;
}