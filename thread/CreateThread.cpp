#include <iostream>
#include <thread>
#include<future>


void run() {

    // 形式1
    ::std::cout << "my first c++ multi thread" << ::std::endl;
    throw std::exception();
}

void runWithParam(const std::string msg) {


//    std::this_thread::sleep_for(std::chrono::seconds(100));
    // 形式1
    ::std::cout << msg << ::std::endl;
}


int main() {

    // 形式1 无参的函数调用
    ::std::thread myThread(run);

    // 形式2  有参函数的调用
    ::std::thread myParamThread(runWithParam, "hello");


    myThread.detach();
    if(myThread.joinable()){
        ::std::cout << "success" << ::std::endl;
    };
//    myThread.join();
    myParamThread.join();

    ::std::cout << "end" << ::std::endl;
//    myParamThread.detach();
    return 0;
}