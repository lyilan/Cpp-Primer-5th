#include <string>
#include <iostream>
class HasPtr
{
public:
    // 构造函数
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0)
    {
        std::cout << "构造函数被调用" << std::endl;
    }
    // 拷贝构造函数
    HasPtr(const HasPtr &rhs)
    {
        ps = new std::string(*rhs.ps);
        i = rhs.i;
        std::cout << "拷贝构造函数被调用" << std::endl;
    }
    // 拷贝赋值运算符
    HasPtr &operator=(const HasPtr &rhs)
    {
        ps = new std::string(*rhs.ps);
        i = rhs.i;
        std::cout << "拷贝赋值运算符被调用" << std::endl;
        return *this;
    }
    void show() { std::cout << *ps << std::endl; }
    // 析构函数
    ~HasPtr() { std::cout << "析构函数被调用" << std::endl; }

private:
    std::string *ps;
    int i;
};

int main()
{
    HasPtr ptr1("hello"), ptr2;
    ptr2 = ptr1;
    ptr2.show();
    return 0;
}