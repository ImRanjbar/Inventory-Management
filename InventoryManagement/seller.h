
#ifndef SELLER_H
#define SELLER_H

#include "user.h"
#include "products.h"
#include "sold.h"
#include "purchase.h"

class Seller : public User {
public:
    Seller();

    void setMID(const std::string_view MID);
    void setManufactureName(const std::string_view manufactureName);
    void addProduct(const Product& newItem);
    void addCustomerID(const std::string_view customerID);
    void addProviderID(const std::string_view providerID);

    const std::string& getMID();
    const std::string& getManufactureName();
    const Products& getProducts();
    Products& editProducts();
    const std::vector<Sold>& getHistory();
    std::vector<Sold>& editHistory();
    const std::vector<Purchase>& getPurchaseHistory();
    std::vector<Purchase>& editPurchaseHistory();
    const std::vector<std::string>& getCutomerIDs();
    const std::vector<std::string>& getProviderIDs();


private:
    std::string m_MID;
    std::string m_manufactureName;
    Products m_products;
    std::vector<Sold> m_history;
    std::vector<Purchase> m_purchaseHistory;
    std::vector<std::string> m_customerIDs;
    std::vector<std::string> m_providerIDs;

};

#endif // SELLER_H
