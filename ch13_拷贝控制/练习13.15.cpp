#include <iostream>
class numbered
{
public:
    // 默认构造函数
    numbered() {mysn = unique++;}
    numbered(const numbered& rhs) {mysn = unique++;} 
    unsigned int mysn;
private:
    static unsigned int unique;
};

void f(numbered s) {std::cout << s.mysn << std::endl;}

// 静态变量成员初始化
unsigned int numbered::unique = 0;

int main() {
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}