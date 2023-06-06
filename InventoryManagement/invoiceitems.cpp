
#include "invoiceitems.h"

invoiceItems::invoiceItems() = default;

void invoiceItems::addItem(const invoiceItem& newItem) {
    if (!existence(newItem.getSku())) {
        m_items.emplace_back(newItem);
    }
    else {
        return;
    }
}

const invoiceItem& invoiceItems::getItem(const std::string_view desiredSku) const{
    auto productIterator = std::ranges::find_if(m_items, [&desiredSku](const invoiceItem& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

invoiceItem& invoiceItems::editItem(const std::string_view desiredSku) {
    auto productIterator = std::ranges::find_if(m_items, [&desiredSku](const invoiceItem& product) {
        return product.getSku() == desiredSku;
    });

    return *productIterator;
}

bool invoiceItems::existence(const std::string_view desiredSku) {
    bool doesExist = std::ranges::any_of(m_items, [desiredSku](const invoiceItem& product) {
        return product.getSku() == desiredSku;
    });

    return doesExist;
}

void invoiceItems::removeItem(std::string_view desiredSku) {
    std::erase_if(m_items, [&desiredSku](const invoiceItem& product) {
        return product.getSku() == desiredSku;
    });
}

void invoiceItems::clearItems(){
    m_items.clear();
}

const std::vector<invoiceItem>& invoiceItems::getItems() const {
    return m_items;
}

std::vector<invoiceItem>& invoiceItems::editItems(){
    return m_items;
}

void invoiceItems::sortByName() {
    std::ranges::sort(m_items, {}, &invoiceItem::getName);
}

void invoiceItems::sortByCategory() {
    std::ranges::sort(m_items, {}, &invoiceItem::getCategory);
}

void invoiceItems::sortByBrand() {
    std::ranges::sort(m_items, {}, &invoiceItem::getBrand);
}

void invoiceItems::sortByAmount() {
    std::ranges::sort(m_items, {}, &invoiceItem::getInventory);
}

void invoiceItems::sortByDate() {
    std::ranges::sort(m_items, {}, &invoiceItem::getAddedDate);
}
