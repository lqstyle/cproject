#include<iostream>

/**
 *  限制某个类不能被继承，或者某个虚函数不能被重写,要把final关键字放到类或者函数的后面
 */
class Base {
public:
    virtual void test() {
        std::cout << "Base class...";
    }
};

class Child : public Base {
public:
    void test() final {
        std::cout << "Child class...";
    }
};

class GrandChild : public Child {
public:
//    void test() final{
//        std::cout << "GrandChild class...";
//    }
};


class BaseNew {
public:
    virtual void test() {
        std::cout << "Base class...";
    }
};

class ChildNew final : public BaseNew {
public:
    void test() final {
        std::cout << "Child class...";
    }
};
//class GrandChildNew : public ChildNew
//{
//public:
//    // 语法错误, 不允许重写
//    void test()
//    {
//        std::cout << "GrandChild class...";
//    }
//};






int main() {


    return 0;
}