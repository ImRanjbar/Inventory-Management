
#ifndef INVOICEITEMS_H
#define INVOICEITEMS_H

#include "invoiceItem.h"
#include <vector>
#include <algorithm>

class invoiceItems
{
public:
    invoiceItems();
    void addItem(const invoiceItem& newItem);
    void removeItem(std::string_view sku);
    const invoiceItem& getItem(const std::string_view sku);
    invoiceItem& editItem(const std::string_view sku);
    const std::vector<invoiceItem>& getItems() const;
    std::vector<invoiceItem>& editItems();
    bool existence(const std::string_view sku);

    void sortByName();
    void sortByCategory();
    void sortByBrand();
    void sortByAmount();
    void sortByDate();

private:
    std::vector<invoiceItem> m_items;
};

#endif // INVOICEITEMS_H
