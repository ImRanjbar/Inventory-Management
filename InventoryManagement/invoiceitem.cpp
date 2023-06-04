
#include "invoiceItem.h"

invoiceItem::invoiceItem() = default;

invoiceItem::invoiceItem(std::string_view name, std::string_view category, std::string_view sku,
                         std::string_view brand, double amount, double price,
                         std::string_view unit, std::string_view description, std::string_view addedDate,
                         std::string_view exDate)
    : m_name(name), m_category(category), m_sku(sku), m_brand(brand), m_amount(amount),
    m_price(price), m_unit(unit), m_description(description), m_addedDate(addedDate),
    m_exDate(exDate) {}

void invoiceItem::setName(const std::string_view name)
{
    m_name = name;
}

void invoiceItem::setCategory(const std::string_view category)
{
    m_category = category;
}

void invoiceItem::setSku(const std::string_view sku)
{
    m_sku = sku;
}

void invoiceItem::setBrand(const std::string_view brand)
{
    m_brand = brand;
}

void invoiceItem::setAmount(const double amount)
{
    m_amount = amount;
}

void invoiceItem::setPrice(const double price)
{
    m_price = price;
}

void invoiceItem::setUnit(std::string_view unit)
{
    m_unit = unit;
}

void invoiceItem::setDescription(const std::string_view description)
{
    m_description = description;
}

void invoiceItem::setAddedDate(const std::string_view addedDate)
{
    m_addedDate = addedDate;
}

void invoiceItem::setExDate(const std::string_view exDate)
{
    m_exDate = exDate;
}

void invoiceItem::setInvoiceID(const std::string_view invoiceID)
{
    m_invoiceID = invoiceID;
}

void invoiceItem::setCustomerID(const std::string_view customerID)
{
    m_customerID = customerID;
}

void invoiceItem::setProviderID(const std::string_view providerID){
    m_providerID = providerID;
}

const std::string& invoiceItem::getName() const
{
    return m_name;
}

const std::string& invoiceItem::getCategory() const
{
    return m_category;
}

const std::string& invoiceItem::getSku() const
{
    return m_sku;
}

const std::string& invoiceItem::getBrand() const
{
    return m_brand;
}

const double& invoiceItem::getAmount() const
{
    return m_amount;
}

const double& invoiceItem::getPrice() const
{
    return m_price;
}

const std::string& invoiceItem::getUnit() const
{
    return m_unit;
}

const std::string& invoiceItem::getDescription() const
{
    return m_description;
}

const std::string& invoiceItem::getAddedDate() const
{
    return m_addedDate;
}

const std::string& invoiceItem::getExDate() const
{
    return m_exDate;
}

const std::string& invoiceItem::getInvoiceID() const
{
    return m_invoiceID;
}

const std::string& invoiceItem::getCustomerID() const
{
    return m_customerID;
}

const std::string& invoiceItem::getProviderID() const
{
    return m_providerID;
}
