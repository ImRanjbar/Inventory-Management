
#ifndef USER_H
#define USER_H

#include "product.h"
#include <algorithm>
#include <vector>

class User {

public:
    void setUsername(const std::string_view username);
    void setPassword(const std::string_view password);

    void addProduct(std::string_view name, std::string_view category, std::string_view sku
                    , std::string_view brand, std::string_view amount
                    , std::string_view price, std::string_view description
                    , std::string_view manufacturedDate, bool availability);
    void removeProduct(std::string_view sku);
    const Product& getProduct(const std::string_view sku);
    Product& editProduct(const std::string_view sku);
    const std::vector<Product>& getProducts() const;
    bool existence(const std::string_view sku);

    void sortByName();
    void sortByCategory();
    void sortByBrand();
    void sortByAmount();
    void sortByDate();

private:
    std::string m_username;
    std::string m_password;
    std::vector<Product> m_products;

};

#endif // USER_H
