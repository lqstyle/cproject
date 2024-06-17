#include<iostream>
// 转义 R("xxx(原始字符串)xxx")
// https://subingwen.cn/cpp/R/
/**
 * 编程过程中，使用的字符串中常带有一些特殊字符，对于这些字符往往要做专门的处理，使用了原始字面量就可以轻松的解决这个问题
 *
 * 个字符串分别写到了不同的行里边，需要加连接符 繁琐且可读性强
 */








int main() {

    std::string s1 = "C:\nindows\tystem32\t2";
    std::string s = "C:\\Windows\\System32\\2";
    std::string s2 = R"("d:\hello\world\tell")";
    std::string s3 = R"111("d:\hello\world\tell")111";
    std::string s4 = R"11("d:\hello\world\tell")11";
    ::std::string s5 = R"(<html>\
        <head>\
        <title>\
        test\
        </title>\
        </head>\
        <body>\
        <p>\
        hello111\
        </p>\
        </body>\
        </html>)";
    std::cout << s1 << std::endl;
    std::cout << s << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;
    std::cout << s5 << std::endl;
    return 0;
}