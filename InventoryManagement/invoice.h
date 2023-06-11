
#ifndef INVOICE_H
#define INVOICE_H

#include "invoiceitems.h"
#include <cstdlib>
#include <ctime>

class   Invoice
{
public:
    Invoice();
//    Invoice(std::string_view providerID);
    Invoice(const int invoiceNumber, const std::string_view providerID, const std::string_view customerID
            , const std::string_view providerName, const std::string_view customerName, const std::string_view date);


    void addItem(const InvoiceItem item);
    void removeItem(const std::string_view desiredSKU);
    void clearInvoiceItems();
    void updateAmount();
    void updateNumSelectedItems();

    void setProviderID(const std::string_view providerID);

    const invoiceItems& getInvoiceItemModel() const;
    invoiceItems& editInvoiceItemModel();

    const std::string& getProviderID() const;

    const std::string& getCustomerID() const;

    double getTotalAmount() const;

    double getNumSelectedItems() const;

    void createInvoiceNumber();

//    bool invoiceNumberExistence();

    void clearInvoice();

    const int getInvoiceNumber() const;

    const std::string& getProviderName() const;

    const std::string& getCustomerName() const;

    const std::string& getDate() const;

    void setProviderName(const std::string_view providerName);

    void setCustomerName(const std::string_view customerName);

    void setCustomerID(const std::string_view customerID);

    void setDate(const std::string_view date);




private:
    int m_invoiceNumber;
    invoiceItems m_items;
    std::string m_providerID;
    std::string m_providerManuName;
    std::string m_customerID;
    std::string m_customerManuName;
    std::string m_date;

    double m_totalAmount;
    double m_numSelctedItems;

};

#endif // INVOICE_H
