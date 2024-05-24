#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<queue>

class ThreadPool {

private:
    //定义线程数组
    std::vector<std::thread> threads;
    //定义存放任务的队列
    std::queue<std::function<void()>> tasks;
    //定义互斥锁
    std::mutex mtx;
    //定义条件变量
    std::condition_variable cv;
    //定义是否终止
    bool stop;


public:
    ThreadPool(int n) : stop(false) {
        for (int i = 0; i < n; i++) {
            auto t = [this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);

                        cv.wait(lock, [this] {
                            return !tasks.empty() || stop;
                        });

                        if (stop && tasks.empty()) {
                            return;
                        }
                        task = (std::move(tasks.front()));
                        tasks.pop();
                    }

                    task();
                }
            };
//            auto t = [this] {
//                while (true) {
//                    std::unique_lock<std::mutex> lock(mtx);
//
//                    cv.wait(lock, [this] {
//                        return !tasks.empty() || stop;
//                    });
//
//                    if (stop && tasks.empty()) {
//                        return;
//                    }
//                    std::function<void()> task = (std::move(tasks.front()));
//                    tasks.pop();
//                    lock.unlock();
//                    task();
//                }
//            };
            threads.emplace_back(t);
            printf("thread %d create success\n", i);

        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto &item: threads) {
            item.join();
        }
    }

    template<class Fun, class ...Args>
    void enqueue(Fun &&fun, Args &&...args) {
        auto task = std::bind(std::forward<Fun>(fun), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        cv.notify_one();
    }

};

void myfunction(int i, int x, std::string y) {
    printf("task  %d is running thread is %d\n", i, std::this_thread::get_id());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("task %d is done thread is %d\n", i, std::this_thread::get_id());
}

int main() {

    ThreadPool threadPool(5);
    //lamada 表达式
    for (int i = 0; i < 5; i++) {
        threadPool.enqueue([i]() {
            printf("task  %d is running thread is %d\n", i, std::this_thread::get_id());
            std::this_thread::sleep_for(std::chrono::seconds(1));
            printf("task %d is done thread is %d\n", i, std::this_thread::get_id());
        });
    }

    // 函数
//    for (int i = 0; i < 5; i++) {
//        threadPool.enqueue(myfunction, i, 10, "hello");
//    }

    return 0;
}