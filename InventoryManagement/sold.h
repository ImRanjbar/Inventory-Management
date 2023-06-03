
#ifndef SOLD_H
#define SOLD_H

#include "invoiceItems.h"


class Sold
{
public:
    Sold();
    Sold(std::string_view date, std::string_view customerID, std::string_view invoiceID);
    void addItem(const invoiceItem& newItem);
    void setDate(const std::string_view invoiceDate);
    void setCustomerID(const std::string_view m_customerID);

    const invoiceItems& getItems();
    invoiceItems& editItems();
    const std::string& getInvoiceDate();
    const std::string& getCustomerID();
    const std::string& getInvoiceID();

private:
    invoiceItems m_items;
    std::string m_date;
    std::string m_customerID;
    std::string m_invoiceID;
};

#endif // SOLD_H
