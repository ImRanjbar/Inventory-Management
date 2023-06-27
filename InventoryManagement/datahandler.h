
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
    QSqlDatabase& openDataBase();

    void closeDataBase(QSqlDatabase* data);

    void readDataLogin(Manufacturers* manufacturers);

    void readDataHomeWindow(Manufacturers* manufacturers, Seller* user);

    void readProducts(Seller* user);

};

#endif // DATAHANDLER_H
