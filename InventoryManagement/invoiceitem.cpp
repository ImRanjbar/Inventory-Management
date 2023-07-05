
#include "invoiceItem.h"

InvoiceItem::InvoiceItem() = default;

InvoiceItem::InvoiceItem(std::string_view name, std::string_view category, std::string_view sku,
                         std::string_view brand, double amount, double price,
                         std::string_view unit, std::string_view description, std::string_view addedDate,
                         std::string_view exDate)
    : m_name(name), m_category(category), m_sku(sku), m_brand(brand), m_inventory(amount),
    m_price(price), m_unit(unit), m_description(description), m_addedDate(addedDate),
    m_exDate(exDate) {}

void InvoiceItem::setName(const std::string_view name)
{
    m_name = name;
}

void InvoiceItem::setCategory(const std::string_view category)
{
    m_category = category;
}

void InvoiceItem::setSku(const std::string_view sku)
{
    m_sku = sku;
}

void InvoiceItem::setBrand(const std::string_view brand)
{
    m_brand = brand;
}

void InvoiceItem::setInventory(const double amount)
{
    m_inventory = amount;
}

void InvoiceItem::setPrice(const double price)
{
    m_price = price;
}

void InvoiceItem::setUnit(std::string_view unit)
{
    m_unit = unit;
}

void InvoiceItem::setDescription(const std::string_view description)
{
    m_description = description;
}

void InvoiceItem::setAddedDate(const std::string_view addedDate)
{
    m_addedDate = addedDate;
}

void InvoiceItem::setExDate(const std::string_view exDate)
{
    m_exDate = exDate;
}

void InvoiceItem::setInvoiceID(const std::string_view invoiceID)
{
    m_invoiceID = invoiceID;
}

void InvoiceItem::setCustomerID(const std::string_view customerID)
{
    m_customerID = customerID;
}

void InvoiceItem::setProviderID(const std::string_view providerID){
    m_providerID = providerID;
}

const std::string& InvoiceItem::getName() const
{
    return m_name;
}

const std::string& InvoiceItem::getCategory() const
{
    return m_category;
}

const std::string& InvoiceItem::getSku() const
{
    return m_sku;
}

const std::string& InvoiceItem::getBrand() const
{
    return m_brand;
}

const double& InvoiceItem::getInventory() const
{
    return m_inventory;
}

const double& InvoiceItem::getPrice() const
{
    return m_price;
}

const std::string& InvoiceItem::getUnit() const
{
    return m_unit;
}

const std::string& InvoiceItem::getDescription() const
{
    return m_description;
}

const std::string& InvoiceItem::getAddedDate() const
{
    return m_addedDate;
}

const std::string& InvoiceItem::getExDate() const
{
    return m_exDate;
}

const std::string& InvoiceItem::getInvoiceID() const
{
    return m_invoiceID;
}

const std::string& InvoiceItem::getCustomerID() const
{
    return m_customerID;
}

const std::string& InvoiceItem::getProviderID() const
{
    return m_providerID;
}
