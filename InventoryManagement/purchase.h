
#ifndef PURCHASE_H
#define PURCHASE_H

#include "Invoice.h"

class Purchase
{
public:
    Purchase();

    void purchase(const Invoice& invoice);

    const std::vector<Invoice>& getInvoices() const;

    std::vector<Invoice>& editInvoices();

    void addInvoice(const Invoice& invoice);

    const Invoice& getInvoice(const int invoiceNumber) const;

    Invoice& editInvoice(const int invoiceNumber);

private:
    std::vector<Invoice> m_invoices;
};

#endif // PURCHASE_H
