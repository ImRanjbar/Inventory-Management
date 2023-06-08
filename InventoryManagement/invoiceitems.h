
#ifndef INVOICEITEMS_H
#define INVOICEITEMS_H

#include "invoiceItem.h"
#include <vector>
#include <algorithm>

class invoiceItems
{
public:
    invoiceItems();
    void addItem(const InvoiceItem& newItem);
    void removeItem(const std::string_view sku);
    void clearItems();
    const InvoiceItem& getItem(const std::string_view sku) const;
    InvoiceItem& editItem(const std::string_view sku);
    const std::vector<InvoiceItem>& getItems() const;
    std::vector<InvoiceItem>& editItems();
    bool existence(const std::string_view sku) const;

    void sortByName();
    void sortByCategory();
    void sortByBrand();
    void sortByAmount();
    void sortByDate();

private:
    std::vector<InvoiceItem> m_items;
};

#endif // INVOICEITEMS_H
