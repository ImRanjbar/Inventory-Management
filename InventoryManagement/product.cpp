
#include "product.h"

Product::Product(){}

Product::Product(std::string_view name, std::string_view category, std::string_view sku
                 , std::string_view brand, std::string_view stock
                 , std::string_view avaialable, std::string_view price
                 , std::string_view unit, std::string_view description
                 , std::string_view addedDate, std::string_view exDate, bool availability)
    : m_name(name), m_category(category), m_sku(sku), m_brand(brand)
    , m_stock(stock),m_available(avaialable), m_price(price),m_unit(unit), m_description(description)
    , m_addedDate(addedDate), m_exDate(exDate), m_availability(availability) {}

void Product::setName(const std::string_view name) {
    m_name = name;
}

void Product::setCategory(const std::string_view category) {
    m_category = category;
}

void Product::setSku(const std::string_view sku) {
    m_sku = sku;
}

void Product::setBrand(const std::string_view brand) {
    m_brand = brand;
}

void Product::setStock(const std::string_view stock) {
    m_stock = stock;
}

void Product::setAvailable(const std::string_view available){
    m_available = available;
}

void Product::setPrice(const std::string_view price) {
    m_price = price;
}

void Product::setDescription(const std::string_view description) {
    m_description = description;
}

void Product::setAddedDate(const std::string_view addedDate){
    m_addedDate = addedDate;
}

void Product::setExDate(const std::string_view exDate){
    m_exDate = exDate;
}

void Product::setAvailability(const bool availability) {
    m_availability = availability;
}

void Product::setUnit(std::string_view symbol) {
    m_unit = symbol;
}

const std::string& Product::getName() const {
    return m_name;
}

const std::string& Product::getCategory() const {
    return m_category;
}

const std::string& Product::getSku() const {
    return m_sku;
}

const std::string& Product::getBrand() const {
    return m_brand;
}

const std::string& Product::getStock() const {
    return m_stock;
}

const std::string& Product::getAvailable() const {
    return m_available;
}

const std::string& Product::getPrice() const {
    return m_price;
}

const std::string& Product::getUnit() const {
    return m_unit;
}

const std::string& Product::getDescription() const {
    return m_description;
}

const std::string& Product::getAddedDate() const {
    return m_addedDate;
}

const std::string& Product::getExDate() const {
    return m_addedDate;
}

bool Product::getAvailability() const {
    return m_availability;
}
