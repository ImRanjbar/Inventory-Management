
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "CurrencyConverter.h"

#include <string>
#include <sstream>
#include <fstream>
#include <qDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>


class DataHandler
{
public:
    DataHandler();

    void readData(Manufacturers* manufacturers);

    void removeQuotes(std::string& value);

    void saveData(Manufacturers* manufacturers);

    void readCurrencyRates(CurrencyConverter& currencyModel);

    void saveCurrencyRates(CurrencyConverter& currencyModel);

    // SQLite
    void openDatabase(QSqlDatabase& data);

    void closeDataBase(QSqlDatabase* data);

    void readDataLogin(Manufacturers* manufacturers);

    void readDataHomeWindow(Manufacturers* manufacturers, Seller* user);

    void readProducts(Seller* user);

    void addUser(Seller* newUser);

    void addProduct(Product* newProduct, const std::string& MID);

    void updateProduct(const std::string& productSKU,const Product& newProduct, const std::string& MID);

    void removeProduct(const std::string& productSKU, const std::string ownerMID);

    void readItems(Manufacturers* manufacturers, const std::string& userMID);

    void readInvoices(Seller& user);

    void readInvoiceItems(Invoice& invoice);

    void addInvoice(const Invoice& invoice);

    void updateCustomerProducts(Seller& customer, const Invoice& invoice);

    void updateProviderProducts(Seller& provider, const Invoice& invoice);

    void addInvoiceItems(const Invoice& invoice);

    void readInvoiceNumbers();
};

#endif // DATAHANDLER_H
