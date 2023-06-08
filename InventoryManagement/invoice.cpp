#include "Invoice.h"

Invoice::Invoice() = default;

Invoice::Invoice(std::string_view providerID){
    m_providerID = providerID;
    createInvoiceNumber();
}

void Invoice::addItem(const InvoiceItem item){
    m_items.addItem(item);
}

void Invoice::removeItem(const std::string_view targetSKU){
    m_items.removeItem(targetSKU);
}

void Invoice::clearInvoiceItems(){
    m_items.clearItems();
}

void Invoice::updateAmount(){
    m_totalAmount = 0;
    for (const InvoiceItem& item : m_items.getItems())
        m_totalAmount += item.getPrice()*item.getInventory();
}

void Invoice::updateNumSelectedItems(){
    m_numSelctedItems = 0;
    for (const InvoiceItem& item : m_items.getItems()){
        m_numSelctedItems += item.getInventory();
    }
}

void Invoice::setProviderID(std::string_view providerID){
    m_providerID = providerID;
}

const invoiceItems &Invoice::getInvoiceItemModel() const{
    return m_items;
}

invoiceItems &Invoice::editInvoiceItemModel(){
    return m_items;
}

const std::string& Invoice::getProviderID() const{
    return m_providerID;
}

double Invoice::getTotalAmount() const{
    return m_totalAmount;
}

double Invoice::getNumSelectedItems() const{
    return m_numSelctedItems;
}

void Invoice::createInvoiceNumber(){
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Generate a random number between 1000 and 10000
    int randomNumber = std::rand() % 9001 + 1000;
    std::cout << "Random number: " << randomNumber << std::endl;

    m_invoiceNumber = randomNumber;
}

void Invoice::clearInvoice(){
    m_invoiceNumber = 0;
    clearInvoiceItems();
    m_providerID = "";
    m_totalAmount = 0;
    m_numSelctedItems = 0;
}

const int Invoice::getInvoiceNumber() const{
    return m_invoiceNumber;
}
