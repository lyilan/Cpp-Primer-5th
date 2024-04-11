#include <iostream>
#include <vector>
struct X
{
    X() { std::cout << "X()" << std::endl; }
    X(const X &) { std::cout << "X(const X&)" << std::endl; }
    X &operator=(const X &rhs)
    {
        std::cout << "X& operator=(const X& rhs)" << std::endl;
        return *this;
    }
    ~X() { std::cout << "~X()" << std::endl; };
};

void conf(const X &x) { return; }

void noconf(const X x) { return; }

int main()
{
    X x1;
    conf(x1);
    noconf(x1);
    X *x2 = new X;
    std::vector<X> v;
    v.push_back(*x2);
    v.pop_back();
    delete x2;
    return 0;
}