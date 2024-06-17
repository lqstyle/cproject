#include<iostream>
// 转义 R("xxx(原始字符串)xxx")
// https://subingwen.cn/cpp/R/
int main() {

    std::string s1 = "C:\Windows\System32\t2";
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