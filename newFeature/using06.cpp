/**
 *  以前的定义是命名空间，现在是定义别名 比如访问父类的同名方法
 *  类型别名和类型的名字等价，只要是类型的名字能出现的地方，就能使用类型别名。使用typedef定义的别名和使用using定义的别名在语义上是等效的。
 *   test1
 *  using 新的类型 = 旧的类型;   eg： using uint_t = int;
 *  typedef 旧的类型名 新的类型名; eg: typedef unsigned int uint_t;
 *
 *  模板别名
 *   test2 test3
 *
 *   using语法和typedef一样，并不会创建出新的类型，它们只是给某些类型定义了新的别名。
 *   using相较于typedef的优势在于定义函数指针别名时看起来更加直观，并且可以给模板定义别名
 */


#include <iostream>
#include <map>


void test1();

void test2();

void test3();

int main() {
//    test1();
//    test2();
    test3();
    return 0;
}

int add(int a, double b) {
    return a + b;
}


// 这是一个接受函数指针作为参数的函数
int applyFunction(int (*func)(int, double), int num, double a) {
    return func(num, a);
}

// 使用typedef定义函数指针
typedef int(*func_ptr)(int, double);

// 使用using定义函数指针
using func_ptr1 = int (*)(int, double);

void test1() {
    func_ptr fuc = &add;
    int result = applyFunction(fuc, 1, 10.0);
    std::cout << result << std::endl;

    func_ptr1 func1 = &add;
    int result2 = applyFunction(func1, 1, 11.0);
    std::cout << result2 << std::endl;

    int (*func_ptr1)(int, double);
    func_ptr1 = &add;
    int result3 = applyFunction(func_ptr1, 1, 12.0);
    std::cout << result3 << std::endl;
}


typedef std::map<int, std::string> m1;
typedef std::map<int, int> m2;
typedef std::map<int, double> m3;

//template <typename T>
//typedef std::map<int,T> type1;

template<typename U>
// 定义外敷类
struct MyMap {
    typedef std::map<int, U> type;
};

void test2() {

    MyMap<std::string>::type m;
    m.insert(std::make_pair(1, "lucy"));
    m.insert(std::make_pair(2, "ace"));

    MyMap<int>::type m1;
    m1.insert(std::make_pair(1, 1));
    m1.insert(std::make_pair(2, 1));
}

template<typename T>
using mymap = std::map<int, T>;

void test3() {

    mymap<std::string> m;
    m.insert(std::make_pair(1, "lucy"));
    m.insert(std::make_pair(2, "ace"));

    mymap<int> m1;
    m1.insert(std::make_pair(1, 1));
    m1.insert(std::make_pair(2, 1));
}