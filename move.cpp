#include<iostream>
#include<string>
#include <iomanip>

class A {

public:
    A() {
        ::std::cout << "构造" << ::std::endl;
    };


    A(std::string b) : name(b) {
        ::std::cout << "构造1" << ::std::endl;
    };

    A(A const &a) {
        ::std::cout << "构造2" << ::std::endl;
    }

    ~A() {
        ::std::cout << "析构" << ::std::endl;
    };


    A(A &&arg) : name(std::move(arg.name)) {
        ::std::cout << "move" << ::std::endl;
    }

    A &operator=(A &other) {
        ::std::cout << "operator" << ::std::endl;
        name = std::move(other.name);
    }

public:
    std::string name;
};

int main() {
    A a("lq");
    ::std::cout << std::quoted(a.name) << ::std::endl;


    A b = std::move(a);
    ::std::cout << std::quoted(a.name) << ::std::endl;
    ::std::cout << std::quoted(b.name) << ::std::endl;
    A c(std::move(a));
    ::std::cout << std::quoted(c.name) << ::std::endl;
    A d=a;
    return 0;
}