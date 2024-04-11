#include "练习13.39.h"

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc(); // 确保有空间容纳新元素
    // 在first_free指向的元素中构造s的副本
    alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    // 分配空间保存给定范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个pair,该pair由data和uninitialized_copy的返回值构成
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    // 不能传递给deallocate一个空指针，如果elements为0，什么也不做
    if (elements)
    {
        // 逆序销毁旧元素
        for (auto p = first_free; p != elements; p--)
            alloc.destroy(p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    // 分配两倍当前大小的空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;  // 指向新数组的下一个空闲位置
    auto elem = elements; // 指向旧数组的下一个元素位置
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = newdata + newcapacity;
}

void StrVec::reserve(size_t n)
{
    if (capacity() < n)
    {
        auto newdata = alloc.allocate(n);
        auto dest = newdata;
        auto elem = elements;
        for (size_t i = 0; i != n; ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = newdata + n;
    }
}
