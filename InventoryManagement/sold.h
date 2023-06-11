
#ifndef SOLD_H
#define SOLD_H

#include "Invoice.h"


class Sold
{
public:
    Sold();

    void sold(const Invoice& invoice);

    const std::vector<Invoice>& getInvoices() const;

    void addInvoice(const Invoice& invoice);

private:
    std::vector<Invoice> m_invoices;
};

#endif // SOLD_H
