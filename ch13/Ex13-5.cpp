#include <string>
#include <iostream>
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {
        std::cout << "默认构造函数被调用" << std::endl;
    }
    HasPtr(const HasPtr&);
    void show() {std::cout << *ps << std::endl;}
private:
    std::string *ps;
    int i;
};

HasPtr::HasPtr(const HasPtr& rhs) {
    ps = new std::string(*rhs.ps);
    i = rhs.i;
    std::cout << "拷贝构造函数被调用" << std::endl;
}

int main() {
    HasPtr ptr1("hello");
    HasPtr ptr2 = ptr1;
    ptr2.show();
    return 0;
}