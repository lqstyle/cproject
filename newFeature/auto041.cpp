#include<iostream>

/**
 * 使用auto声明的变量必须要进行初始化，以让编译器推导出它的实际类型，在编译时将auto占位符替换为真正的类型
 *
 * 当变量不是指针或者引用类型时，推导的结果中不会保留const、volatile关键字 autoTest3
 * 当变量是指针或者引用类型时，推导的结果中会保留const、volatile关键字   autoTest3
 *
 * 限制 ：1 不能作为函数参数使用
 *       2 不能用于类的非静态成员变量的初始化 静态非常量的初始化
 *       3 不能使用auto关键字定义数组
 *       4 无法使用auto推导出模板参数
 *
 *  场景 容器遍历 1
 *       泛型编程 2
 * @return
 */

void autoTest();

void autoTest2();

void autoTest3();

void test4();

void test5();

int main() {

//    autoTest();
//    autoTest2();
//    autoTest3();
    test4();
//    test5();
    return 0;
}

void autoTest() {
    auto x = 3.14;
    auto y = 520;
    auto z = 'a';
//    auto nb;
//    auto double nbl;
}

void autoTest2() {
    int temp = 110;
    auto *a = &temp;
    auto b = &temp;
    auto &c = temp;
    auto d = temp;
}

void autoTest3() {
    int tmp = 250;
    const auto a1 = tmp;
    auto a2 = a1;
    const auto &a3 = tmp;
    auto &a4 = a3;
}

// 1
//int func(auto a, auto b)
//{
//    std::cout << "a: " << a <<", b: " << b << std::endl;
//}

// 2
class Test {
//    auto v1 = 0;
//    static auto v2 = 0;
    static const auto v3 = 10;
};

//3
int func() {
    int array[] = {1, 2, 3, 4, 5};
    auto t1 = array;
//    auto t2[] = array;
//    auto t3[] = {1,2,3,4,5};;
}


//4
template<typename T>
struct Test1 {

};

int func2() {
    Test1<double> t;
//    Test1<auto> t1 = t;
    return 0;
}


//泛型编程
class T1 {
public:
    static int get() {
        return 10;
    }
};

class T2 {
public:
    static std::string get() {
        return "hello, world";
    }
};

template<class A>
void func() {
    auto val = A::get();
    std::cout << "val: " << val << std::endl;
}

template<class A, typename B>
void func1() {
    B val = A::get();
    std::cout << "val: " << val << std::endl;
}


void test4() {
    func<T1>();
    func<T2>();
}


void test5() {
    func1<T1, int>();
    func1<T2, std::string>();
}









