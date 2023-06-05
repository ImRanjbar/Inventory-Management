
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "manufacturers.h"

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
};

#endif // DATAHANDLER_H
