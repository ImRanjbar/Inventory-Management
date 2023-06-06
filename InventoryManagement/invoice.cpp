#include "Invoice.h"

Invoice::Invoice() = default;

Invoice::Invoice(std::string_view providerID, double totalAmount = 0.0):
    m_providerID(providerID), m_totalAmount(totalAmount){}

void Invoice::addItem(const invoiceItem item){
    m_items.addItem(item);
}

void Invoice::removeItem(const std::string_view targetSKU){
    m_items.removeItem(targetSKU);
}

void Invoice::clearInvoice(){
    m_items.clearItems();
}

void Invoice::updateAmount(){
    m_totalAmount = 0;
    for (const invoiceItem& item : m_items.getItems())
        m_totalAmount += item.getPrice()*item.getInventory();
}

void Invoice::setProviderID(std::string_view providerID){
    m_providerID = providerID;
}

const invoiceItems &Invoice::getItems() const{
    return m_items;
}

invoiceItems &Invoice::editItems(){
    return m_items;
}

const std::string& Invoice::getProviderID() const{
    return m_providerID;
}

double Invoice::getTotalAmount() const{
    return m_totalAmount;
}
