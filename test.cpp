#include <string>
#include <iostream>
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    ~HasPtr() { delete ps; }

private:
    std::string *ps;
    int i;
};

HasPtr f(HasPtr hp)
{
    HasPtr ret = hp;
    return ret;
}

int main()
{
    HasPtr p("some values");
    f(p);
    HasPtr q(p);
    std::cout << "hello world" << std::endl;
    return 0;
}