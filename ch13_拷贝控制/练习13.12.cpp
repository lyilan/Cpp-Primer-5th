#include <iostream>

class Sales_data
{
public:
    Sales_data() = default;
    Sales_data(int i) : id(i) {}
    ~Sales_data() { std::cout << "析构函数被调用" << std::endl; }
    int id = 0;
};

bool fcn(const Sales_data *trans, Sales_data accum)
{
    Sales_data item1(*trans), item2(accum);
    return false;
}

int main()
{
    Sales_data d1(1), d2(2);
    fcn(&d1, d2);
    return 0;
}