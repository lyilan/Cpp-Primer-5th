#include <iostream>
#include <string>
class Employee
{
public:
    Employee() : id(unique++), name("Bob") {}
    Employee(const std::string &s) { name = s; }
    Employee(const Employee& rhs) {
        name = rhs.name;
        id = rhs.id;
    }
private:
    static uint32_t unique;
    uint32_t id;
    std::string name;
};

uint32_t Employee::unique = 0;