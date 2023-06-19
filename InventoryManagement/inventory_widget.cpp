#include "inventory_widget.h"
#include "ui_inventory_widget.h"
#include "add_product_window.h"
#include <QStringListModel>
#include <QMessageBox>
#include <QHeaderView>
#include "edit_product_window.h"

inventory_widget::inventory_widget(Manufacturers* manufacturers, Seller* user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inventory_widget)
{
    qDebug() << "inventory_widget constructure\n";
    ui->setupUi(this);

    customizeListItems();

    m_manufacturers = manufacturers;
    m_user = user;

    setSearchComboBox();
    setTableColumns();

    updateTable();

    updateFilterBrand();
    updateFilterCategory();

    connect(ui->LV_brandList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &inventory_widget::onSelectionChangedBrands);
    connect(ui->LV_categoryList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &inventory_widget::onSelectionChangedCategories);

    connect(ui->LE_search, &QLineEdit::textChanged, this, &inventory_widget::onTextChanged);



    qDebug() << "inventory_widget constructure done\n";
}

inventory_widget::~inventory_widget()
{
    qDebug() << "inventory_widget destructure\n";
    delete ui;
}

void inventory_widget::customizeListItems(){
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

void inventory_widget::setSearchComboBox(){
    ui->CB_searchBy->addItem("Name");
    ui->CB_searchBy->addItem("SKU");
    ui->CB_searchBy->addItem("Category");
    ui->CB_searchBy->addItem("Brand");
    ui->CB_searchBy->addItem("Unit");
}

void inventory_widget::setTableColumns(){
    m_tableViewModel.setHorizontalHeaderItem(0 ,new QStandardItem("SKU"));
    m_tableViewModel.setHorizontalHeaderItem(1 ,new QStandardItem("Name"));
    m_tableViewModel.setHorizontalHeaderItem(2 ,new QStandardItem("Brand"));
    m_tableViewModel.setHorizontalHeaderItem(3 ,new QStandardItem("Category"));
    m_tableViewModel.setHorizontalHeaderItem(4 ,new QStandardItem("Price"));
    m_tableViewModel.setHorizontalHeaderItem(5 ,new QStandardItem("In Stock"));
    m_tableViewModel.setHorizontalHeaderItem(6 ,new QStandardItem("Available"));
    m_tableViewModel.setHorizontalHeaderItem(7 ,new QStandardItem("Unit"));
    m_tableViewModel.setHorizontalHeaderItem(8 ,new QStandardItem("Added Date"));
    m_tableViewModel.setHorizontalHeaderItem(9 ,new QStandardItem("Expration Date"));

    ui->TV_products->setModel(&m_tableViewModel);
    ui->TV_products->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    ui->TV_products->setCursor(Qt::PointingHandCursor);
    ui->TV_products->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Set the size of each column
    const int numColumns = 9;
    const int columnWidth = 100;
    for (int column = 0; column < numColumns; ++column) {
        if (column == 4)
            ui->TV_products->setColumnWidth(column, 70);
        else if (column == 5 || column == 6 || column == 7)
            ui->TV_products->setColumnWidth(column, 70);
        else if (column == 8 || column == 9)
            ui->TV_products->setColumnWidth(column, 80);
        else
            ui->TV_products->setColumnWidth(column, columnWidth);
    }

    ui->TV_products->horizontalHeader()->setSectionsClickable(true);
    connect(ui->TV_products->horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, &inventory_widget::handleHeaderDoubleClicked);
    connect(ui->TV_products->horizontalHeader(), &QHeaderView::sectionClicked, this, &inventory_widget::handleHeaderClicked);

}

void inventory_widget::updateTable() {
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        QStandardItem* SKU = new QStandardItem(QString::fromStdString(product.getSku()));
        SKU->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        m_tableViewModel.setItem(row,0 ,SKU);
        m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
        m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
        m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
        m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
        m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
        m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
        m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
        m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
        m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
        row++;
    }

    ui->LE_search->setText("");
    qDebug() << "updateTable func done\n ";
}

void inventory_widget::updateFilterBrand(){
    QStringList brands;
    for (const Product& product : m_user->getProductsModel().getProducts()){
        qDebug() << product.getBrand() << "have added into filter brand listView\n";
        QString brand = QString::fromStdString(product.getBrand());
        if (!brands.contains(brand))
            brands << brand;
    }
    qDebug() << brands;

    m_brandFilterList.setStringList(brands);

    ui->LV_brandList->setModel(&m_brandFilterList);

}

void inventory_widget::updateFilterCategory(){
    QStringList categories;
    for (const Product& product : m_user->getProductsModel().getProducts()){
        qDebug() << product.getCategory() << "have added into filter category listView\n";
        QString category = QString::fromStdString(product.getCategory());
        if (!categories.contains(category))
            categories << category;
    }

    m_categoryFilterList.setStringList(categories);

    ui->LV_categoryList->setModel(&m_categoryFilterList);


    qDebug() << "updateFilterCategory func done suc\n";
}

void inventory_widget::removeProduct(int row){
    QModelIndex index = ui->TV_products->model()->index(row, 0);
    QString productSKU = ui->TV_products->model()->data(index, Qt::DisplayRole).toString();

    QMessageBox* messageBox = new QMessageBox(this);

    messageBox->setText("Are you sure you want to remove the product with SKU code " + productSKU +" from your inventory?");
    messageBox->setWindowTitle("Remove Product");

    messageBox->addButton(QMessageBox::Yes);
    messageBox->addButton(QMessageBox::No);

    int buttonClicked = messageBox->exec();

    if (buttonClicked == QMessageBox::Yes)
        m_user->removerProduct(productSKU.toStdString());
    else
        return;
}

void inventory_widget::updateTableBrand(const std::string_view brand){
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        if (product.getBrand() == brand){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void inventory_widget::updateTableCategory(const std::string_view category){
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        if (product.getCategory() == category){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";

}

void inventory_widget::search(const QString &text){
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

void inventory_widget::searchByName(const QString &text){
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        if (QString::fromStdString(product.getName()).startsWith(text)){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void inventory_widget::searchBySKU(const QString &text)
{
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        if (QString::fromStdString(product.getSku()).startsWith(text)){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void inventory_widget::searchByCategory(const QString &text)
{
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        if (QString::fromStdString(product.getCategory()).startsWith(text)){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void inventory_widget::searchByBrand(const QString &text)
{
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        if (QString::fromStdString(product.getBrand()).startsWith(text)){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}

void inventory_widget::searchByUnit(const QString &text)
{
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;
    for (const Product& product : products){
        if (QString::fromStdString(product.getUnit()).startsWith(text)){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
    qDebug() << "updateTable func done\n ";
}


void inventory_widget::on_TV_products_doubleClicked(const QModelIndex &index)
{
    qDebug() << index << '\n';
    int row = index.row();
    std::string sku = m_tableViewModel.item(row,0)->data(Qt::DisplayRole).toString().toStdString();
    Product& product = m_user->editProducts().editProduct(sku);
    edit_product_window* editProductWindow = new edit_product_window(m_user, &product, this);
    editProductWindow->setModal(true);
    editProductWindow->show();
    connect(editProductWindow, &edit_product_window::windowClosed, this, &inventory_widget::onDialogClosed);
}


void inventory_widget::on_TV_products_activated(const QModelIndex &index)
{
    qDebug() << index << '\n';
}


void inventory_widget::on_PB_add_clicked(){
    add_product_window* addProductWindow = new add_product_window(m_user, this);
    connect(addProductWindow, &add_product_window::dialogClosed, this, &inventory_widget::onDialogClosed);
    addProductWindow->setModal(true);
    addProductWindow->show();
}

void inventory_widget::onDialogClosed(){
    updateFilterBrand();
    updateFilterCategory();
    updateTable();
}


void inventory_widget::on_PB_remove_clicked()
{
    QItemSelectionModel* selectionModel = ui->TV_products->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.empty()) {
        QModelIndex selectedIndex = selectedIndexes.first();
        int row = selectedIndex.row();
        removeProduct(row);
        qDebug() << "after removeProduct\n";
        updateFilterBrand();
        updateFilterCategory();
        updateTable();
    }
    qDebug() << "on_PB_remove_clicked func done\n";
}


void inventory_widget::on_PB_brandFilter_clicked(){
    qDebug() << "PB_BrandFilter\n";

    // Get the currently selected index
    QModelIndex selectedIndex = ui->LV_brandList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString selectedItemText = selectedIndex.data(Qt::DisplayRole).toString();
        qDebug() << "Selected item: " << selectedItemText;
        updateTableBrand(selectedItemText.toStdString());
        ui->LE_search->setText("");
    }

    ui->LV_categoryList->clearSelection();
}

void inventory_widget::onSelectionChangedBrands(const QItemSelection& selected, const QItemSelection& deselected){
    qDebug() << "on inventory_widget::onSelectionChangedBrands \n";
    // Check if there is at least one selected item
    if (!selected.isEmpty()) {
        // Enable the QPushButton
        ui->PB_brandFilter->setEnabled(true);
    } else {
        // No selected items, disable the QPushButton
        ui->PB_brandFilter->setEnabled(false);
    }
}

void inventory_widget::onSelectionChangedCategories(const QItemSelection &selected, const QItemSelection &deselected){
    qDebug() << "on inventory_widget::onSelectionChangedCategories \n";
    // Check if there is at least one selected item
    if (!selected.isEmpty()) {
        // Enable the QPushButton
        ui->PB_categoryFilter->setEnabled(true);
    } else {
        // No selected items, disable the QPushButton
        ui->PB_categoryFilter->setEnabled(false);
    }
}


void inventory_widget::on_PB_categoryFilter_clicked(){
    qDebug() << "PB_CategoryFilter\n";

    // Get the currently selected index
    QModelIndex selectedIndex = ui->LV_categoryList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString selectedItemText = selectedIndex.data(Qt::DisplayRole).toString();
        qDebug() << "Selected item: " << selectedItemText;
        updateTableCategory(selectedItemText.toStdString());
        ui->LE_search->setText("");
    }

    ui->LV_brandList->clearSelection();
}

void inventory_widget::handleHeaderDoubleClicked(int logicalIndex){
    qDebug() << "handleHeaderDoubleClicked\n";

    switch (logicalIndex){
    case 0:
        m_user->editProducts().sortBySKU();
        break;
    case 1:
        m_user->editProducts().sortByName();
        break;
    case 2:
        m_user->editProducts().sortByBrand();
        break;
    case 3:
        m_user->editProducts().sortByCategory();
        break;
    case 4:
        m_user->editProducts().sortByPrice();
        break;
    case 5:
        m_user->editProducts().sortByStock();
        break;
    case 6:
        m_user->editProducts().sortByAvailable();
        break;
    case 7:
        m_user->editProducts().sortByAddDate();
        break;
    case 8:
        m_user->editProducts().sortByExDate();
        break;
    }
    updateTable();
}

void inventory_widget::handleHeaderClicked(int logicalIndex){
    qDebug() << "handleHeaderClicked\n";

    switch (logicalIndex){
    case 0:
        m_user->editProducts().sortBySKUdes();
        break;
    case 1:
        m_user->editProducts().sortByNameDes();
        break;
    case 2:
        m_user->editProducts().sortByBrandDes();
        break;
    case 3:
        m_user->editProducts().sortByCategoryDes();
        break;
    case 4:
        m_user->editProducts().sortByPriceDes();
        break;
    case 5:
        m_user->editProducts().sortByStockDes();
        break;
    case 6:
        m_user->editProducts().sortByAvailableDes();
        break;
    case 7:
        m_user->editProducts().sortByAddDateDes();
        break;
    case 8:
        m_user->editProducts().sortByExDateDes();
        break;
    }
    updateTable();
}

void inventory_widget::onTextChanged(const QString &text){
    qDebug() << "LE_search text : " << text << "\n";
    search(text);

}

