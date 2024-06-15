

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <memory>

using String = ::std::string;


class Student {

public:
    Student(std::string name, int age) : name(std::move(name)), age(age) {
        std::cout << "con" << std::endl;
    }

    ~Student() {
        std::cout << "dec" << std::endl;
    };


    Student(const Student &other) {
        std::cout << "copy" << std::endl;
    }

    Student &operator=(Student &&other) noexcept {
        std::cout << "move =" << std::endl;

        if (this != &other) {
            age = other.age;
            name = other.name;
        }
        std::cout << "move =" << std::endl;
        return *this;
    }

    // 拷贝赋值运算符
    Student &operator=(const Student &other) {
        if (this != &other) {
            age = other.age;
            name = other.name;
        }
        std::cout << "fees" << std::endl;
        return *this;
    }


public :
    std::string name;
    int age{};
};

//
//int main() {
//
////    std::vector<std::unique_ptr<Student>> vector;
////
////    std::unique_ptr<Student> student = std::make_unique<Student>("lq", 11);
////    std::unique_ptr<Student> student2 = std::make_unique<Student>("dd",22);
////    vector.push_back(std::move(student));
////    vector.push_back(std::move(student2));
//
//    return 0;
//}