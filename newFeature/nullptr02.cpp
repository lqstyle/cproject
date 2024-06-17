//https://subingwen.cn/cpp/nullptr/

/**
 * 目的：为了提高程序的健壮性，指针定义都会初始化，如果没有明确指向，会被定义为空指针，避免野指针
 * C++98/03 char *ptr = 0;   char *ptr = NULL;
 *
 * C++中 void * 类型无法隐式转换成其他类型的指针，所以使用0代替 ((void *) 0) 用于解决空指针的问题
 * 0（0x0000 0000） 虚拟地址空间中的0地址，这块地址是只读的。
 *
 *  问题： NULL定义字面量0，并不能保证所有的场景都能正常工作，比如重载时候，NULL和0无法区分
 *  解决：  C++引入了 nullptr
 *  最佳实践：nullptr 无法隐式转换为整形，但是可以隐式匹配指针类型。在
 *  C++11 标准下，相比 NULL 和 0，使用 nullptr 初始化空指针可以令我们编写的程序更加健壮，但是如果需要兼容老版本还是要使用NULL定义
 *  
 * #ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

 */
#include<iostream>

void test(int a) {
    std::cout << "int call" << std::endl;
}

void test(char *a) {
    std::cout << "char call" << std::endl;
}

int main() {

    int a = 10;
//    ::std::cout << &a << ::std::endl;
//    ::std::cout << a << ::std::endl;
    char *e = NULL;
    test(a);
//    test(NULL);
//    test((int)NULL);
//    test((char *)NULL);
//    test(e);
//    char *c = nullptr;
//    test(c);
//    test(nullptr);
//    test(((void *)0));
    return 0;
}