
#include "invoiceitems.h"

invoiceItems::invoiceItems() = default;

void invoiceItems::addItem(const InvoiceItem& newItem) {
    if (!existence(newItem.getSku())) {
        m_items.emplace_back(newItem);
    }
    else {
        removeItem(newItem.getSku());
        m_items.emplace_back(newItem);
    }
}

void invoiceItems::removeItem(std::string_view desiredSku) {
    std::erase_if(m_items, [&desiredSku](const InvoiceItem& product) {
        return product.getSku() == desiredSku;
    });
}

void invoiceItems::clearItems(){
    m_items.clear();
}

const InvoiceItem& invoiceItems::getItem(const std::string_view desiredSku) const{
    auto productIterator = std::ranges::find_if(m_items, [&desiredSku](const InvoiceItem& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

InvoiceItem& invoiceItems::editItem(const std::string_view desiredSku) {
    auto productIterator = std::ranges::find_if(m_items, [&desiredSku](const InvoiceItem& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

const std::vector<InvoiceItem>& invoiceItems::getItems() const {
    return m_items;
}

std::vector<InvoiceItem>& invoiceItems::editItems(){
    return m_items;
}

bool invoiceItems::existence(const std::string_view desiredSku) const{
    bool doesExist = std::ranges::any_of(m_items, [desiredSku](const InvoiceItem& item) {
        return item.getSku() == desiredSku;
    });

    return doesExist;
}

void invoiceItems::sortBySKU(){
    std::ranges::sort(m_items, {}, &InvoiceItem::getSku);
}

void invoiceItems::sortBySkuDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getSku);
}

void invoiceItems::sortByName() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getName);
}

void invoiceItems::sortByNameDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getName);
}

void invoiceItems::sortByCategory() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getCategory);
}

void invoiceItems::sortByCategoryDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getCategory);
}

void invoiceItems::sortByBrand() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getBrand);
}

void invoiceItems::sortByBrandDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getBrand);
}

void invoiceItems::sortByPrice(){
    std::ranges::sort(m_items, {}, &InvoiceItem::getPrice);
}

void invoiceItems::sortByPriceDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getPrice);
}

void invoiceItems::sortByInventory() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getInventory);
}

void invoiceItems::sortByInventoryDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getInventory);
}

void invoiceItems::sortByUnit(){
    std::ranges::sort(m_items, {}, &InvoiceItem::getUnit);
}

void invoiceItems::sortByUnitDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getUnit);
}

void invoiceItems::sortByAddDate() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getAddedDate);
}

void invoiceItems::sortByAddDateDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getAddedDate);
}

void invoiceItems::sortByExDate(){
    std::ranges::sort(m_items, {}, &InvoiceItem::getExDate);
}

void invoiceItems::sortByExDateDes(){
    std::ranges::sort(m_items, std::greater<>{}, &InvoiceItem::getExDate);
}
