/**
 * 不需要或者不能定义变量，但是希望得到某种类型
 *
 * decltype推导的表达式可简单可复杂，在这一点上auto是做不到的，auto只能推导已初始化的变量类型
 *
 *推导规则
 *
 *  1、表达式为普通变量或者普通表达式或者类表达式，在这种情况下，使用decltype推导出的类型和表达式的类型是一致的。
 *  2、 表达式是函数调用，使用decltype推导出的类型和函数返回值一致
 *       对于纯右值而言，只有类类型可以携带const、volatile限定符，除此之外需要忽略掉这两个限定符
 *  3、表达式是一个左值，或者被括号( )包围，使用 decltype推导出的是表达式类型的引用（如果有const、volatile限定符不能忽略）
 *
 *  应用
 *   泛型编程
 *   返回类型后置
 */

#include<iostream>
#include <list>

class Test {
public:
    std::string text;
    static const int value = 110;
    int number = 110;
};


//函数声明
int func_int();                 // 返回值为 int
int &func_int_r();              // 返回值为 int&
int &&func_int_rr();            // 返回值为 int&&

const int func_cint();          // 返回值为 const int
const int &func_cint_r();       // 返回值为 const int&
const int &&func_cint_rr();     // 返回值为 const int&&

const Test func_ctest();        // 返回值为 const Test

void test1();

void test2();

void test3();

void test5();

void test6();

void test7();

int main() {
    test1();
    test2();
    test3();
    test5();
//    test6();
//    test7();
}

void test1() {
    int a = 10;
    decltype(a) b = 99;
    decltype(a + 3.14) c = 52.13;
    decltype(a + b * c) d = 520.1314;
}

void test2() {
    int x = 99;
    const int &y = x;
    decltype(x) a = x;
    decltype(y) b = x;
    decltype(Test::value) c = 0;

    Test t;
    decltype(t.text) d = "hello, world";

}

void test3() {
    int n = 100;
    decltype(func_int()) a = 0;
    decltype(func_int_r()) b = n;
    decltype(func_int_rr()) c = 0;
    decltype(func_cint()) d = 0;
    decltype(func_cint_r()) e = n;
    decltype(func_cint_rr()) f = 0;
    decltype(func_ctest()) g = Test();
}


void test4() {
    const Test obj;
    //带有括号的表达式
    decltype(obj.number) a = 0;
    decltype((obj.number)) b = a;
    //加法表达式
    int n = 0, m = 0;
    decltype(n + m) c = 0;
    decltype(n = n + m) d = n;

}


template<class T>
class Container {
public:
    void func(T &c) {
        for (m_it = c.begin(); m_it != c.end(); ++m_it) {
            std::cout << *m_it << " ";
        }
        std::cout << std::endl;
    }

private:
    decltype(T().begin()) m_it;
};

void test5() {
    const std::list<int> lst{1, 2, 3, 4, 5, 6, 7, 8, 9};
    Container<const std::list<int>> obj;
    obj.func(lst);
}


template<typename R, typename T, typename U>
R add(T t, U u) {
    return t + u;
}

void test6() {

    int x = 520;
    double y = 13.14;
    // auto z = add<decltype(x + y), int, double>(x, y);
    auto z = add<decltype(x + y)>(x, y);    // 简化之后的写法
    std::cout << "z: " << z << std::endl;

}

//template <typename T, typename U>
//decltype(t+u) add(T t, U u) {
//    return t + u;
//};
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}

void test7() {
    int x = 520;
    double y = 13.14;
    // auto z = add<int, double>(x, y);
    auto z = add(x, y);        // 简化之后的写法
    std::cout << "z: " << z << std::endl;

}