#include "purchase_widget.h"
#include "ui_purchase_widget.h"

#include "add_to_invoice.h"
#include "product_information_window.h"
#include "currency.h"

purchase_widget::purchase_widget(Manufacturers* manufacturers, Seller* user ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchase_widget)
{
    qDebug() << "purchase widget constructure\n";
    ui->setupUi(this);
    m_manufacturers = manufacturers;
    m_user = user;

    ui->PB_brand->setEnabled(false);
    ui->PB_category->setEnabled(false);



    customizeListItems();

    setSearchComboBox();
    setProvidersComboBox();
    setTableColumns();
}

purchase_widget::~purchase_widget()
{
    qDebug() << "purchase widget destructure\n";
    delete ui;
}

void purchase_widget::customizeListItems(){
    class CustomItemDelegate_QListView : public QStyledItemDelegate {
    public:
        void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
            if (option.state & QStyle::State_Selected) {
                // Customize the selected item's appearance
                painter->save();

                // Draw a rounded border around the selected item
                QColor bgColor("#b3b7ff");        // Background color of the selected item
                int borderRadius = 8;             // Radius of the rounded corners
                int borderWidth = 4;              // Width of the border

                painter->setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing for smooth edges
                painter->setPen(Qt::NoPen);       // No outline pen for the background
                painter->setBrush(bgColor);       // Set the background color
                painter->drawRoundedRect(option.rect.adjusted(borderWidth, borderWidth, -borderWidth, -borderWidth), borderRadius, borderRadius);

                painter->restore();
            } else {
                // Customize the non-selected item's appearance
                painter->fillRect(option.rect, Qt::transparent);
            }

            // Draw the text centered within the item's rectangle
            painter->setPen(Qt::black);            // Set the text color to black
            painter->setFont(QFont("Calibri", 9, QFont::Weight::Medium)); // Set the font and size
            painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
        }
    };

    CustomItemDelegate_QListView* listDelegate = new CustomItemDelegate_QListView ;
    ui->LV_brandList->setItemDelegate(listDelegate);
    ui->LV_categoryList->setItemDelegate(listDelegate);
    ui->LV_brandList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->LV_categoryList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void purchase_widget::setSearchComboBox(){
    ui->CB_searchBy->addItem("Name");
    ui->CB_searchBy->addItem("SKU");
    ui->CB_searchBy->addItem("Category");
    ui->CB_searchBy->addItem("Brand");
    ui->CB_searchBy->addItem("Unit");
}

void purchase_widget::setProvidersComboBox(){
    qDebug() << "in setProvidersComboBox from purchase widget\n";
    ui->CB_providers->addItem("none");
    std::string userMID = m_user->getMID();
    for (const Seller* seller : m_manufacturers->getManufacturers())
        if(seller->getMID() != userMID)
            ui->CB_providers->addItem(QString::fromStdString(seller->getManufactureName()));
}

void purchase_widget::setTableColumns(){
    m_tableViewModel.setHorizontalHeaderItem(0 ,new QStandardItem("SKU"));
    m_tableViewModel.setHorizontalHeaderItem(1 ,new QStandardItem("Name"));
    m_tableViewModel.setHorizontalHeaderItem(2 ,new QStandardItem("Brand"));
    m_tableViewModel.setHorizontalHeaderItem(3 ,new QStandardItem("Category"));
    m_tableViewModel.setHorizontalHeaderItem(4 ,new QStandardItem("Price"));
    m_tableViewModel.setHorizontalHeaderItem(5 ,new QStandardItem("Inventory"));
    m_tableViewModel.setHorizontalHeaderItem(6 ,new QStandardItem("Selected"));
    m_tableViewModel.setHorizontalHeaderItem(7 ,new QStandardItem("Unit"));
    m_tableViewModel.setHorizontalHeaderItem(8 ,new QStandardItem("Added Date"));
    m_tableViewModel.setHorizontalHeaderItem(9 ,new QStandardItem("Expration Date"));

    ui->TV_items->setModel(&m_tableViewModel);
    ui->TV_items->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TV_items->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Set the size of each column
    const int numColumns = 9;
    const int columnWidth = 100;
    for (int column = 0; column < numColumns; ++column) {
        if (column == 4)
            ui->TV_items->setColumnWidth(column, 90);
        else if (column == 5 || column == 6 || column == 7)
            ui->TV_items->setColumnWidth(column, 70);
        else if (column == 8 || column == 9)
            ui->TV_items->setColumnWidth(column, 70);
        else
            ui->TV_items->setColumnWidth(column, columnWidth);
    }
}

void purchase_widget::updateTable(){
    qDebug() << "in updateTable of purchase widget\n";

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    if (m_provider){
        const std::vector<InvoiceItem> items = m_provider->getInvoiceItemsModel().getItems();
        int row = 0;
        for (const InvoiceItem& item : items){

            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
            qDebug() << item.getSku() << " from " << m_provider->getManufactureName() << " have added to list\n";
        }
    }
    else{
        qDebug() << "m_provider is null, clear table\n";
    }
}

void purchase_widget::updateFilterBrand(){
    m_brandFilterList.removeRows(0, m_brandFilterList.rowCount());

    if (m_provider){
        QStringList brands;
        for (const InvoiceItem& item : m_provider->getInvoiceItemsModel().getItems()){
            QString brand = QString::fromStdString(item.getBrand());
            if (!brands.contains(brand))
                brands << brand;
        }

        m_brandFilterList.setStringList(brands);

        ui->LV_brandList->setModel(&m_brandFilterList);
    }

    connect(ui->LV_brandList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &purchase_widget::onSelectionChangedBrands);

}

void purchase_widget::updateFilterCategory(){
    m_categoryFilterList.removeRows(0, m_categoryFilterList.rowCount());

    if (m_provider){
        QStringList categories;
        for (const InvoiceItem& item : m_provider->getInvoiceItemsModel().getItems()){
            QString category = QString::fromStdString(item.getCategory());
            if (!categories.contains(category))
                categories << category;
        }

        m_categoryFilterList.setStringList(categories);

        ui->LV_categoryList->setModel(&m_categoryFilterList);
    }

    connect(ui->LV_categoryList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &purchase_widget::onSelectionChangedCategories);
}

void purchase_widget::addItemToInvoice(int row){
    QModelIndex index = ui->TV_items->model()->index(row, 0);
    QString itemSKU = ui->TV_items->model()->data(index, Qt::DisplayRole).toString();

    InvoiceItem& item = m_provider->editInvoiceItems().editItem(itemSKU.toStdString());

    add_to_invoice* addWindow = new add_to_invoice(m_user,m_provider, &item,this);
    connect(addWindow, &add_to_invoice::dialogClosed, this,&purchase_widget::onAddToInvoiceDialogClosed);
    addWindow->setModal(true);
    addWindow->show();
}

void purchase_widget::search(const QString &text){
    QString by = ui->CB_searchBy->currentText();
    if (by == "Name")
        searchByName(text);
    else if (by == "SKU")
        searchBySKU(text);
    else if (by == "Category")
        searchByCategory(text);
    else if (by =="Brand")
        searchByBrand(text);
    else if (by == "Unit")
        searchByUnit(text);
}

void purchase_widget::searchByName(const QString &text){
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const InvoiceItem& item : items){
        if (QString::fromStdString(item.getName()).startsWith(text)){

            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void purchase_widget::searchBySKU(const QString &text)
{
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const InvoiceItem& item : items){
        if (QString::fromStdString(item.getSku()).startsWith(text)){

            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void purchase_widget::searchByCategory(const QString &text)
{
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const InvoiceItem& item : items){
        if (QString::fromStdString(item.getCategory()).startsWith(text)){

            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void purchase_widget::searchByBrand(const QString &text)
{
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const InvoiceItem& item : items){
        if (QString::fromStdString(item.getBrand()).startsWith(text)){

            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void purchase_widget::searchByUnit(const QString &text)
{
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const InvoiceItem& item : items){
        if (QString::fromStdString(item.getUnit()).startsWith(text)){

            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void purchase_widget::filterByBrand(const QString &brand){
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const InvoiceItem& item : items){
        if (item.getBrand() == brand.toStdString()){
            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }

    qDebug() << "filterByBrand func done\n ";
}

void purchase_widget::filterByCategory(const QString &category){
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const InvoiceItem& item : items){
        if (item.getCategory() == category.toStdString()){
            double selected = 0;
            if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
                if (m_user->getInvoice().getInvoiceItemModel().existence(item.getSku())){
                    selected = m_user->getInvoice().getInvoiceItemModel().getItem(item.getSku()).getInventory();
                }
            }

            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(selected)));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }

    qDebug() << "filterByCategory func done\n ";
}


void purchase_widget::on_CB_providers_currentTextChanged(const QString &arg1){
    qDebug() << "in currentTextChanged provider combo box in purchase widget arg1: " << arg1 << '\n' ;
    if (arg1 != "none"){
        m_provider = m_manufacturers->editSellerByManuName(arg1.toStdString());
        qDebug() << "m_provider is " << m_provider->getUsername() << "\n";
        updateTable();
        updateFilterBrand();
        updateFilterCategory();
        ui->LE_searchBar->clear();
    }
    else {
        m_provider = nullptr;
        updateTable();
        updateFilterBrand();
        updateFilterCategory();
    }


}


void purchase_widget::on_PB_addToInvoice_clicked(){
    QItemSelectionModel* selectionModel = ui->TV_items->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.empty()) {
        QModelIndex selectedIndex = selectedIndexes.first();
        int row = selectedIndex.row();
        addItemToInvoice(row);
    }

}

void purchase_widget::onAddToInvoiceDialogClosed(){
    updateTable();
}


void purchase_widget::on_LE_searchBar_textChanged(const QString &arg1){
    search(arg1);
}


void purchase_widget::on_PB_brand_clicked(){
    qDebug() << "PB_BrandFilter\n";

    QModelIndex selectedIndex = ui->LV_brandList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString selectedItemText = selectedIndex.data(Qt::DisplayRole).toString();
        qDebug() << "Selected item: " << selectedItemText;
        filterByBrand(selectedItemText);
        ui->LE_searchBar->setText("");
    }

    ui->LV_categoryList->clearSelection();
}


void purchase_widget::on_PB_category_clicked(){
    qDebug() << "PB_CategoryFilter\n";

    QModelIndex selectedIndex = ui->LV_categoryList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString selectedItemText = selectedIndex.data(Qt::DisplayRole).toString();
        qDebug() << "Selected item: " << selectedItemText;
        filterByCategory(selectedItemText);
        ui->LE_searchBar->setText("");
    }

    ui->LV_brandList->clearSelection();
}

void purchase_widget::onSelectionChangedBrands(const QItemSelection &selected, const QItemSelection &deselected){
    qDebug() << "onSelectionChangedBrands\n";
    if (!selected.isEmpty())
        ui->PB_brand->setEnabled(true);
    else
        ui->PB_brand->setEnabled(false);
}

void purchase_widget::onSelectionChangedCategories(const QItemSelection &selected, const QItemSelection &deselected){
    qDebug() << "onSelectionChangedCategories\n";
    if (!selected.isEmpty())
        ui->PB_category->setEnabled(true);
    else
        ui->PB_category->setEnabled(false);
}


void purchase_widget::on_TV_items_doubleClicked(const QModelIndex &index){
    const int row = index.row();
    std::string sku = m_tableViewModel.item(row, 0)->data(Qt::DisplayRole).toString().toStdString();
    const InvoiceItem& item = m_provider->getInvoiceItemsModel().getItem(sku);
    qDebug() << "item with sku : " << item.getSku() << " selected by double click TV_items\n";

    product_information_window* informationWindow = new product_information_window(m_user, &item, this);
    informationWindow->setModal(true);
    informationWindow->show();
}

