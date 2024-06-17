#include <iostream>
#include <vector>

/**
 * 1、test1 右尖括号的优化  C++98/03 >>会被认为是左移运算符
 * 2、test2  test3 类模板可以有默认的模板参数，函数模板不行，C++11 新增了函数模板对默认参数的支持
 * 当所有模板参数都有默认参数时，函数模板的调用如同一个普通函数。但对于类模板而言，哪怕所有参数都有默认参数，在使用时也必须在模板名后跟随<>来实例化
 *
 * test4  函数模板的默认模板参数在使用规则上和其他的默认参数也有一些不同，它没有必须写在参数表最后的限制
 *        我们可以指定函数模板中的一部分模板参数使用默认参数，另一部分使用自动推导
 * test5 如果可以推导出参数类型则使用推导出的类型
 * 如果函数模板无法推导出参数类型，那么编译器会使用默认模板参数
 * 如果无法推导出模板参数类型并且没有设置默认模板参数，编译器就会报错。
 * @tparam T
 */
template<typename T>
class Base {
public:
    void traversal(T &t) {
        auto it = t.begin();
        for (; it != t.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};


template<typename T=int, T t = 520>
class Test {
public:
    void print() {
        std::cout << "current value: " << t << std::endl;
    }
};

template<typename T=int>
void func(T t) {
    std::cout << "current value: " << t << std::endl;
}


void test1();

void test2();

void test3();

void test4();

void test5();

void test6();

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    return 0;
}

void test1() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    Base<std::vector<int>> b;
    b.traversal(v);
}

void test2() {
    Test<> t;
    t.print();
    Test<int, 100> t1;
    t1.print();
    Test<long, 200> t2;
    t2.print();
}


void test3() {
    func<int>(100);
    func(100);
    func<double>(300);
}


template<typename R = int, typename N>
R func1(N arg) {
    return arg;
}

void test4() {
    auto ret1 = func1(520);
    std::cout << "return value-1: " << ret1 << std::endl;

    auto ret2 = func1<double>(52.134);
    std::cout << "return value-2: " << ret2 << std::endl;

    auto ret3 = func1<int>(52.134);
    std::cout << "return value-3: " << ret3 << std::endl;

    auto ret4 = func1<char, int>(100);
    std::cout << "return value-4: " << ret4 << std::endl;

}

// 函数模板定义
template<typename T, typename U = char>
void func2(T arg1 = 100, U arg2 = 100) {
    std::cout << "arg1: " << arg1 << ", arg2: " << arg2 << std::endl;
}


void test5() {
    func2('a');
    func2(97, 'a');
//     func();    //编译报错
}



template<typename T=int, typename U>
void func3(T arg1 = 100, U arg2 = 80) {
    std::cout << "arg1: " << arg1 << ", arg2: " << arg2 << std::endl;
}

void test6() {
//    func3('a');
    func3('a','b');
    func3(97, 'a');
//     func();    //编译报错
}

