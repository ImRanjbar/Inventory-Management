
#include "datahandler.h"
#include "InvoiceNumbers.h"
#include "currency.h"
#include "CurrencyConverter.h"

DataHandler::DataHandler() = default;

void DataHandler::removeQuotes(std::string& value) {
    if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
        value = value.substr(1, value.size() - 2);
    }
}

void DataHandler::readCurrencyRates(CurrencyConverter &currencyModel){
    std::ifstream file("CurrencyExchangeRates.csv");
    std::string line;

    if (file.is_open())
        qDebug() << "file is open\n";
    else {
        qDebug() << "file cannot be opened\n";
        return;
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

void DataHandler::openDatabase(QSqlDatabase & data){
    data = QSqlDatabase::addDatabase("QSQLITE");
    data.setDatabaseName("dataBase.db");

    if (!data.open())
        qWarning() << "Couldn't open database!";
}

void DataHandler::closeDataBase(QSqlDatabase *data){
    data->close();
    delete data;
}

void DataHandler::readDataLogin(Manufacturers* manufacturers){
    QSqlDatabase data;
    openDatabase(data);

    QSqlQuery sellersQuery;
    sellersQuery.prepare("SELECT * FROM sellers");

    if (!sellersQuery.exec())
        qDebug() << "Query failed!";

    while (sellersQuery.next()){
        QString NIN = sellersQuery.value("nin").toString();

        QSqlQuery userQuery;
        userQuery.prepare("SELECT * FROM users WHERE nin = " + NIN);

        if (!userQuery.exec())
            qDebug() << "usersQuery failed!";

        userQuery.next();
        Seller* newSeller = new Seller;

        std::string username =userQuery.value("username").toString().toStdString();
        newSeller->setUsername(username);

        std::string password = userQuery.value("password").toString().toStdString();
        newSeller->setPassword(password);

        std::string name = userQuery.value("name").toString().toStdString();
        newSeller->setName(name);

        std::string lastName = userQuery.value("last_name").toString().toStdString();
        newSeller->setLastName(lastName);

        std::string nin = NIN.toStdString();
        newSeller->setNIN(nin);

        std::string phoneNumber = userQuery.value("phone_number").toString().toStdString();
        newSeller->setPhoneNumber(phoneNumber);

        std::string manufacturerName = sellersQuery.value("manufacturer_name").toString().toStdString();
        newSeller->setManufactureName(manufacturerName);

        std::string MID = sellersQuery.value("MID").toString().toStdString();
        newSeller->setMID(MID);

        manufacturers->addManufact(newSeller);
    }

    data.close();
}

void DataHandler::readDataHomeWindow(Manufacturers *manufacturers, Seller *user){
    Currency::currentCurrency = "USD";
    Currency::currencySymbol = "$";
    readProducts(user);
    readItems(manufacturers, user->getMID());
    readInvoices(*user);
    readInvoiceNumbers();
}

void DataHandler::readProducts(Seller *user){
    QSqlDatabase data;
    openDatabase(data);

    QSqlQuery query;

    QString MID = '"' + QString::fromStdString(user->getMID()) + '"';

    query.prepare("SELECT * FROM products WHERE owner_MID = " + MID);

    if (!query.exec())
        qDebug() << "Query for product failed!";

    while (query.next()){

        std::string name = query.value("name").toString().toStdString();
        std::string category = query.value("category").toString().toStdString();
        std::string SKU = query.value("sku").toString().toStdString();
        std::string brand = query.value("brand").toString().toStdString();
        double stock = query.value("stock_quantity").toDouble();
        double available = query.value("available_quantity").toDouble();
        double price = query.value("price").toDouble();
        std::string unit = query.value("unit").toString().toStdString();
        std::string description = query.value("description").toString().toStdString();
        std::string addDate = query.value("added_date").toString().toStdString();
        std::string exDate = query.value("ex_date").toString().toStdString();

        bool availability = ([available](){ return available > 0; })();

        Product newProduct(name, category, SKU, brand, stock, available, price, unit, description, addDate, exDate, availability);
        user->addProduct(newProduct);
    }

    data.close();
}

void DataHandler::addUser(Seller *newUser){

    QSqlDatabase data;
    openDatabase(data);

    QString username = QString::fromStdString(newUser->getUsername());
    QString password = QString::fromStdString(newUser->getPassword());
    QString name = QString::fromStdString(newUser->getName());
    QString lastName = QString::fromStdString(newUser->getLastName());
    QString nin = QString::fromStdString(newUser->getNIN());
    QString phoneNumber = QString::fromStdString(newUser->getPhoneNumber());

    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256).toHex();

    // set user password again
    newUser->setPassword(hashedPassword.toStdString());

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, name, last_name, nin, phone_number) "
                  "VALUES (:username, :password, :name, :last_name, :nin, :phone_number)");

    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);
    query.bindValue(":name", name);
    query.bindValue(":last_name", lastName);
    query.bindValue(":nin", nin);
    query.bindValue(":phone_number", phoneNumber);

    if (!query.exec()) {
        qDebug() << "Failed to insert user into the database";
    }

    int userId = query.lastInsertId().toInt();

    query.prepare("INSERT INTO sellers (id, nin, MID, manufacturer_name) "
                  "VALUES (:id, :nin, :mid, :manufacturer_name)");
    query.bindValue(":id", userId);
    query.bindValue(":nin", QString::fromStdString(newUser->getNIN()));
    query.bindValue(":mid", QString::fromStdString(newUser->getMID()));
    query.bindValue(":manufacturer_name", QString::fromStdString(newUser->getManufactureName()));

    if (!query.exec()) {
        qDebug() << "Failed to insert seller into the database";
    }

    data.close();
}

void DataHandler::addProduct(Product *newProduct, const std::string &MID) {
    QSqlDatabase data;
    openDatabase(data);

    QString ownerMID = QString::fromStdString(MID);
    QString name = QString::fromStdString(newProduct->getName());
    QString category = QString::fromStdString(newProduct->getCategory());
    QString sku = QString::fromStdString(newProduct->getSku());
    QString brand = QString::fromStdString(newProduct->getBrand());
    double stockQuantity = newProduct->getStock();
    double availableQuantity = newProduct->getAvailable();

    double price = newProduct->getPrice();
    if (Currency::currentCurrency != "USD"){
        CurrencyConverter currency;
        readCurrencyRates(currency);
        price = currency.convert(Currency::currentCurrency, "USD", price);
    }

    QString unit = QString::fromStdString(newProduct->getUnit());
    QString description = QString::fromStdString(newProduct->getDescription());
    QString addedDate = QString::fromStdString(newProduct->getAddedDate());
    QString expiryDate = QString::fromStdString(newProduct->getExDate());

    QSqlQuery query;
    query.prepare("INSERT INTO products (owner_MID, name, category, sku, brand, stock_quantity, "
                  "available_quantity, price, unit, description, added_date, ex_date) "
                  "VALUES (:owner_MID, :name, :category, :sku, :brand, :stock_quantity, "
                  ":available_quantity, :price, :unit, :description, :added_date, :ex_date)");
    query.bindValue(":owner_MID", ownerMID);
    query.bindValue(":name", name);
    query.bindValue(":category", category);
    query.bindValue(":sku", sku);
    query.bindValue(":brand", brand);
    query.bindValue(":stock_quantity", stockQuantity);
    query.bindValue(":available_quantity", availableQuantity);
    query.bindValue(":price", price);
    query.bindValue(":unit", unit);
    query.bindValue(":description", description);
    query.bindValue(":added_date", addedDate);
    query.bindValue(":ex_date", expiryDate);

    if (!query.exec()) {
        qDebug() << "Failed to insert product into the database";
        return;
    }

    qDebug() << "Product inserted successfully";

    data.close();
}

void DataHandler::updateProduct(const std::string& productSKU, const Product &newProduct, const std::string& MID){
    QSqlDatabase data;
    openDatabase(data);

    const QString newName = QString::fromStdString(newProduct.getName());
    const QString newCategory = QString::fromStdString(newProduct.getCategory());
    const QString newSKU = QString::fromStdString(newProduct.getSku());
    const QString newBrand = QString::fromStdString(newProduct.getBrand());
    const double newStock = newProduct.getStock();
    const double newAvailable = newProduct.getAvailable();

    double newPrice = newProduct.getPrice();
    if (Currency::currentCurrency != "USD"){
        CurrencyConverter currency;
        readCurrencyRates(currency);
        newPrice = currency.convert(Currency::currentCurrency, "USD", newPrice);
    }

    const QString newUnit = QString::fromStdString(newProduct.getUnit());
    const QString newDescription = QString::fromStdString(newProduct.getDescription());
    const QString newAddDate = QString::fromStdString(newProduct.getAddedDate());
    const QString newExDate = QString::fromStdString(newProduct.getExDate());

    QSqlQuery query;
    query.prepare("UPDATE products SET name = :newName, category = :newCategory, sku = :newSKU, brand = :newBrand "
                  ", stock_quantity = :newStock, available_quantity = :newAvailable, price = :newPrice, unit = :newUnit "
                  ", description = :newDescription, added_date = :newAddDate, ex_date = :newExDate "
                  "WHERE owner_MID = :ownerMID AND sku = :sku");
    query.bindValue(":newName",newName);
    query.bindValue(":newCategory", newCategory);
    query.bindValue(":newSKU", newSKU);
    query.bindValue(":newBrand", newBrand);
    query.bindValue(":newStock", newStock);
    query.bindValue(":newAvailable", newAvailable);
    query.bindValue(":newPrice", newPrice);
    query.bindValue(":newUnit", newUnit);
    query.bindValue(":newDescription", newDescription);
    query.bindValue(":newAddDate", newAddDate);
    query.bindValue(":newExDate", newExDate);
    query.bindValue(":ownerMID",QString::fromStdString(MID));
    query.bindValue(":sku",QString::fromStdString(productSKU));

    if (!query.exec()) {
        qDebug() << "Product update Failed for database";
    }

    data.close();
}

void DataHandler::removeProduct(const std::string &productSKU, const std::string ownerMID){
    QSqlDatabase data;
    openDatabase(data);

    QSqlQuery query;
    QString SKU = '"' + QString::fromStdString(productSKU) + '"';
    QString MID = '"' + QString::fromStdString(ownerMID) + '"';
    query.prepare("DELETE FROM products WHERE owner_MID = " + MID + " AND sku = " + SKU);

    if (!query.exec())
        qDebug() << "Failed to delete product from database";

    data.close();
}

void DataHandler::readItems(Manufacturers* manufacturers, const std::string& userMID){
    QSqlDatabase data;
    openDatabase(data);

    for (Seller* manufacturer : manufacturers->getManufacturers()){
        QString MID = QString::fromStdString(manufacturer->getMID());

        if (MID == QString::fromStdString(userMID))
            continue;

        QSqlQuery query;
        MID = '"' + MID + '"';
        query.prepare("SELECT * FROM products WHERE owner_MID = " + MID + " AND available_quantity > 0");

        if (!query.exec()) {
            qDebug() << "Query Failed";
            return;
        }

        while (query.next()){
            const std::string name = query.value("name").toString().toStdString();
            const std::string category = query.value("category").toString().toStdString();
            const std::string sku = query.value("sku").toString().toStdString();
            const std::string brand = query.value("brand").toString().toStdString();
            const double stockQuantity = query.value("stock_quantity").toDouble();
            const double availableQuantity = query.value("available_quantity").toDouble();
            const double price = query.value("price").toDouble();
            const std::string unit = query.value("unit").toString().toStdString();
            const std::string description = query.value("description").toString().toStdString();
            const std::string addDate = query.value("added_date").toString().toStdString();
            const std::string exDate = query.value("ex_date").toString().toStdString();

            Product newProduct(name, category, sku, brand, stockQuantity, availableQuantity, price, unit, description, addDate, exDate, 1);
            manufacturer->addProduct(newProduct);
        }
    }

    data.close();
}

void DataHandler::readInvoices(Seller& user){
    QSqlDatabase data;
    openDatabase(data);

    QString MID = '"' + QString::fromStdString(user.getMID()) + '"';

    // As provider
    QSqlQuery providerQuery;

    providerQuery.prepare("SELECT * FROM invoices WHERE provider_id = " + MID);
    if (!providerQuery.exec())
        qDebug() << "ProviderQuery Failed";

    while (providerQuery.next()){
        const int invoiceNumber = providerQuery.value("invoice_number").toInt();
        const std::string providerID = user.getMID();
        const std::string customerID = providerQuery.value("customer_id").toString().toStdString();
        const std::string providerName = providerQuery.value("provider_name").toString().toStdString();
        const std::string customerName = providerQuery.value("customer_name").toString().toStdString();
        const double amount = providerQuery.value("amount").toDouble();
        const std::string date = providerQuery.value("date").toString().toStdString();

        Invoice newInvoice(invoiceNumber, providerID, customerID, providerName, customerName, amount, date);
        user.editSoldModel().addInvoice(newInvoice);
    }

    // As customer
    QSqlQuery customerQuery;

    customerQuery.prepare("SELECT * FROM invoices WHERE customer_id = " + MID);
    if (!customerQuery.exec())
        qDebug() << "CustomerQuery Failed";

    while(customerQuery.next()){
        const int invoiceNumber = customerQuery.value("invoice_number").toInt();
        const std::string providerID = customerQuery.value("provider_id").toString().toStdString();
        const std::string customerID = user.getMID();
        const std::string providerName = customerQuery.value("provider_name").toString().toStdString();
        const std::string customerName = user.getManufactureName();
        const double amount = customerQuery.value("amount").toDouble();
        const std::string date = customerQuery.value("date").toString().toStdString();

        Invoice newInvoice(invoiceNumber, providerID, customerID, providerName, customerName, amount, date);
        user.editPurchaseModel().addInvoice(newInvoice);
    }

    data.close();
}

void DataHandler::readInvoiceItems(Invoice &invoice){
    QSqlDatabase data;
    openDatabase(data);

    const QString invoiceNumber = QString::number(invoice.getInvoiceNumber());

    QSqlQuery query;
    query.prepare("SELECT * FROM invoice_items WHERE invoice_id = " + invoiceNumber);

    if (!query.exec())
        qDebug() << "Read invoice items Failed";

    double conversionRate = 1.0;
    if (Currency::currentCurrency != "USD"){
        CurrencyConverter currency;
        readCurrencyRates(currency);
        conversionRate = currency.getRate("USD", Currency::currentCurrency);
    }

    while (query.next()){
        std::string name = query.value("name").toString().toStdString();
        std::string category = query.value("category").toString().toStdString();
        std::string sku = query.value("sku").toString().toStdString();
        std::string brand = query.value("brand").toString().toStdString();
        double inventory = query.value("inventory").toDouble();
        double price = query.value("price").toDouble();
        price *= conversionRate;
        std::string unit = query.value("unit").toString().toStdString();
        std::string description = query.value("description").toString().toStdString();
        std::string addDate = query.value("added_date").toString().toStdString();
        std::string exDate = query.value("ex_date").toString().toStdString();

        InvoiceItem newItem(name, category, sku, brand, inventory, price, unit, description, addDate, exDate);
        invoice.addItem(newItem);
    }

    data.close();
}

void DataHandler::addInvoice(const Invoice &invoice){
    QSqlDatabase data;
    openDatabase(data);

    const int invoiceNumber = invoice.getInvoiceNumber();
    const QString providerID = QString::fromStdString(invoice.getProviderID());
    const QString customerID = QString::fromStdString(invoice.getCustomerID());
    const QString providerName = QString::fromStdString(invoice.getProviderName());
    const QString customerName = QString::fromStdString(invoice.getCustomerName());
    double amount = invoice.getTotalAmount();
    if (Currency::currentCurrency != "USD"){
        CurrencyConverter currency;
        readCurrencyRates(currency);
        amount = currency.convert(Currency::currentCurrency, "USD", amount);
    }
    const QString date = QString::fromStdString(invoice.getDate());

    QSqlQuery query;

    query.prepare("INSERT INTO invoices (invoice_number, provider_id, customer_id, provider_name, customer_name, amount, date)"
                  "VALUES(:invoice_number, :provider_id, :customer_id, :provider_name, :customer_name, :amount, :date)");
    query.bindValue(":invoice_number", invoiceNumber);
    query.bindValue(":provider_id", providerID);
    query.bindValue(":customer_id", customerID);
    query.bindValue(":provider_name", providerName);
    query.bindValue(":customer_name", customerName);
    query.bindValue(":amount", amount);
    query.bindValue(":date", date);

    if (!query.exec())
        qDebug() << "Failed to insert invoice";

    addInvoiceItems(invoice);

    data.close();
}

void DataHandler::updateCustomerProducts(Seller& customer, const Invoice& invoice){
    QSqlDatabase data;
    openDatabase(data);

    QSqlQuery query;

    CurrencyConverter currency;
    readCurrencyRates(currency);

    for (const InvoiceItem& item : invoice.getInvoiceItemModel().getItems()){
        if (customer.editProducts().existence(item.getSku())){

            const double newStock  = customer.getProductsModel().getProduct(item.getSku()).getStock() + item.getInventory();
            query.prepare("UPDATE products SET stock_quantity = :newStock WHERE owner_MID = :ownerMID AND sku = :sku");
            query.bindValue(":newStock", newStock);
            query.bindValue(":ownerMID", QString::fromStdString(customer.getMID()));
            query.bindValue(":sku", QString::fromStdString(item.getSku()));

            if (!query.exec())
                qDebug() << "Failed to update Customer Product";
        }
        else {

            query.prepare("INSERT INTO products (owner_MID, name, category, sku, brand, stock_quantity, "
                          "available_quantity, price, unit, description, added_date, ex_date) "
                          "VALUES (:owner_MID, :name, :category, :sku, :brand, :stock_quantity, "
                          ":available_quantity, :price, :unit, :description, :added_date, :ex_date)");
            query.bindValue(":owner_MID", QString::fromStdString(customer.getMID()));
            query.bindValue(":name", QString::fromStdString(item.getName()));
            query.bindValue(":category", QString::fromStdString(item.getCategory()));
            query.bindValue(":sku", QString::fromStdString(item.getSku()));
            query.bindValue(":brand", QString::fromStdString(item.getBrand()));
            query.bindValue(":stock_quantity", item.getInventory());
            query.bindValue(":available_quantity", 0);

            double price = item.getPrice();
            if (Currency::currentCurrency != "USD"){
                price = currency.convert(Currency::currentCurrency, "USD", price);
            }

            query.bindValue(":price", price);
            query.bindValue(":unit", QString::fromStdString(item.getUnit()));
            query.bindValue(":description", QString::fromStdString(item.getDescription()));
            query.bindValue(":added_date", QString::fromStdString(item.getAddedDate()));
            query.bindValue(":ex_date", QString::fromStdString(item.getExDate()));

            if (!query.exec())
                qDebug() << "Failed to insert product into the database for customer";
        }
    }

    data.close();
}

void DataHandler::updateProviderProducts(Seller& provider, const Invoice& invoice){
    QSqlDatabase data;
    openDatabase(data);

    QSqlQuery query;
    query.prepare("UPDATE products SET available_quantity = :newAvailable WHERE owner_MID = :ownerMID AND sku = :sku");

    for (const InvoiceItem& item : invoice.getInvoiceItemModel().getItems()){
        const double newAvailable = provider.getProductsModel().getProduct(item.getSku()).getAvailable() - item.getInventory();
        query.bindValue(":newAvailable", newAvailable);
        query.bindValue(":ownerMID", QString::fromStdString(provider.getMID()));
        query.bindValue(":sku", QString::fromStdString(item.getSku()));

        if (!query.exec())
            qDebug() << "Failed to update product available quantity in database for provider";
    }

    data.close();
}

void DataHandler::addInvoiceItems(const Invoice &invoice){

    const  double invoiceNumber = invoice.getInvoiceNumber();
    const QString providerID = QString::fromStdString(invoice.getProviderID());
    const QString customerID = QString::fromStdString(invoice.getCustomerID());

    QSqlQuery query;
    query.prepare("INSERT INTO invoice_items (invoice_id, provider_id, customer_id, name, category, sku, brand, inventory, price, "
                  "unit, description, added_date, ex_date) "
                  "VALUES (:invoice_id, :provider_id, :customer_id,:name, :category, :sku, :brand, :inventory, :price, "
                  ":unit, :description, :added_date, :ex_date)");
    query.bindValue(":invoice_id", invoiceNumber);
    query.bindValue(":provider_id", providerID);
    query.bindValue(":customer_id", customerID);

    double conversionRate = 1.0;
    if (Currency::currentCurrency != "USD"){
        CurrencyConverter currency;
        readCurrencyRates(currency);
        conversionRate = currency.getRate(Currency::currentCurrency, "USD");
    }

    for (const InvoiceItem& item : invoice.getInvoiceItemModel().getItems()){
        const QString name = QString::fromStdString(item.getName());
        const QString category = QString::fromStdString(item.getCategory());
        const QString SKU = QString::fromStdString(item.getSku());
        const QString brand = QString::fromStdString(item.getBrand());
        const double inventory = item.getInventory();
        double price = item.getPrice();
        price *= conversionRate;
        const QString unit = QString::fromStdString(item.getUnit());
        const QString description = QString::fromStdString(item.getDescription());
        const QString addDate = QString::fromStdString(item.getAddedDate());
        const QString exDate = QString::fromStdString(item.getExDate());

        query.bindValue(":name", name);
        query.bindValue(":category", category);
        query.bindValue(":sku", SKU);
        query.bindValue(":brand", brand);
        query.bindValue(":inventory", inventory);
        query.bindValue(":price", price);
        query.bindValue(":unit", unit);
        query.bindValue(":description", description);
        query.bindValue(":added_date", addDate);
        query.bindValue(":ex_date", exDate);

        if (!query.exec())
            qDebug() << "Failed to add items to invoice";
    }
}

void DataHandler::readInvoiceNumbers(){
    QSqlDatabase data;
    openDatabase(data);

    QSqlQuery query;
    query.prepare("SELECT invoice_number FROM invoices");
    if (!query.exec())
        qDebug() << "readInvoiceNumbers Failed";

    while(query.next()){
        const int invoiceNumber = query.value(0).toInt();
        InvoiceNumbers::invoiceNumbers.insert(invoiceNumber);
    }

    data.close();
}
