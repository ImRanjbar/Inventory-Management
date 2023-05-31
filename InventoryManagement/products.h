
#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <vector>
#include <algorithm>
#include "product.h"

class Products
{
public:
    Products();

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
    std::vector<Product> m_products;
};

#endif // PRODUCTS_H
