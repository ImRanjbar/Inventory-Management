
#include "seller.h"

Seller::Seller() = default;

void Seller::setMID(const std::string_view MID) {
    m_MID = MID;
}

void Seller::setManufactureName(const std::string_view manufactureName) {
    m_manufactureName = manufactureName;
}

void Seller::addProduct(const Product& newProduct){
    if (newProduct.getAvailability() == true){
        invoiceItem newItem(newProduct.getName(), newProduct.getCategory(),
                            newProduct.getSku(), newProduct.getBrand(), newProduct.getAvailable()
                            , newProduct.getPrice(), newProduct.getUnit(), newProduct.getDescription()
                            , newProduct.getAddedDate(), newProduct.getExDate()
                            );
        m_items.addItem(newItem);
    }
    m_products.addProduct(newProduct);
}

void Seller::removerProduct(const std::string_view targetSKU){
    m_products.removeProduct(targetSKU);
    if (m_items.existence(targetSKU)){
        m_items.removeItem(targetSKU);
    }
}

void Seller::editProduct(const std::string_view targetSKU, std::string_view newName, std::string_view newCategory
                         , std::string_view newSKU, std::string_view newBrand, double newStock
                         , double newAvailable, double newPrice, std::string_view newUnit, std::string_view newDescription
                         , std::string_view newAddDate, std::string_view newExDate, bool newAvailability){
    if (m_products.existence(newSKU))
        return;
    else{
        if (m_products.getProduct(targetSKU).getAvailability())
            m_items.removeItem(targetSKU);

        m_products.removeProduct(targetSKU);

        Product product(newName, newCategory, newSKU, newBrand, newStock, newAvailable
                        , newPrice, newUnit, newDescription, newAddDate,newExDate, newAvailability);
        addProduct(product);
    }
}

void Seller::addCustomerID(const std::string_view customerID) {
    m_customerIDs.push_back(static_cast<std::string>(customerID));
}

void Seller::addProviderID(const std::string_view providerID){
    m_providerIDs.push_back(static_cast<std::string>(providerID));
}

const std::string& Seller::getMID() const{
    return m_MID;
}

const std::string& Seller::getManufactureName() const{
    return m_manufactureName;
}

const Products& Seller::getProductsModel() const{
    return m_products;
}

Products& Seller::editProducts() {
    return m_products;
}

const std::vector<Sold>& Seller::getHistory() const{
    return m_history;
}

std::vector<Sold>& Seller::editHistory(){
    return m_history;
}

const std::vector<Purchase>& Seller::getPurchaseHistory() const{
    return m_purchaseHistory;
}

std::vector<Purchase>& Seller::editPurchaseHistory(){
    return m_purchaseHistory;
}

const invoiceItems &Seller::getInvoiceItems() const {
    return m_items;
}

invoiceItems &Seller::editInvoiceItems(){
    return m_items;
}

const invoiceItem &Seller::getInvoiceItem(const std::string_view desiredSKU) const{
    return m_items.getItem(desiredSKU);
}

const std::vector<std::string>& Seller::getCutomerIDs() const{
    return m_customerIDs;
}

const std::vector<std::string>& Seller::getProviderIDs() const{
    return m_providerIDs;
}

const Invoice &Seller::getInvoice() const{
    return m_invoice;
}

Invoice &Seller::editInvoice(){
    return m_invoice;
}
