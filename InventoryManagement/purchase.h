
#ifndef PURCHASE_H
#define PURCHASE_H

#include "Invoice.h"

class Purchase
{
public:
    Purchase();

    void purchase(const Invoice& invoice);

    const std::vector<Invoice>& getInvoices() const;

    void addInvoice(const Invoice& invoice);


private:
    std::vector<Invoice> m_invoices;
};

#endif // PURCHASE_H
