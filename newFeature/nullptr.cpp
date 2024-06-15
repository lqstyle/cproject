//https://subingwen.cn/cpp/nullptr/

/**
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

    char *e = NULL;
    test(1);
    test((int)NULL);
    test(e);
    test(nullptr);
    return 0;
}