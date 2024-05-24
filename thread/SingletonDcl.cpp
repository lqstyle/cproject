#include<mutex>
#include<thread>
#include<iostream>

class Singleton {
public:
    static Singleton *getInstance() {
        if (instance == nullptr) {
            std::unique_lock<std::mutex> lck(mtx);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

    void show() {
        printf("Address of this object: %p\n", (void*)this);
    }


private :
    Singleton() = default;

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

private:
    static Singleton *instance;
    static std::mutex mtx;
};

void showSingleton() {
    Singleton::getInstance()->show();
}

Singleton *Singleton::instance = nullptr;
std::mutex Singleton::mtx;


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