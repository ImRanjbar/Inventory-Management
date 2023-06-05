
#ifndef INVOICE_H
#define INVOICE_H

#include "invoiceitems.h"

class Invoice
{
public:
    Invoice();
    Invoice(std::string_view providerID, double totalAmount);

    void addItem(const invoiceItem item);
    void removeItem(const std::string_view desiredSKU);
    void clearInvoice();
    void updateAmount();

    void setProviderID(const std::string_view providerID);

    const invoiceItems& getItems() const;
    invoiceItems& editItems();

    const std::string& getProviderID() const;
    double getTotalAmount() const;

private:
    invoiceItems m_items;
    std::string m_providerID;
    double m_totalAmount;

};

#endif // INVOICE_H
