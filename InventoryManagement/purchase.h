
#ifndef PURCHASE_H
#define PURCHASE_H

#include "products.h"


class Purchase
{
public:
    Purchase();

private:
    Products m_puchase;
    std::string m_date;
    std::string m_sellerID;
};

#endif // PURCHASE_H
