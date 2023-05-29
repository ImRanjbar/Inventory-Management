
#include "user.h"

void User::setUsername(const std::string_view username) {
    m_username = username;
}

void User::setPassword(const std::string_view password) {
    m_password = password;
}

void User::addProduct(std::string_view name, std::string_view category, std::string_view sku
                      , std::string_view brand, std::string_view amount
                      , std::string_view price, std::string_view description
                      , std::string_view manufacturedDate, bool availability) {

    Product newProduct(name, category, sku, brand, amount, price, description, manufacturedDate, availability);
    m_products.push_back(newProduct);
}

const std::vector<Product>& User::getProducts() const
{
    return m_products;
}

void User::sortByName() {
    std::ranges::sort(m_products, {}, &Product::getName);
}

void User::sortByCategory(){
    std::ranges::sort(m_products, {}, &Product::getCategory);
}

void User::sortByBrand(){
    std::ranges::sort(m_products, {}, &Product::getBrand);
}

void User::sortByAmount(){
    std::ranges::sort(m_products, {}, &Product::getAmount);
}

void User::sortByDate(){
    std::ranges::sort(m_products, {}, &Product::getManufactureDate);
}


