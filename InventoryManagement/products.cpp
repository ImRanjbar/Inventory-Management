
#include "products.h"
#include <QDebug>
Products::Products() = default;

void Products::addProduct(const Product& newItem) {
    qDebug() << "in Products::addProduct function\n";
    if (!existence(newItem.getSku())) {
        qDebug() << "The product with " << newItem.getSku() << " sku " << "have added to products\n";
        m_products.emplace_back(newItem);
    }
    else {
        return;
    }
}

const Product& Products::getProduct(const std::string_view desiredSku) const{
    std::vector<Product>::const_iterator productIterator = std::ranges::find_if(m_products, [&desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

Product& Products::editProduct(const std::string_view desiredSku) {
    std::vector<Product>::iterator productIterator = std::ranges::find_if(m_products, [&desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

bool Products::existence(const std::string_view desiredSku) const {
    bool doesExist = std::ranges::any_of(m_products, [desiredSku](const Product& product) {
        return product.getSku() == desiredSku;
    });

    return doesExist;
}

void Products::sortBySKU(){
    std::ranges::sort(m_products, {}, &Product::getSku);
}

void Products::sortBySKUdes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getSku);
}

void Products::removeProduct(std::string_view desiredSku) {
    std::erase_if(m_products, [&desiredSku](const Product& product) {return (product.getSku() == desiredSku); });
}

const std::vector<Product>& Products::getProducts() const {
    return m_products;
}

void Products::sortByName() {
    std::ranges::sort(m_products, {}, &Product::getName);
}

void Products::sortByNameDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getName);
}

void Products::sortByCategory() {
    std::ranges::sort(m_products, {}, &Product::getCategory);
}

void Products::sortByCategoryDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getCategory);
}

void Products::sortByBrand() {
    std::ranges::sort(m_products, {}, &Product::getBrand);
}

void Products::sortByBrandDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getBrand);
}

void Products::sortByPrice(){
    std::ranges::sort(m_products, {}, &Product::getPrice);
}

void Products::sortByPriceDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getPrice);
}

void Products::sortByStock() {
    std::ranges::sort(m_products, {}, &Product::getStock);
}

void Products::sortByStockDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getStock);
}

void Products::sortByAvailable(){
    std::ranges::sort(m_products, {}, &Product::getAvailable);
}

void Products::sortByAvailableDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getAvailable);
}

void Products::sortByAddDate() {
    std::ranges::sort(m_products, {}, &Product::getAddedDate);
}

void Products::sortByAddDateDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getAddedDate);
}

void Products::sortByExDate(){
    std::ranges::sort(m_products, {}, &Product::getExDate);
}

void Products::sortByExDateDes(){
    std::ranges::sort(m_products, std::greater<>{}, &Product::getExDate);
}
