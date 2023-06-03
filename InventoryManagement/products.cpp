
#include "products.h"

Products::Products()
{

}

void Products::addProduct(const Product& newItem) {

    if (!existence(newItem.getSku())){
        m_products.emplace_back(newItem);
    }
    else{
        return;
    }
}

const Product& Products::getProduct(const std::string_view desiredSku) {
    std::vector<Product>::iterator productIterator = std::ranges::find_if(m_products, [&desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

Product& Products::editProduct(const std::string_view desiredSku){
    std::vector<Product>::iterator productIterator = std::ranges::find_if(m_products, [&desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

bool Products::existence(const std::string_view desiredSku) {
    bool doesExist = std::ranges::any_of(m_products, [desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return doesExist;
}

void Products::removeProduct(std::string_view desiredSku) {
    std::erase_if(m_products, [&desiredSku](const Product& product) {return (product.getSku() == desiredSku); });
}

const std::vector<Product>& Products::getProducts() const
{
    return m_products;
}

void Products::sortByName() {
    std::ranges::sort(m_products, {}, &Product::getName);
}

void Products::sortByCategory() {
    std::ranges::sort(m_products, {}, &Product::getCategory);
}

void Products::sortByBrand() {
    std::ranges::sort(m_products, {}, &Product::getBrand);
}

void Products::sortByAmount() {
    std::ranges::sort(m_products, {}, &Product::getStock);
}

void Products::sortByDate() {
    std::ranges::sort(m_products, {}, &Product::getAddedDate);
}
