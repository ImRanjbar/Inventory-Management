
#include "sold.h"

Sold::Sold() = default;

void Sold::sold(const Invoice &invoice){
    Invoice newInvoice = invoice;
    m_invoices.push_back(newInvoice);
}

const std::vector<Invoice> &Sold::getInvoices() const{
    return m_invoices;
}

std::vector<Invoice> &Sold::editInvoices(){
    return m_invoices;
}

void Sold::addInvoice(const Invoice &invoice){
    Invoice newInvoice = invoice;
    m_invoices.push_back(newInvoice);
}

const Invoice &Sold::getInvoice(const int invoiceNumber) const{
    std::vector<Invoice>::const_iterator invoiceIterator = std::ranges::find_if(m_invoices, [invoiceNumber](const Invoice& invoice) {
        return invoice.getInvoiceNumber() == invoiceNumber;
    });

    return *invoiceIterator;
}

Invoice &Sold::editInvoice(const int invoiceNumber){
    std::vector<Invoice>::iterator invoiceIterator = std::ranges::find_if(m_invoices, [invoiceNumber](Invoice& invoice) {
        return invoice.getInvoiceNumber() == invoiceNumber;
    });

    return *invoiceIterator;
}
