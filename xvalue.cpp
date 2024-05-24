#include<iostream>
#include<vector>
#include <utility>
#include <iomanip>

int main() {

    std::string s1 = "hello c++";
    std::vector<std::string> v;
    v.push_back(s1);
    ::std::cout << s1 << ::std::endl;
    static_cast(s1);
    v.push_back(std::move(s1));
    ::std::cout << std::quoted(s1) << ::std::endl;
    std::cout << "The contents of the vector are {" << std::quoted(v[0])
              << ", " << std::quoted(v[1]) << "}\n";
    return 0;
}