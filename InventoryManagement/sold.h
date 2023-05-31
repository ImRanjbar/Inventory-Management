
#ifndef SOLD_H
#define SOLD_H

#include "products.h"


class Sold
{
public:
    Sold();
private:
    Products m_products;
    std::string m_date;
    std::string m_customerID;
};

#endif // SOLD_H
