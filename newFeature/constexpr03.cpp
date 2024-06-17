//
// Created by 86182 on 2024/6/15.
// https://subingwen.cn/cpp/constexpr/
//
/**
 *  const关键字 : 修饰变量只读   定义常量
 *  constexpr 修饰常量表达式  由多个（≥1）常量（值不会改变）组成并且在编译过程中就得到计算结果的表达式
 *
 *  预处理、 编译、汇编和链接
 *  常量表达式和非常量表达式的计算时机不同，非常量表达式只能在程序运行阶段计算出结果，但是常量表达式的计算往往发生在程序的编译阶段，这可以极大提高程序的执行效率，
 *  因为表达式只需要在编译阶段计算一次，节省了每次程序运行时都需要计算一次的时间
 *
 *  应用场景：凡是表达“只读”语义的场景都使用 const，表达“常量”语义的场景都使用 constexpr  两者在定义常量的时候是等价的
 *
 * * 常量表达式函数  普通函数/类成员函数  类的构造函数 模板函数   主要是修饰函数的返回值
 *
 * constexpr 并不能修改任意函数的返回值
 * 1 、 函数必须有返回值，且返回值必须是常量表达式 test2
 * 2、 函数使用之前必须有定义
 * 3、 常量表达式函数的函数体中，不能出现除了 using typedef static_assert return以外的语句
 *
 * 不同的C++ 编译器版本要求不同，此处说明的是11版本
 * 例如 14版本 可以使用局部变量，但是不能使用全局变量和静态变量，但是C++ 23又支持，所以根据实际的版本来决定
 * C++ 14 对上述描述的3进行了放宽，可以使用 if switch for while  但不能使用goto  返回值可以使用void 也可以使用多个return
 *
 * 常量构造函数 构造函数的函数体必须为空，并且必须采用初始化列表的方式为各个成员赋值
 *
 * 优点：
 * 编译期计算，提高运行效率，目前大部分标准库都已经支持constexpr
 * 编译器静态验证，发现潜在错误
 *
 *
 * const 和constexpr 创建常量对象的区别
 * 编译期优化存储 和constexpr
 * 存储可能是动态分配 const

 *
 *
 */
#include<iostream>

void func(const int num);

void constexprs();

void constexprstruct();

constexpr int test2();

void testTemplate();

int main() {

//    func(10);
//    constexprs();
//    test2();
//    constexprstruct();
//    testTemplate();
    return 0;

}


int f() {
    return 10;
}


void constexprs() {
    const int m = f();
    const int i = 520;
    const int j = i + 1;

    constexpr int i1 = 520;
    constexpr int j1 = i + 1;

}


void func(const int num) {
    const int count = 24;
    int array[num];
    int array1[count];

    int a1 = 520;
    int a2 = 250;
    const int &b = a1;
//    b = a2;
    a1 = 1314;
    std::cout << "b: " << b << std::endl;     // 输出结果为1314
}


struct Test {
    int id;
    int num;
};


void constexprstruct() {
    constexpr Test t{10, 20};
    constexpr int t1 = t.id;
    constexpr int t2 = t.num;
    std::cout << t1 << std::endl;

}

//constexpr
void test1() {

}

constexpr int test2() {

    int a = 10;
//    for (int i = 0; i < a ++i)
//    {
//        std::cout << "i: " << i << std::endl;
//    }
    return a;
}


/**
 * 修饰构造函数的话，构造函数的函数体必须为空，并且必须使用初始化成员列表的方式来为各个成员赋值
 */
struct Person {

    constexpr Person(const char *p, int age) : name(p), age(age) {
    }

    const char *name;
    int age;

};

template<typename T>
constexpr T display(T t) {
//    for (int i = 0; i < 10; ++i) {
//
//    }
    return t;
}

void testTemplate() {
    struct Person p{"lucy", 19};
//普通函数  constexpr是否有效？
    struct Person ret = display(p);
    std::cout << "lucy's name: " << ret.name << ", age: " << ret.age << std::endl;

//常量表达式函数 constexpr是否有效？
    constexpr int ret1 = display(250);
    std::cout << ret1 << std::endl;

    constexpr struct Person p1{"lucy", 20};
    //constexpr是否有效？
    constexpr struct Person p2 = display(p1);
    std::cout << "lucy's name: " << p2.name << ", age: " << p2.age << std::endl;

}

