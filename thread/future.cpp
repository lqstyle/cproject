#include<iostream>
#include<future>
#include<thread>

void future();

void promise();

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibonacci1(int n) {
    if (n <= 1) {
        return n;
    }
    // 由于多线程环境下的递归调用可能会导致栈溢出，我们在这里使用一个简单的循环来计算斐波那契数列
    int a = 0, b = 1, temp;
    for (int i = 0; i < n - 1; ++i) {
        temp = a;
        a = b;
        b = temp + b;
    }
    return b;
}

void calculateSum(std::promise<int> &prom, int a, int b) {
    int sum = a + b;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    prom.set_value(sum);  // 设置promise的值
}

int main() {

//    future();

    promise();

    return 0;
}

void promise() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();  // 获取与promise关联的future

    std::thread t(calculateSum, std::ref(prom), 10, 20);  // 启动一个线程来计算和

    t.join();  // 等待线程完成

    int sum = fut.get();  // 获取promise设置的值
    std::cout << "Sum: " << sum << std::endl;
}

void future() {
    std::future<int> future = std::async(fibonacci, 30);
    std::cout << "waiting for res" << std::endl;

    int result = future.get();

    std::cout << "result is " << result << std::endl;
}
