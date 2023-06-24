
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "CurrencyConverter.h"

#include <string>
#include <sstream>
#include <fstream>
#include <qDebug>

class DataHandler
{
public:
    DataHandler();

    void readData(Manufacturers* manufacturers);

    void removeQuotes(std::string& value);

    void saveData(Manufacturers* manufacturers);

    void readCurrencyRates(CurrencyConverter& currencyModel);

    void saveCurrencyRates(CurrencyConverter& currencyModel);
};

#endif // DATAHANDLER_H
