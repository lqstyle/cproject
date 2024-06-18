/**
 * a、可调用对象
 * 1、 函数指针
 * 2、 具有operator()成员函数的类对象（仿函数）
 * 3、 可以被转换成函数指针的类对象
 * 4、 类成员函数指针/类成员指针
 *
 * 由于定义方式的五花八门，所以C++11通过提供std::function 和 std::bind统一了可调用对象的各种操作
 *
 *
 * b、可调用对象包装器
 * std::function是可调用对象的包装器。它是一个类模板，可以容纳除了类成员（函数）指针之外的所有可调用对象。
 * 通过指定它的模板参数，它可以用统一的方式处理函数、函数对象、函数指针，并允许保存和延迟执行它们
 *   std::function<返回值类型(参数类型列表)> diy_name = 可调用对象;
 *
 *   std::function可以将可调用对象进行包装，得到一个统一的格式，包装完成得到的对象相当于一个函数指针，
 *   和函数指针的使用方式相同，通过包装器对象就可以完成对包装的函数的调用了
 *
 *
 * c、 作为回调函数使用
 * 回调函数本身就是通过函数指针实现的，使用对象包装器可以取代函数指针的作用
 * 对象包装器std::function可以非常方便的将仿函数转换为一个函数指针
 *
 * d、绑定器
 * std::bind用来将可调用对象与其参数一起进行绑定。绑定后的结果可以使用std::function进行保存，
 * 并延迟调用到任何我们需要的时候。通俗来讲，它主要有两大作用：
     将可调用对象与其参数一起绑定成一个仿函数。
     将多元（参数个数为n，n>1）可调用对象转换为一元或者（n-1）元可调用对象，即只绑定部分参数
    // 绑定非类成员函数/变量
     auto f = std::bind(可调用对象地址, 绑定的参数/占位符);
    // 绑定类成员函/变量
    auto f = std::bind(类函数/成员地址, 类实例对象地址, 绑定的参数/占位符);

    std::bind绑定器返回的是一个仿函数类型，得到的返回值可以直接赋值给一个std::function，
    在使用的时候我们并不需要关心绑定器的返回值类型，使用auto进行自动类型推导就可以了。
    placeholders::_1是一个占位符，代表这个位置将在函数调用时被传入的第一个参数所替代。
    同样还有其他的占位符placeholders::_2、placeholders::_3、placeholders::_4、placeholders::_5等……

    可调用对象包装器std::function是不能实现对类成员函数指针或者类成员指针的包装的，但是通过绑定器std::bind的配合之后
 */

#include<iostream>
#include <functional>

//1
int print(int a, int b) {
    std::cout << a << " one " << b << std::endl;
    return a + b;
}

int (*func)(int, int) = &print;


//2
class Test {
public:
    void operator()(const std::string &msg) {
        std::cout << msg << std::endl;
    }
};

//3
using func_ptr = void (*)(int, int);

class Test1 {
public:
    static void print(int a, int b) {
        std::cout << a << " three " << b << std::endl;
    }

    operator func_ptr() {
        return print;
    }
};

//4
class Test2 {
public:
    void print(int a, int b) {
        std::cout << a << " four " << b << std::endl;
    }

    int m;
};


class A {
public:
    explicit A(const std::function<void()> &f) : callback(f) {

    }

    void notify() {
        callback();
    }

private :
    std::function<void()> callback;
};

class B {
public:
    void operator()() {
        std::cout << "call me do something" << std::endl;
    }
};


void callFunc(int x, const std::function<void(int)> &f) {
    if (x % 2 == 0) {
        f(x);
    }
}

void output(int x) {
    std::cout << x << " ";
}

void output_add(int x) {
    std::cout << x + 10 << " ";
}


void output1(int x, int y) {
    std::cout << x << "six " << y << std::endl;
}


class Test3 {
public:
    void output(int x, int y) {
        std::cout << "x: " << x << ", y: " << y << std::endl;
    }

    int m_number = 100;
};

int main() {
    func(1, 2);
    Test t;
    t("lucy");

    Test1 t1;
    t1(1, 2);


    // 定义
    void (Test2::*func2)(int, int) =&Test2::print;
    int Test2::*ptr = &Test2::m;

    Test2 t2;
    (t2.*func2)(1, 2);
    (t2.*ptr) = 20;
    std::cout << t2.m << std::endl;


    // wrapper
    std::function<int(int, int)> f1 = print;
    std::function<void(int, int)> f2 = Test1::print;

    Test tt;
    std::function<void(std::string)> f3 = tt;

    f1(3, 4);
    f2(5, 6);
    f3("test");


    B b;
    A a(b);
    a.notify();


    auto f5 = std::bind(output, std::placeholders::_1);
    for (int i = 0; i < 10; ++i) {
        callFunc(i, f5);
    }

    std::cout << std::endl;

    auto f6 = bind(output_add, std::placeholders::_1);
    for (int i = 0; i < 10; ++i) {
        callFunc(i, f6);
    }
    std::cout << std::endl;


    std::bind(output1, 1, 2);
    std::bind(output1, std::placeholders::_1, 2)(10);
    std::bind(output1, 2, std::placeholders::_1)(10);

//    std::bind(output1,2,std::placeholders::_2)(10);
//    std::bind(output1, 2, std::placeholders::_2)(10, 20);
//    std::bind(output1, std::placeholders::_1, std::placeholders::_2)(10, 20);
//    std::bind(output1, std::placeholders::_2, std::placeholders::_1)(10, 20);



    Test3 t3;
    auto ff = std::bind(&Test3::output, &t3, std::placeholders::_1, std::placeholders::_2);
    auto ff1 = std::bind(&Test3::m_number, &t3);


    ff(10, 10);
    ff1() = 333;
    std::cout << "t.m_number: " << t3.m_number << std::endl;
    return 0;
}

