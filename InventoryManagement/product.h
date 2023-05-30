
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

class Product
{
public:
    Product();
    Product(std::string_view name, std::string_view category, std::string_view sku
            , std::string_view brand, std::string_view amount
            , std::string_view price, std::string_view description
            , std::string_view manufacturedDate, bool availability);

    void setName(const std::string_view name);
    void setCategory(const std::string_view category);
    void setSku(const std::string_view sku);
    void setBrand(const std::string_view brand);
    void setAmount(const std::string_view amount);
    void setPrice(const std::string_view price);
    void setDescription(const std::string_view description);
    void setManufacture(const std::string_view manufacture);
    void setAvailability(const bool availability);
    void setUnit(std::string_view symbol);

    const std::string& getName() const;
    const std::string& getCategory() const;
    const std::string& getSku() const;
    const std::string& getBrand() const;
    const std::string& getAmount() const;
    const std::string& getPrice() const;
    const std::string& getDescription() const;
    const std::string& getManufactureDate() const;
    bool getAvailability() const;

private:
    std::string m_name;
    std::string m_category;
    std::string m_sku;
    std::string m_brand;
    std::string m_amount;
    std::string m_price;
    std::string m_description;
    std::string m_manufacturedDate;
    std::string m_unit;
    bool m_availability;

};

#endif // PRODUCT_H
