
#ifndef PURCHASE_H
#define PURCHASE_H

#include "invoiceitems.h"


class Purchase
{
public:
    Purchase();
    Purchase(std::string_view date, std::string_view customerID, std::string_view invoiceID);
    void addItem(const invoiceItem& newItem);
    void setDate(const std::string_view invoiceDate);
    void setProviderID(const std::string_view providerID);
    void setInvoiceNumber(const std::string_view invoiceNumber);

    const invoiceItems& getItems();
    invoiceItems& editItems();
    const std::string& getInvoiceDate();
    const std::string& getProviderID();
    const std::string& getInvoiceNumber();

private:
    invoiceItems m_items;
    std::string m_date;
    std::string m_providerID;
    std::string m_invoiceNumber;
};

#endif // PURCHASE_H
