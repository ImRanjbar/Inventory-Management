
#include "datahandler.h"
#include "invoice_numbers.h"
#include "currency.h"

DataHandler::DataHandler() = default;

void DataHandler::readData(Manufacturers* manufacturers){
    std::ifstream file("data.csv");
    std::string line;

    qDebug() << "in readData function\n";
    int usersIndex{ -1 };
    int invoiceIndex;
    int itemsNum;

    if (file.is_open())
        qDebug() << "file is open\n";
    else {
        qDebug() << "file cannot be opened\n";
        return; // or handle the error appropriately
    }

    while (std::getline(file, line)) {
        qDebug() << "in the while loop of readData function\n";
        std::string first;
        std::stringstream ss(line);
        std::getline(ss, first, ',');
        removeQuotes(first);
        if (first == "appCurrency"){
            std::string currency;
            std::getline(ss, currency, ',');
            removeQuotes(currency);
            Currency::currentCurrency = currency;

            std::string symbol;
            std::getline(ss, symbol, ',');
            removeQuotes(symbol);
            Currency::currencySymbol = symbol;
            qDebug() << "currency have read\n";
        }
        else if (first == "appUsername") {
            Seller* newSeller = new Seller;

            std::string username;
            qDebug() << "username have read!\n";
            std::getline(ss, username, ',');
            removeQuotes(username);
            newSeller->setUsername(username);

            std::string password;
            std::getline(ss, password, ',');
            removeQuotes(password);
            newSeller->setPassword(password);

            std::string name;
            std::getline(ss, name, ',');
            removeQuotes(name);
            newSeller->setName(name);

            std::string lastName;
            std::getline(ss, lastName, ',');
            removeQuotes(lastName);
            newSeller->setLastName(lastName);

            std::string NIN;
            std::getline(ss, NIN, ',');
            removeQuotes(NIN);
            newSeller->setNIN(NIN);

            std::string phoneNumber;
            std::getline(ss, phoneNumber, ',');
            removeQuotes(phoneNumber);
            newSeller->setPhoneNumber(phoneNumber);

            std::string manufactureName;
            std::getline(ss, manufactureName, ',');
            removeQuotes(manufactureName);
            newSeller->setManufactureName(manufactureName);

            std::string MID;
            std::getline(ss, MID, ',');
            removeQuotes(MID);
            newSeller->setMID(MID);

            manufacturers->addManufact(newSeller);
            usersIndex++;

            continue;
        }

        else if (first == "appProduct") {


            std::string name;
            std::getline(ss, name, ',');
            removeQuotes(name);

            std::string category;
            std::getline(ss, category, ',');
            removeQuotes(category);

            std::string SKU;
            std::getline(ss, SKU, ',');
            removeQuotes(SKU);

            std::string brand;
            std::getline(ss, brand, ',');
            removeQuotes(brand);

            std::string stock;
            std::getline(ss, stock, ',');

            std::string available;
            std::getline(ss, available, ',');

            std::string price;
            std::getline(ss, price, ',');

            std::string unit;
            std::getline(ss, unit, ',');
            removeQuotes(unit);

            std::string description;
            std::getline(ss, description, ',');
            removeQuotes(description);

            std::string addDate;
            std::getline(ss, addDate, ',');
            removeQuotes(addDate);

            std::string exDate;
            std::getline(ss, exDate, ',');
            removeQuotes(exDate);

            double temp = std::stod(available);
            bool availability = ([temp](){ return temp > 0; })();

            Product newItem(name, category, SKU, brand, std::stod(stock), std::stod(available), std::stod(price), unit
                            , description, addDate, exDate, availability);
            manufacturers->editManufacturers()[usersIndex]->addProduct(newItem);

            continue;
        }

        else if (first == "appInvoice"){

            qDebug() << "adding a invoice \n";

            std::string invoiceNumber;
            std::getline(ss, invoiceNumber, ',');

            std::string providerName;
            std::getline(ss, providerName, ',');
            removeQuotes(providerName);

            std::string customerName;
            std::getline(ss, customerName, ',');
            removeQuotes(customerName);

            std::string providerMID;
            std::getline(ss, providerMID, ',');
            removeQuotes(providerMID);

            std::string customerMID;
            std::getline(ss, customerMID, ',');
            removeQuotes(customerMID);

            std::string amount;
            std::getline(ss, amount, ',');

            std::string date;
            std::getline(ss, date,',');
            removeQuotes(date);

            std::string numberOfSupplies;
            std::getline(ss, numberOfSupplies, ',');

            itemsNum = std::stod(numberOfSupplies);


            Invoice newInvoice(std::stoi(invoiceNumber), providerMID, customerMID, providerName, customerName, std::stod(amount), date);
            invoiceNumbers.insert(std::stoi(invoiceNumber));

            manufacturers->editManufacturers()[usersIndex]->setInvoice(newInvoice);

        }

        else if (first == "appInvoiceItem"){

            std::string name;
            std::getline(ss, name, ',');
            removeQuotes(name);

            std::string category;
            std::getline(ss, category, ',');
            removeQuotes(category);

            std::string SKU;
            std::getline(ss, SKU, ',');
            removeQuotes(SKU);

            std::string brand;
            std::getline(ss, brand, ',');
            removeQuotes(brand);

            std::string inventory;
            std::getline(ss, inventory, ',');

            std::string price;
            std::getline(ss, price, ',');

            std::string unit;
            std::getline(ss, unit, ',');
            removeQuotes(unit);

            std::string description;
            std::getline(ss, description, ',');
            removeQuotes(description);

            std::string addDate;
            std::getline(ss ,addDate, ',');
            removeQuotes(addDate);

            std::string exDate;
            std::getline(ss, exDate,',');
            removeQuotes(exDate);

            InvoiceItem newItem(name, category, SKU, brand, std::stod(inventory)
                                , std::stod(price), unit, description, addDate,exDate );
            manufacturers->editManufacturers()[usersIndex]->editInvoice().addItem(newItem);

            itemsNum--;
            if (itemsNum == 0){
                if (manufacturers->editManufacturers()[usersIndex]->getInvoice().getProviderID()
                    == manufacturers->getManufacturers()[usersIndex]->getMID()){

                    manufacturers->editManufacturers()[usersIndex]->editSoldModel()
                        .addInvoice(manufacturers->getManufacturers()[usersIndex]->getInvoice());

                    // Clear Invoice of user
                    manufacturers->editManufacturers()[usersIndex]->editInvoice().clearInvoice();

                }
                else {

                    manufacturers->editManufacturers()[usersIndex]->editPurchaseModel()
                        .addInvoice(manufacturers->getManufacturers()[usersIndex]->getInvoice());

                    // Clear Invoice of user
                    manufacturers->editManufacturers()[usersIndex]->editInvoice().clearInvoice();

                }
            }
        }

    }

    file.close();
}

void DataHandler::removeQuotes(std::string& value) {
    if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.size() - 2);
    }
}

void DataHandler::saveData(Manufacturers *manufacturers){
    std::ofstream file("data.csv");
    file << '"' << "appCurrency" << '"' << ","
         << '"' << Currency::currentCurrency << '"' << ","
         << '"' << Currency::currencySymbol << '"' << '\n';
    for (Seller* manufacturer : manufacturers->getManufacturers()) {
        qDebug() << "save username\n";
        file << '"' <<"appUsername" <<'"'<< ","
             << '"' << manufacturer->getUsername() << '"' << ","
             << '"' << manufacturer->getPassword() << '"' << ","
             << '"' << manufacturer->getName() << '"' << ","
             << '"' << manufacturer->getLastName() << '"' << ","
             << '"' << manufacturer->getNIN() << '"' << ","
             << '"' << manufacturer->getPhoneNumber() << '"' << ","
             << '"' << manufacturer->getManufactureName() << '"' << ","
             << '"' << manufacturer->getMID() << '"' << "\n";
        for (const Product& product : manufacturer->getProductsModel().getProducts()) {
            file << '"' << "appProduct" << '"' << ","
                 << '"' << product.getName() << '"' << ","
                 << '"' << product.getCategory() << '"' << ","
                 << '"' << product.getSku() << '"' << ","
                 << '"' << product.getBrand() << '"' << ","
                 << product.getStock() << ","
                 << product.getAvailable() << ","
                 << product.getPrice() << ","
                 << '"' << product.getUnit() << '"' << ","
                 << '"' << product.getDescription() << '"' << ","
                 << '"' << product.getAddedDate() << '"' << ","
                 << '"' << product.getExDate() << '"' << ","
                 << '"' << product.getAvailability() << '"' << "\n";
        }
        for (const Invoice& invoice : manufacturer->getPurchaseHistory().getInvoices()){
            file << '"' << "appInvoice" << '"' << ","
                 <<  invoice.getInvoiceNumber()  << ","
                 << '"' << invoice.getProviderName() << '"' << ","
                 << '"' << invoice.getCustomerName() << '"' << ","
                 << '"' << invoice.getProviderID()<< '"' << ","
                 << '"' << invoice.getCustomerID()<< '"' << ","
                 << invoice.getTotalAmount() << ","
                 << '"' << invoice.getDate() << '"' << ","
                 << invoice.getInvoiceItemModel().getItems().size() << "\n";
            qDebug() << "invoice provider name is " << invoice.getProviderName() << '\n';
            for (const InvoiceItem& item : invoice.getInvoiceItemModel().getItems()){
                file << '"' << "appInvoiceItem" << '"' << ","
                     << '"' << item.getName() << '"' << ","
                     << '"' << item.getCategory() << '"' << ","
                     << '"' << item.getSku() << '"' << ","
                     << '"' << item.getBrand() << '"' << ","
                     << item.getInventory() << ","
                     << item.getPrice() << ","
                     << '"' << item.getUnit() << '"' << ","
                     << '"' << item.getDescription() << '"' << ","
                     << '"' << item.getAddedDate() << '"' << ","
                     << '"' << item.getExDate() << '"' << "\n";
            }
        }

        for (const Invoice& invoice : manufacturer->getSoldHistory().getInvoices()){
            file << '"' << "appInvoice" << '"' << ","
                 <<  invoice.getInvoiceNumber()  << ","
                 << '"' << invoice.getProviderName() << '"' << ","
                 << '"' << invoice.getCustomerName() << '"' << ","
                 << '"' << invoice.getProviderID()<< '"' << ","
                 << '"' << invoice.getCustomerID()<< '"' << ","
                 << invoice.getTotalAmount() << ","
                 << '"' << invoice.getDate() << '"' << ","
                 << invoice.getInvoiceItemModel().getItems().size() << "\n";
            for (const InvoiceItem& item : invoice.getInvoiceItemModel().getItems()){
                file << '"' << "appInvoiceItem" << '"' << ","
                     << '"' << item.getName() << '"' << ","
                     << '"' << item.getCategory() << '"' << ","
                     << '"' << item.getSku() << '"' << ","
                     << '"' << item.getBrand() << '"' << ","
                     << item.getInventory() << ","
                     << item.getPrice() << ","
                     << '"' << item.getUnit() << '"' << ","
                     << '"' << item.getDescription() << '"' << ","
                     << '"' << item.getAddedDate() << '"' << ","
                     << '"' << item.getExDate() << '"' << "\n";
            }
        }
    }
    file.close();
}

void DataHandler::readCurrencyRates(CurrencyConverter &currencyModel){
    std::ifstream file("CurrencyExchangeRates.csv");
    std::string line;

    qDebug() << "In ReadCurrencyRates() func\n";

    if (file.is_open())
        qDebug() << "file is open\n";
    else {
        qDebug() << "file cannot be opened\n";
        return; // or handle the error appropriately
    }

    while (std::getline(file, line)){
        std::stringstream ss(line);

        std::string fromCurrency;
        std::getline(ss, fromCurrency, ',');
        removeQuotes(fromCurrency);

        std::string toCurrency;
        std::getline(ss, toCurrency, ',');
        removeQuotes(toCurrency);

        std::string rateStr;
        std::getline(ss, rateStr, ',');
        double rate = std::stod(rateStr);

        currencyModel.setConversionRate(fromCurrency, toCurrency, rate);
    }

    file.close();
}

void DataHandler::saveCurrencyRates(CurrencyConverter &currencyModel){
    std::ofstream file("CurrencyExchangeRates.csv");

    qDebug() << "In saveCurrencyRates() func\n";

    for (const std::pair<const std::string,double>& convertionRate : currencyModel.getConversionRates()){
        const std::string key = convertionRate.first;
        const double rate = convertionRate.second;

        const std::string base = key.substr(0,3);
        const std::string quote = key.substr(3,3);

        file << '"' << base << '"' << ","
             << '"' << quote << '"' << ","
             << rate << '\n';
    }
    file.close();
}

void DataHandler::printInvoice(const std::string& path,const Invoice &invoice){
    std::ofstream file(path);

    if (file.is_open()){
        file << "INVOICE\n";
        file << "INV-" << invoice.getInvoiceNumber() << '\n';
        file << "Date : " << invoice.getDate() << '\n';
        file << "Provider : " << invoice.getProviderName() << "," << "MID : " << invoice.getProviderID() << '\n';
        file << "Customer : " << invoice.getCustomerName() << "," << "MID : " << invoice.getCustomerID() << '\n';
        file << '\n';
        file << "ITEMS\n";

        std::vector<std::string> headers = {"SKU", "Name", "Brand", "Category", "Price", "Selected", "Unit", "Added Date", "Expiration Date", "Total"};
        // Write headers to the file
        for (const std::string& header : headers) {
            file << header << ",";
        }
        file << "\n";

        for (const InvoiceItem& item : invoice.getInvoiceItemModel().getItems()){
            file << item.getSku() << ",";
            file << item.getName() << ",";
            file << item.getBrand() << ",";
            file << item.getCategory() << ",";
            file << Currency::currencySymbol << item.getPrice() << ",";
            file << item.getInventory() << ",";
            file << item.getUnit() << ",";
            file << item.getAddedDate() << ",";
            file << item.getExDate() << ",";
            file << Currency::currencySymbol << item.getPrice()*item.getInventory() << "\n";
        }

        file << ",,,,,,,,," << "Total Amount: " << Currency::currencySymbol <<invoice.getTotalAmount() << "\n";
    }

    file.close();
}