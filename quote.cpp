#include "quote.h"

double print_total(std::ostream &os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}
// -------------------------- Quote ----------------------------

void Quote::debug() const
{
    std::cout << "bookNo:" << bookNo
              << " price:" << price << std::endl;
}

// ------------------------- Bulk_quote ------------------------

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt < quantity)
    {
        return cnt * price;
    }
    else
        return cnt * price * (1 - discount);
}

void Bulk_quote::debug() const
{
    std::cout << "bookNo:" << isbn()
              << " price:" << price
              << " quantity:" << quantity
              << " discount:" << discount << std::endl;
}