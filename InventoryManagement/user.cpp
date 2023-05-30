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

    if (!existence(sku)){
        Product newProduct(name, category, sku, brand, amount, price, description, manufacturedDate, availability);
        m_products.push_back(newProduct);
    }
    else{
        return;
    }
}

const Product& User::getProduct(const std::string_view desiredSku) {
    std::vector<Product>::iterator productIterator = std::ranges::find_if(m_products, [&desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

Product& User::editProduct(const std::string_view desiredSku){
    std::vector<Product>::iterator productIterator = std::ranges::find_if(m_products, [&desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

bool User::existence(const std::string_view desiredSku) {
    bool doesExist = std::ranges::any_of(m_products, [desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return doesExist;
}

void User::removeProduct(std::string_view desiredSku) {
    std::erase_if(m_products, [&desiredSku](const Product& product) {return (product.getSku() == desiredSku); });
}

const std::vector<Product>& User::getProducts() const
{
    return m_products;
}

void User::sortByName() {
    std::ranges::sort(m_products, {}, &Product::getName);
}

void User::sortByCategory() {
    std::ranges::sort(m_products, {}, &Product::getCategory);
}

void User::sortByBrand() {
    std::ranges::sort(m_products, {}, &Product::getBrand);
}

void User::sortByAmount() {
    std::ranges::sort(m_products, {}, &Product::getAmount);
}

void User::sortByDate() {
    std::ranges::sort(m_products, {}, &Product::getManufactureDate);
}


