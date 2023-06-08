#ifndef SELLER_H
#define SELLER_H

#include "user.h"
#include "products.h"
#include "sold.h"
#include "purchase.h"
#include "Invoice.h"
#include "invoiceItems.h"

class Seller : public User {
public:
    Seller();

    void addProduct(const Product& newProduct);
    void removerProduct(const std::string_view targetSKU);
    void editProduct(const std::string_view targetSKU, std::string_view newName, std::string_view newCategory
                     , std::string_view newSKU, std::string_view newBrand, double newStock
                     , double newAvailable, double newPrice, std::string_view newUnit, std::string_view newDescription
                     , std::string_view newAddDate, std::string_view newExDate, bool newAvailability);

    void addCustomerID(const std::string_view customerID);
    void addProviderID(const std::string_view providerID);

    void setMID(const std::string_view MID);
    void setManufactureName(const std::string_view manufactureName);

    const std::string& getMID() const;
    const std::string& getManufactureName()const;

    const Products& getProductsModel() const;
    Products& editProducts();

    const std::vector<Sold>& getHistory() const;
    std::vector<Sold>& editHistory();

    const std::vector<Purchase>& getPurchaseHistory() const;
    std::vector<Purchase>& editPurchaseHistory();

    const invoiceItems& getInvoiceItemsModel() const;
    invoiceItems& editInvoiceItems();

    const std::vector<std::string>& getCutomerIDs() const;
    const std::vector<std::string>& getProviderIDs() const;

    void buy(const Product& product, const Seller& provider);
    void sell(const Product& product, const Seller& buyer);
    
    void addToInvoice(const Seller& provider, const InvoiceItem& item) {
        if (m_invoice.getProviderID() != provider.getMID()) {
            m_invoice.clearInvoiceItems();
            m_invoice.setProviderID(provider.getMID());
            m_invoice.addItem(item);
        }
        else {
            m_invoice.addItem(item);
        }
    }

    const Invoice& getInvoice() const;
    Invoice& editInvoice();

private:
    std::string m_MID;
    std::string m_manufactureName;
    Products m_products;
    invoiceItems m_items;
    std::vector<Sold> m_history;
    std::vector<Purchase> m_purchaseHistory;
    std::vector<std::string> m_customerIDs;
    std::vector<std::string> m_providerIDs;
    Invoice m_invoice;
};

#endif // SELLER_H
