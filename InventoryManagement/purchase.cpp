
#include "purchase.h"

Purchase::Purchase() = default;

void Purchase::addInvoice(const Invoice &invoice){
    Invoice newInvoice = invoice;
    m_invoices.push_back(newInvoice);
}

const Invoice &Purchase::getInvoice(const int invoiceNumber) const{
    std::vector<Invoice>::const_iterator invoiceIterator = std::ranges::find_if(m_invoices, [invoiceNumber](const Invoice& invoice) {
        return invoice.getInvoiceNumber() == invoiceNumber;
    });

    return *invoiceIterator;
}

Invoice &Purchase::editInvoice(const int invoiceNumber){
    std::vector<Invoice>::iterator invoiceIterator = std::ranges::find_if(m_invoices, [invoiceNumber](Invoice& invoice) {
        return invoice.getInvoiceNumber() == invoiceNumber;
    });

    return *invoiceIterator;
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
