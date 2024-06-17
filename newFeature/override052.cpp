#include<iostream>

/**
 *  这个关键字要写到方法的后面
 **/



class Base {
public:
    virtual void test() {
        std::cout << "Base class...";
    }
};

class Child : public Base {
public:
    void test() override {
        std::cout << "Child class...";
    }
};

class GrandChild : public Child {
public:
    void test() override {
        std::cout << "Child class...";
    }
};

