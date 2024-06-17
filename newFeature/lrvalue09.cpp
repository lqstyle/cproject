
/**
 * lvalue 是loactor value的缩写，rvalue 是 read value的缩写  test01
左值是指存储在内存中、有明确存储地址（可取地址）的数据；
右值是指可以提供数据值的数据（不可取地址）；
 验证方法 ：可以对表达式取地址（&）就是左值，否则为右值
 一般情况下，位于=前的表达式为左值，位于=后边的表达式为右值

 右值又分为将忘值和纯右值
 一个是将亡值（ xvalue, expiring value），另一个则是纯右值（ prvalue, PureRvalue）
 纯右值： 非引用返回的临时变量，运算表达式产生的临时变量，原始字面量，lambda表达式等
 将亡值： 与右值引用相关的表达式 例如 T&&类型函数的返回值 std::move的返回值


 右值引用：对一个右值进行引用  因为右值是匿名的，我们只能通过右值引用获取到  test02
 左值引用： 对一个左值进行引用

 无论声明左值引用还是右值引用都必须立即进行初始化，因为引用类型本身并不拥有所绑定对象的内存，只是该对象的一个别名。
 通过右值引用的声明，该右值又“重获新生”

 常量左值引用是一个万能引用类型，它可以接受左值、右值、常量左值和常量右值
 右值引用具有移动语义，移动语义可以将资源（堆、系统对象等）通过浅拷贝从一个对象转移到另一个对象这样就能减少不必要的临时对象的创建、拷贝以及销毁，可以大幅提高C++应用程序的性能。
  这通常被称为 “return-value optimization” 或 " RVO"

&& 特性 test04
 T&&或者auto&&这种未定引用类型，当它作为参数时，有可能被一个右值引用初始化，也有可能被一个左值引用初始化，在进行类型推导时右值引用类型（&&）会发生变化，这种变化被称为引用折叠
通过右值推导 T&& 或者 auto&& 得到的是一个右值引用类型
通过非右值（右值引用、左值、左值引用、常量右值引用、常量左值引用）推导 T&& 或者 auto&& 得到的是一个左值引用类型


 test05
左值和右值是独立于他们的类型的，右值引用类型可能是左值也可能是右值。
编译器会将已命名的右值引用视为左值，将未命名的右值引用视为右值。
auto&&或者函数参数类型自动推导的T&&是一个未定的引用类型，它可能是左值引用也可能是右值引用类型，这取决于初始化的值类型（上面有例子）。
通过右值推导 T&& 或者 auto&& 得到的是一个右值引用类型，其余都是左值引用类型


 **/

#include<iostream>


int &&value = 520;

class Test {
public:
    Test() {
        std::cout << "construct: my name is jerry" << std::endl;
    }

    Test(const Test &a) {
        std::cout << "copy construct: my name is tom" << std::endl;
    }
};

Test getObj() {
    return Test();
}

class Test1 {
public:
    Test1() : m_num(new int(100)) {
        std::cout << "construct1: my name is jerry1" << std::endl;
    }

    Test1(const Test1 &a) noexcept: m_num(new int(*a.m_num)) {
        std::cout << "copy construct1: my name is tom1" << std::endl;
    }

    Test1(Test1 &&a) : m_num(a.m_num) {
        a.m_num = nullptr;
        std::cout << "move construct: my name is sunny1" << std::endl;
    }


    ~Test1() {
        delete m_num;
    }

    int *m_num;
};

Test1 getObj1() {
    Test1 t;
    return t;
}


void


test1();

void test2();

void test3();

void test4();

void test05();

int main() {
    test1();
    test2();
    test3();

//    test05();
    return 0;
}

void test1() {
    int a = 520;
    int b = 1314;
    a = b;
    int i = 42;
    int &c = ++i;
//    int &d = i++;
}

void test2() {
    int a1;
//    int &&a2 = a1;
//    Test& t = getObj();
//    Test && t = getObj();
//    const Test &t = getObj();
}

void test3() {
    Test1 t1 = getObj1();
    std::cout << "t.m_num: " << *t1.m_num << std::endl;
}

template<typename T>
void f(T &&param);

template<typename T>
void f1(const T &&param);

void test4() {
//    f(10);
//    int x = 10;
//    f(x);
//    f1(x);
//    f1(10);
//    int x = 520, y = 1314;
//    auto &&v1 = x;
//    auto &&v2 = 250;
//    decltype(x) &&v3 = y;
//    std::cout << "v1: " << v1 << ", v2: " << v2 << std::endl;
}

void printValue(int &i) {
    std::cout << "l-value: " << i << std::endl;
}

void printValue(int &&i) {
    std::cout << "r-value: " << i << std::endl;
}

void forward(int &&k) {
    printValue(k);
}

void test05() {
    int i = 520;
    printValue(i);
    printValue(1314);
    forward(250);
}
