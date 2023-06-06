
#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <vector>
#include <algorithm>
#include "product.h"

class Products
{
public:
    Products();

    void addProduct(const Product& newItem);
    void removeProduct(std::string_view sku);
    const Product& getProduct(const std::string_view sku) const;
    Product& editProduct(const std::string_view sku);
    const std::vector<Product>& getProducts() const;
    bool existence(const std::string_view sku) const;

    void sortBySKU();
    void sortBySKUdes();
    void sortByName();
    void sortByNameDes();
    void sortByCategory();
    void sortByCategoryDes();
    void sortByBrand();
    void sortByBrandDes();
    void sortByPrice();
    void sortByPriceDes();
    void sortByStock();
    void sortByStockDes();
    void sortByAvailable();
    void sortByAvailableDes();
    void sortByAddDate();
    void sortByAddDateDes();
    void sortByExDate();
    void sortByExDateDes();

private:
    std::vector<Product> m_products;
};

#endif // PRODUCTS_H
