#include "inventory_widget.h"
#include "ui_inventory_widget.h"
#include "add_product_window.h"
#include <QStringListModel>
#include <QMessageBox>
#include <QHeaderView>
#include "edit_product_window.h"
#include "currency.h"
#include "datahandler.h"

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
    initializeTableView();

    updateTable();

    updateFilterBrand();
    updateFilterCategory();

    // Connect the selectionChanged signal of the brand list view's selection model
    // to the onSelectionChangedBrands slot of the purchase_widget
    connect(ui->LV_brandList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &inventory_widget::onSelectionChangedBrands);

    // Connect the selectionChanged signal of the category list view's selection model
    // to the onSelectionChangedCategories slot of the purchase_widget
    connect(ui->LV_categoryList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &inventory_widget::onSelectionChangedCategories);

    connect(ui->LE_search, &QLineEdit::textChanged, this, &inventory_widget::onTextChanged);
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
                QColor bgColor(179,183,255);        // Background color of the selected item
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

void inventory_widget::initializeTableView(){
    // Custom delegate for center-aligned text
    class CenterAlignmentDelegate : public QStyledItemDelegate {
    public:
        explicit CenterAlignmentDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

        void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
            QStyleOptionViewItem centeredOption = option;
            centeredOption.displayAlignment = Qt::AlignCenter;

            QStyledItemDelegate::paint(painter, centeredOption, index);
        }
    };

    // Create and set the custom delegate for center alignment
    ui->TV_products->setItemDelegate(new CenterAlignmentDelegate(ui->TV_products));

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
    ui->TV_products->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TV_products->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Set the size of each column
    const int numColumns = 9;
    const int defaultColumnWidth = 100;
    for (int column = 0; column < numColumns; ++column) {
        if (column == 4)    // for Price column
            ui->TV_products->setColumnWidth(column, 90);
        else if (column == 5 || column == 6 || column == 7 || column == 8 || column == 9)
            ui->TV_products->setColumnWidth(column, 70);
        else
            ui->TV_products->setColumnWidth(column, defaultColumnWidth);
    }

    ui->TV_products->horizontalHeader()->setSectionsClickable(true);

    // Connect the table header signals to the respective slots for sorting table elements
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
        m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(product.getPrice(), 'f' , 2)));
        m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
        m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
        m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getUnit())));
        m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
        m_tableViewModel.setItem(row,9 ,new QStandardItem(QString::fromStdString(product.getExDate())));
        row++;
    }

    ui->LE_search->setText("");
}

void inventory_widget::updateFilterBrand(){
    QStringList brands;
    for (const Product& product : m_user->getProductsModel().getProducts()){
        QString brand = QString::fromStdString(product.getBrand());
        if (!brands.contains(brand))
            brands << brand;
    }

    m_brandFilterList.setStringList(brands);
    ui->LV_brandList->setModel(&m_brandFilterList);
}

void inventory_widget::updateFilterCategory(){
    QStringList categories;
    for (const Product& product : m_user->getProductsModel().getProducts()){
        QString category = QString::fromStdString(product.getCategory());
        if (!categories.contains(category))
            categories << category;
    }

    m_categoryFilterList.setStringList(categories);
    ui->LV_categoryList->setModel(&m_categoryFilterList);
}

void inventory_widget::removeProduct(int row){
    // Get the index of the product SKU in the first column of the table view
    QModelIndex index = ui->TV_products->model()->index(row, 0);
    QString productSKU = ui->TV_products->model()->data(index, Qt::DisplayRole).toString();

    // Create a message box to confirm the removal of the product
    QMessageBox* messageBox = new QMessageBox(this);
    messageBox->setText("Are you sure you want to remove the product with SKU code " + productSKU +" from your inventory?");
    messageBox->setWindowTitle("Remove Product");
    messageBox->addButton(QMessageBox::Yes);
    messageBox->addButton(QMessageBox::No);

    // Display the message box and wait for the user's response
    int buttonClicked = messageBox->exec();

    // Check if the user clicked "Yes"
    if (buttonClicked == QMessageBox::Yes){
        // Remove the product from the user's inventory
        m_user->removerProduct(productSKU.toStdString());

        // Remove the product from the data storage
        DataHandler data;
        data.removeProduct(productSKU.toStdString(), m_user->getMID());
    }
    else
        return;
}

void inventory_widget::search(const QString &text){
    QString searchBy = ui->CB_searchBy->currentText();

    if (searchBy == "Name")
        updateTableViewWithSearchCriteria(text.toLower(), &Product::getName);
    else if (searchBy == "SKU")
        updateTableViewWithSearchCriteria(text.toLower(), &Product::getSku);
    else if (searchBy == "Category")
        updateTableViewWithSearchCriteria(text.toLower(), &Product::getCategory);
    else if (searchBy =="Brand")
        updateTableViewWithSearchCriteria(text.toLower(), &Product::getBrand);
    else if (searchBy == "Unit")
        updateTableViewWithSearchCriteria(text.toLower(), &Product::getUnit);
}

template<typename MemberFunction>
void inventory_widget::updateTableViewWithSearchCriteria(const QString& text, MemberFunction memberFunction) {
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;

    for (const Product& product : products) {
        QString value = QString::fromStdString((product.*memberFunction)()).toLower();

        if (value.startsWith(text)) {
            m_tableViewModel.setItem(row, 0, new QStandardItem(QString::fromStdString(product.getSku())));
            m_tableViewModel.setItem(row, 1, new QStandardItem(QString::fromStdString(product.getName())));
            m_tableViewModel.setItem(row, 2, new QStandardItem(QString::fromStdString(product.getBrand())));
            m_tableViewModel.setItem(row, 3, new QStandardItem(QString::fromStdString(product.getCategory())));
            m_tableViewModel.setItem(row, 4, new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(product.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row, 5, new QStandardItem(QString::number(product.getStock())));
            m_tableViewModel.setItem(row, 6, new QStandardItem(QString::number(product.getAvailable())));
            m_tableViewModel.setItem(row, 7, new QStandardItem(QString::fromStdString(product.getUnit())));
            m_tableViewModel.setItem(row, 8, new QStandardItem(QString::fromStdString(product.getAddedDate())));
            m_tableViewModel.setItem(row, 9, new QStandardItem(QString::fromStdString(product.getExDate())));
            row++;
        }
    }
}

void inventory_widget::on_TV_products_doubleClicked(const QModelIndex &index){
    // Get the row index of the double-clicked item
    int row = index.row();

    // Retrieve the SKU (item at column 0) from the model
    std::string sku = m_tableViewModel.item(row,0)->data(Qt::DisplayRole).toString().toStdString();

    // Get a reference to the product based on the SKU
    Product& product = m_user->editProducts().editProduct(sku);

    // Create the edit product window
    edit_product_window* editProductWindow = new edit_product_window(m_user, &product, this);

    // Connect the windowClosed signal from editProductWindow to the onDialogClosed slot
    connect(editProductWindow, &edit_product_window::windowClosed, this, &inventory_widget::onDialogClosed);

    // Set the window as modal and show it
    editProductWindow->setModal(true);
    editProductWindow->show();
}

void inventory_widget::on_PB_add_clicked(){
    // Create the add product window
    add_product_window* addProductWindow = new add_product_window(m_user, this);

    // Connect the dialogClosed signal from addProductWindow to the onDialogClosed slot
    connect(addProductWindow, &add_product_window::dialogClosed, this, &inventory_widget::onDialogClosed);

    // Set the window as modal and show it
    addProductWindow->setModal(true);
    addProductWindow->show();
}


void inventory_widget::onDialogClosed(){
    updateFilterBrand();
    updateFilterCategory();
    updateTable();
}

void inventory_widget::on_PB_remove_clicked() {
    // Get the selection model for the table view
    QItemSelectionModel* selectionModel = ui->TV_products->selectionModel();
    // Get the currently selected index
    QModelIndex selectedIndex = selectionModel->currentIndex();

    // Check if a valid index is selected
    if (selectedIndex.isValid()) {
        int row = selectedIndex.row();

        removeProduct(row);

        updateFilterBrand();
        updateFilterCategory();
        updateTable();
    }
}

void inventory_widget::on_PB_brandFilter_clicked(){
    // Get the currently selected index
    QModelIndex selectedIndex = ui->LV_brandList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString brand = selectedIndex.data(Qt::DisplayRole).toString();

        updateTableViewWithSearchCriteria(brand.toLower(), &Product::getBrand);
        ui->LE_search->setText("");
    }

    ui->LV_categoryList->clearSelection();
}

void inventory_widget::onSelectionChangedBrands(const QItemSelection& selected, const QItemSelection& deselected){
    // Check if there is at least one selected item
    if (!selected.isEmpty()) {
        // Enable the QPushButton
        ui->PB_brandFilter->setEnabled(true);
    }
    else {
        // No selected items, disable the QPushButton
        ui->PB_brandFilter->setEnabled(false);
    }
}

void inventory_widget::onSelectionChangedCategories(const QItemSelection &selected, const QItemSelection &deselected){
    // Check if there is at least one selected item
    if (!selected.isEmpty()) {
        // Enable the QPushButton
        ui->PB_categoryFilter->setEnabled(true);
    }
    else {
        // No selected items, disable the QPushButton
        ui->PB_categoryFilter->setEnabled(false);
    }
}

void inventory_widget::on_PB_categoryFilter_clicked(){
    // Get the currently selected index
    QModelIndex selectedIndex = ui->LV_categoryList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString category = selectedIndex.data(Qt::DisplayRole).toString();

        updateTableViewWithSearchCriteria(category.toLower(), &Product::getCategory);
        ui->LE_search->setText("");
    }

    ui->LV_brandList->clearSelection();
}

void inventory_widget::handleHeaderDoubleClicked(int logicalIndex){
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
    ui->LV_brandList->clearSelection();
    ui->LV_categoryList->clearSelection();
    search(text);
}
