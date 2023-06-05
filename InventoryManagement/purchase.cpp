
#include "purchase.h"

Purchase::Purchase() = default;

Purchase::Purchase(std::string_view date, std::string_view providerID, std::string_view invoiceID) :
    m_date(date), m_providerID(providerID), m_invoiceNumber(invoiceID) {}

void Purchase::addItem(const invoiceItem& newItem) {
    m_items.addItem(newItem);
}

void Purchase::setDate(const std::string_view date) {
    m_date = date;
}

void Purchase::setProviderID(const std::string_view providerID) {
    m_providerID = providerID;
}

void Purchase::setInvoiceNumber(const std::string_view invoiceNumber){
    m_invoiceNumber = invoiceNumber;
}

const invoiceItems& Purchase::getItems() {
    return m_items;
}

invoiceItems& Purchase::editItems() {
    return m_items;
}

const std::string& Purchase::getProviderID() {
    return m_providerID;
}

const std::string& Purchase::getInvoiceDate() {
    return m_date;
}

const std::string& Purchase::getInvoiceNumber(){
    return m_invoiceNumber;
}
