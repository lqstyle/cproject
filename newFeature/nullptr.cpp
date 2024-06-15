#include<iostream>

void test(int a) {
    std::cout << "int call" << std::endl;
}

void test(char *a) {
    std::cout << "char call" << std::endl;
}

int main() {

    int *a = NULL;
    float *b = NULL;
    double *c = NULL;
//    char *d = NULL;
    char *d = nullptr;
//    void *e = NULL;
    void *e = nullptr;
    int *f =(int *)e;
    test(1);
    test(nullptr);
    return 0;
}