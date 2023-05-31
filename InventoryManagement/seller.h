
#ifndef SELLER_H
#define SELLER_H

#include "user.h"
#include "products.h"
#include "sold.h"

class Seller : public User {
public:
    Seller();

private:
    std::string m_sellerID;
    std::string m_marketName;
    Products m_products;
    std::vector<Sold> m_history;
    std::vector<std::string> customerIDs;

};

#endif // SELLER_H
