
#include "invoiceitems.h"

invoiceItems::invoiceItems() = default;

void invoiceItems::addItem(const InvoiceItem& newItem) {
    if (!existence(newItem.getSku())) {
        m_items.emplace_back(newItem);
    }
    else {
        return;
    }
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

bool invoiceItems::existence(const std::string_view desiredSku) const{
    bool doesExist = std::ranges::any_of(m_items, [desiredSku](const InvoiceItem& item) {
        return item.getSku() == desiredSku;
    });

    return doesExist;
}

void invoiceItems::removeItem(std::string_view desiredSku) {
    std::erase_if(m_items, [&desiredSku](const InvoiceItem& product) {
        return product.getSku() == desiredSku;
    });
}

void invoiceItems::clearItems(){
    m_items.clear();
}

const std::vector<InvoiceItem>& invoiceItems::getItems() const {
    return m_items;
}

std::vector<InvoiceItem>& invoiceItems::editItems(){
    return m_items;
}

void invoiceItems::sortByName() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getName);
}

void invoiceItems::sortByCategory() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getCategory);
}

void invoiceItems::sortByBrand() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getBrand);
}

void invoiceItems::sortByAmount() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getInventory);
}

void invoiceItems::sortByDate() {
    std::ranges::sort(m_items, {}, &InvoiceItem::getAddedDate);
}
