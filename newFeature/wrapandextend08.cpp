/**
 * 这种链式的构造函数调用不能形成一个闭环（死循环），否则会在运行期抛异常。
   如果要进行多层构造函数的链式调用，建议将构造函数的调用的写在初始列表中而不是函数体内部，否则编译器会提示形参的重复定义。
    在初始化列表中调用了代理构造函数初始化某个类成员变量之后，就不能在初始化列表中再次初始化这个变量了
 */
#include <iostream>

class Test {
public:
    Test() {};

    Test(int max) {
        this->m_max = max > 0 ? max : 100;
    }

    Test(int max, int min) {
        this->m_max = max > 0 ? max : 100;              // 冗余代码
        this->m_min = min > 0 && min < max ? min : 1;
    }

    Test(int max, int min, int mid) {
        this->m_max = max > 0 ? max : 100;             // 冗余代码
        this->m_min = min > 0 && min < max ? min : 1;  // 冗余代码
        this->m_middle = mid < max && mid > min ? mid : 50;
    }

    int m_min;
    int m_max;
    int m_middle;
};


class Test1 {
public:
    Test1() {};

    Test1(int max) {
        this->m_max = max > 0 ? max : 100;
    }

    Test1(int max, int min) : Test1(max) {
        this->m_min = min > 0 && min < max ? min : 1;
    }

//    Test1(int max, int min)  {
//        Test1(max);
//        this->m_min = min > 0 && min < max ? min : 1;
//    }
//    Test1(int max, int min) : Test1(max), m_max(max) {
//        this->m_min = min > 0 && min < max ? min : 1;
//    }

    Test1(int max, int min, int mid) : Test1(max, min) {
        this->m_middle = mid < max && mid > min ? mid : 50;
    }

    int m_min;
    int m_max;
    int m_middle;
};

void test1();

void test2();

void test3();

void test4();

int main() {
    test1();
    test2();
    test3();
    test4();

    return 0;
}

void test1() {
    Test t(90, 30, 60);
    std::cout << "min: " << t.m_min << ", middle: "
              << t.m_middle << ", max: " << t.m_max << std::endl;

    Test1 t1(90, 30, 60);
    std::cout << "min: " << t1.m_min << ", middle: "
              << t1.m_middle << ", max: " << t1.m_max << std::endl;
}


class Base {
public:
    Base(int i) : m_i(i) {}

    Base(int i, double j) : m_i(i), m_j(j) {}

    Base(int i, double j, std::string k) : m_i(i), m_j(j), m_k(k) {}

    void func(int i) {
        std::cout << "base class: i = " << i << std::endl;
    }

    int m_i;
    double m_j;
    std::string m_k;
};

class Child : public Base {
public:
    Child(int i) : Base(i) {}

    Child(int i, double j) : Base(i, j) {}

    Child(int i, double j, std::string k) : Base(i, j, k) {}

    using Base::func;

    void func() {
        std::cout << "child class: i'am lucy!!!" << std::endl;
    }

};


class Base1 {
public:
    Base1(int i) : m_i(i) {}

    Base1(int i, double j) : m_i(i), m_j(j) {}

    Base1(int i, double j, std::string k) : m_i(i), m_j(j), m_k(k) {}

    void func(int i) {
        std::cout << "base class: i = " << i << std::endl;
    }

    int m_i;
    double m_j;
    std::string m_k;
};

class Child1 : public Base1 {
public:
    using Base1::Base1;
    using Base1::func;

    void func() {
        std::cout << "child class: i'am lucy!!!" << std::endl;
    }
};

void test2() {
    Child c1(520, 13.14);
    std::cout << "int: " << c1.m_i << ", double: " << c1.m_j << std::endl;
    Child c2(520, 13.14, "i love you");
    std::cout << "int: " << c2.m_i << ", double: "
              << c2.m_j << ", string: " << c2.m_k << std::endl;
}


void test3() {
    Child1 c1(520, 13.14);
    std::cout << "int: " << c1.m_i << ", double: " << c1.m_j << std::endl;
    Child1 c2(520, 13.14, "i love you");
    std::cout << "int: " << c2.m_i << ", double: "
              << c2.m_j << ", string: " << c2.m_k << std::endl;
}

void test4() {
    Child1 c(250);
    c.func();
    c.func(19);
};


