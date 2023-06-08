
#include "sold.h"

Sold::Sold() = default;

Sold::Sold(std::string_view date, std::string_view customerID, std::string_view invoiceID):
    m_date(date), m_customerID(customerID), m_invoiceID(invoiceID) {}

void Sold::addItem(const InvoiceItem& newItem){
    m_items.addItem(newItem);
}

void Sold::setDate(const std::string_view date){
    m_date = date;
}

void Sold::setCustomerID(const std::string_view customerID){
    m_customerID = customerID;
}

const invoiceItems& Sold::getItems() const{
    return m_items;
}

invoiceItems& Sold::editItems(){
    return m_items;
}

const std::string& Sold::getCustomerID(){
    return m_customerID;
}

const std::string& Sold::getInvoiceDate(){
    return m_date;
}

const std::string& Sold::getInvoiceID(){
    return m_invoiceID;
}
