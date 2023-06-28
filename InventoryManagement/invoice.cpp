#include "Invoice.h"
#include "InvoiceNumbers.h"

Invoice::Invoice() = default;

//Invoice::Invoice(std::string_view providerID){
//    m_providerID = providerID;
//    createInvoiceNumber();
//}

Invoice::Invoice(const int invoiceNumber, const std::string_view providerID, const std::string_view customerID
                 , const std::string_view providerName, const std::string_view customerName, const double amount, const std::string_view date) :
    m_invoiceNumber(invoiceNumber), m_providerID(providerID), m_providerManuName(providerName), m_customerID(customerID)
    , m_customerManuName(customerName),m_date(date) , m_totalAmount(amount) {}


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

const std::string &Invoice::getCustomerID() const{
    return m_customerID;
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
    if (InvoiceNumbers::invoiceNumbers.contains(randomNumber)){
        createInvoiceNumber();
    }

    m_invoiceNumber = randomNumber;
}

//bool Invoice::invoiceNumberExistence(){

//}

void Invoice::clearInvoice(){
    m_invoiceNumber = 0;
    clearInvoiceItems();
    m_providerManuName = "";
    m_providerID = "";
    m_totalAmount = 0;
    m_numSelctedItems = 0;
}

const int Invoice::getInvoiceNumber() const{
    return m_invoiceNumber;
}

const std::string &Invoice::getProviderName() const{
    return m_providerManuName;
}

const std::string &Invoice::getCustomerName() const{
    return m_customerManuName;
}

const std::string &Invoice::getDate() const{
    return m_date;
}

void Invoice::setProviderName(const std::string_view providerName){
    m_providerManuName = providerName;
}

void Invoice::setCustomerName(const std::string_view customerName){
    m_customerManuName = customerName;
}

void Invoice::setCustomerID(const std::string_view customerID){
    m_customerID = customerID;
}

void Invoice::setDate(const std::string_view date){
    m_date = date;
}
