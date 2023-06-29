
#include "purchase.h"

Purchase::Purchase() = default;

void Purchase::addInvoice(const Invoice &invoice){
    Invoice newInvoice = invoice;
    m_invoices.push_back(newInvoice);
}

void Purchase::purchase(const Invoice &invoice){
    Invoice newInvoice = invoice;
    m_invoices.push_back(newInvoice);
}

const std::vector<Invoice> &Purchase::getInvoices() const{
    return m_invoices;
}

std::vector<Invoice> &Purchase::editInvoices(){
    return m_invoices;
}
