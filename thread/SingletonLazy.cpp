#include<iostream>
#include<thread>


class Singleton {

public:
    static Singleton &getInstance() {
        static Singleton singleton;
        return singleton;
    }

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

    void show() {
        printf("Address of this object: %p\n", (void*)this);
    }

private:
    Singleton() = default;

};

void showSingleton() {
    Singleton::getInstance().show();
}

int main() {
    Singleton &singleton = Singleton::getInstance();
    singleton.show();
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