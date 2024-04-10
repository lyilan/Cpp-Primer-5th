#include <iostream>
using namespace std;

class Point
{
public:
    // 默认构造函数
    Point() { cout << "Point()被调用" << endl; }
    // 拷贝构造函数
    Point(const Point &other) { cout << "Point(const Point &)被调用" << endl; }
};

Point global;
Point foo_bar(Point arg) {
    Point local = arg, *heap = new Point(global);
    *heap = local;
    Point pa[4] = {local, *heap};
    return *heap;
}

int main() {
    Point p;
    foo_bar(p);
    return 0;
}