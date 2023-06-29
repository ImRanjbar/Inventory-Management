
#include "sold.h"

Sold::Sold() = default;

//Sold::Sold(std::string_view date, std::string_view customerID, std::string_view invoiceID):
//    m_date(date), m_customerID(customerID), m_invoiceID(invoiceID) {}

//void Sold::addItem(const InvoiceItem& newItem){
//    m_items.addItem(newItem);
//}

//void Sold::setDate(const std::string_view date){
//    m_date = date;
//}

//void Sold::setCustomerID(const std::string_view customerID){
//    m_customerID = customerID;
//}

//const invoiceItems& Sold::getItems() const{
//    return m_items;
//}

//invoiceItems& Sold::editItems(){
//    return m_items;
//}

//const std::string& Sold::getCustomerID(){
//    return m_customerID;
//}

//const std::string& Sold::getInvoiceDate(){
//    return m_date;
//}

//const std::string& Sold::getInvoiceID(){
//    return m_invoiceID;
//}

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
