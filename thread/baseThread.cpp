#include <chrono>
#include <iostream>
#include <thread>
#include <utility>
#include <pthread.h>
#include <windows.h>

int size = 1;

void f1(int n) {
    for (int i = 0; i < size; ++i) {
        printf("Thread 1 executing %d\n",std::this_thread::get_id());
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int &n) {
    for (int i = 0; i < size; ++i) {
        printf("Thread 2 executing %d\n",std::this_thread::get_id());
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo {
public:
    void bar() {
        for (int i = 0; i < size; ++i) {
            printf("Thread 3 executing %d\n",std::this_thread::get_id());
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    int n = 0;
};

class baz {
public:
    void operator()() {
        for (int i = 0; i < size; ++i) {
            printf("Thread 4 executing %d\n",std::this_thread::get_id());
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    int n = 0;
};

void threadBase();

void pthreadBase();

void win32Base();

void *threadFunction(void *arg) {

    int *number = (int *) arg;
//    _sleep(*number);
    std::cout << "Hello from pthread!" << *number << std::endl;
    return nullptr;
}


int main() {
//    threadBase();

//    pthreadBase();
    win32Base();
    return 0;

}

DWORD WINAPI threadFunctionWin(LPVOID lpParam) {
    std::cout << "Hello from Windows thread!" << std::endl;
    return 0;
}

void win32Base() {
    HANDLE hThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(threadFunctionWin), nullptr, 0,
                                  nullptr);
    if (hThread == nullptr) {
        return;
    }
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
}


void pthreadBase() {

    int number = 1000;
    pthread_t thread;
    if (pthread_create(&thread, nullptr, threadFunction, &number) != 0) {
        return;
    }
//    pthread_join(thread, nullptr);
    pthread_detach(thread);
}

void threadBase() {
    int n = 0;
    foo f;
    baz b;
    std::thread t1;                                                                                     // t1 is not a thread,你只是创建了一个线程对象，而不是一个正在运行的线程。要启动线程，你需要为std::thread构造函数提供一个函数（或者函数对象、 lambda 表达式等），这个函数将会在新线程中执行
    std::thread t2(f1, n + 1);                                                                        // pass by value
    std::thread t3(f2, std::ref(n));                                                                  // pass by reference
    std::thread t4(std::move(t3));                                                                       // t4 is now running f2(). t3 is no longer a thread
    std::thread t5(&foo::bar, &f);                                                                     // t5 runs foo::bar() on object f
//    std::thread t6(b);
    std::thread t6(std::ref(b));
    t2.join();
//    t3.join();
    t4.join();
    t5.join();
    t6.join();
    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
    std::cout << "Final value of b.n (baz::n) is " << b.n << '\n';
}
