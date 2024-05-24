

#include <string>

using String = ::std::string;

int main() {


    String s = "123";
    String s1 = s + "234";


    String s2 = "123";

    //左值引用
    String &s3 = s2;

    //右值引用
    String &&s4 = "132";
    const String &s5 = "111";

    String &s6 = s4;


    int i = 10;
    int &j=i;
    int &&j = ::std::move(i);
    return 0;
}