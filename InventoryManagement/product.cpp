
#include "product.h"

Product::Product(){}

Product::Product(std::string_view name, std::string_view category, std::string_view sku
                 , std::string_view brand, std::string_view amount
                 , std::string_view price, std::string_view description
                 , std::string_view manufacturedDate, bool availability)
    : m_name(name), m_category(category), m_sku(sku), m_brand(brand)
    , m_amount(amount), m_price(price), m_description(description)
    , m_manufacturedDate(manufacturedDate), m_availability(availability) {}

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

void Product::setAmount(const std::string_view amount) {
    m_amount = amount;
}

void Product::setPrice(const std::string_view price) {
    m_price = price;
}

void Product::setDescription(const std::string_view description) {
    m_description = description;
}

void Product::setManufacture(const std::string_view date){
    m_manufacturedDate = date;
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

const std::string& Product::getAmount() const {
    return m_amount;
}

const std::string& Product::getPrice() const {
    return m_price;
}

const std::string& Product::getDescription() const {
    return m_description;
}

const std::string& Product::getManufactureDate() const {
    return m_manufacturedDate;
}

bool Product::getAvailability() const {
    return m_availability;
}
