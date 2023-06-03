
#include "seller.h"

Seller::Seller()
{

}

void Seller::setMID(const std::string_view MID) {
    m_MID = MID;
}

void Seller::setManufactureName(const std::string_view manufactureName) {
    m_manufactureName = manufactureName;
}

void Seller::addProduct(const Product& newItem){
    m_products.addProduct(newItem);
}

void Seller::addCustomerID(const std::string_view customerID) {
    m_customerIDs.push_back(static_cast<std::string>(customerID));
}

void Seller::addProviderID(const std::string_view providerID){
    m_providerIDs.push_back(static_cast<std::string>(providerID));
}

const std::string& Seller::getMID(){
    return m_MID;
}

const std::string& Seller::getManufactureName(){
    return m_manufactureName;
}

const Products& Seller::getProducts(){
    return m_products;
}

Products& Seller::editProducts(){
    return m_products;
}

const std::vector<Sold>& Seller::getHistory(){
    return m_history;
}

std::vector<Sold>& Seller::editHistory(){
    return m_history;
}

const std::vector<Purchase>& Seller::getPurchaseHistory(){
    return m_purchaseHistory;
}

std::vector<Purchase>& Seller::editPurchaseHistory(){
    return m_purchaseHistory;
}

const std::vector<std::string>& Seller::getCutomerIDs(){
    return m_customerIDs;
}

const std::vector<std::string>& Seller::getProviderIDs(){
    return m_providerIDs;
}

