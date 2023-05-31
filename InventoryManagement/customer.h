
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "purchase.h"

class Customer : public User {
public:
    Customer();
private:
    std::string m_customerID;
    Products m_products;
    Purchase m_history;

};

#endif // CUSTOMER_H
