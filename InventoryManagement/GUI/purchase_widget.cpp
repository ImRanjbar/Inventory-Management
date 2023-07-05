#include "purchase_widget.h"
#include "ui_purchase_widget.h"

#include "add_to_invoice.h"
#include "product_information_window.h"
#include "../currency.h"

purchase_widget::purchase_widget(Manufacturers* manufacturers, Seller* user ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchase_widget)
{
    ui->setupUi(this);
    m_manufacturers = manufacturers;
    m_user = user;

    ui->PB_brand->setEnabled(false);
    ui->PB_category->setEnabled(false);
    customizeListItems();
    setSearchComboBox();
    setProvidersComboBox();
    initializeTableView();
}

purchase_widget::~purchase_widget()
{
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

void purchase_widget::setSearchComboBox(){
    ui->CB_searchBy->addItem("Name");
    ui->CB_searchBy->addItem("SKU");
    ui->CB_searchBy->addItem("Category");
    ui->CB_searchBy->addItem("Brand");
    ui->CB_searchBy->addItem("Unit");
}

void purchase_widget::setProvidersComboBox(){
    ui->CB_providers->addItem("none");
    std::string userMID = m_user->getMID();
    for (const Seller* seller : m_manufacturers->getManufacturers())
        if(seller->getMID() != userMID)
            ui->CB_providers->addItem(QString::fromStdString(seller->getManufactureName()));
}

void purchase_widget::initializeTableView(){
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
    ui->TV_items->setItemDelegate(new CenterAlignmentDelegate(ui->TV_items));

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
    ui->TV_items->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->TV_items->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Set the size of each column
    const int numColumns = 9;
    const int defaultColumnWidth = 100;
    for (int column = 0; column < numColumns; ++column) {
        if (column == 4)    // for Price column
            ui->TV_items->setColumnWidth(column, 90);
        else if (column == 5 || column == 6 || column == 7 || column == 8 || column == 9)
            ui->TV_items->setColumnWidth(column, 70);
        else
            ui->TV_items->setColumnWidth(column, defaultColumnWidth);
    }

    ui->TV_items->horizontalHeader()->setSectionsClickable(true);

    // Connect the table header signals to the respective slots for sorting table elements
    connect(ui->TV_items->horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, &purchase_widget::handleHeaderDoubleClicked);
    connect(ui->TV_items->horizontalHeader(), &QHeaderView::sectionClicked, this, &purchase_widget::handleHeaderClicked);
}

void purchase_widget::updateTable(){

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
        }
    }
}

void purchase_widget::updateFilterBrand(){
    // Remove existing rows from the brand filter list
    m_brandFilterList.removeRows(0, m_brandFilterList.rowCount());

    if (m_provider) {
        QStringList brands;

        // Retrieve the invoice items from the provider's invoice items model
        for (const InvoiceItem& item : m_provider->getInvoiceItemsModel().getItems()) {
            QString brand = QString::fromStdString(item.getBrand());
            if (!brands.contains(brand))
                brands << brand;
        }

        // Set the string list of brands to the brand filter list
        m_brandFilterList.setStringList(brands);

        // Set the brand filter list as the model for the brand list view
        ui->LV_brandList->setModel(&m_brandFilterList);
    }

    // Connect the selectionChanged signal of the brand list view's selection model
    // to the onSelectionChangedBrands slot of the purchase_widget
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

    // Connect the selectionChanged signal of the category list view's selection model
    // to the onSelectionChangedCategories slot of the purchase_widget
    connect(ui->LV_categoryList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &purchase_widget::onSelectionChangedCategories);
}

void purchase_widget::addItemToInvoice(int row){
    // Get the index of the selected cell
    QModelIndex selectedCellIndex = ui->TV_items->model()->index(row, 0);

    // Extract the SKU from the selected cell
    QString selectedSku = ui->TV_items->model()->data(selectedCellIndex, Qt::DisplayRole).toString();

    InvoiceItem& selectedItem = m_provider->editInvoiceItems().editItem(selectedSku.toStdString());

    // Create a new instance of the add_to_invoice dialog
    add_to_invoice* addWindow = new add_to_invoice(m_user, m_provider, &selectedItem, this);

    // Connect the dialog's dialogClosed signal to the purchase_widget's onAddToInvoiceDialogClosed slot
    connect(addWindow, &add_to_invoice::dialogClosed, this, &purchase_widget::onAddToInvoiceDialogClosed);

    // Set the dialog as modal and show it
    addWindow->setModal(true);
    addWindow->show();
}

void purchase_widget::search(const QString &text){
    QString searchBy = ui->CB_searchBy->currentText();

    if (searchBy == "Name")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getName);
    else if (searchBy == "SKU")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getSku);
    else if (searchBy == "Category")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getCategory);
    else if (searchBy =="Brand")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getBrand);
    else if (searchBy == "Unit")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getUnit);
}

template<typename MemberFunction>
void purchase_widget::updateTableViewWithSearchCriteria(const QString& text, MemberFunction memberFunction) {
    const std::vector<InvoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;

    for (const InvoiceItem& item : items) {
        // Get the value of the member function and convert it to lowercase for case-insensitive comparison
        QString value = QString::fromStdString((item.*memberFunction)()).toLower();

        if (value.startsWith(text)) {
            // Get the selected value from the user's invoice, if available
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
}

void purchase_widget::on_CB_providers_currentTextChanged(const QString &arg1){
    if (arg1 != "none"){
        m_provider = m_manufacturers->editSellerByManuName(arg1.toStdString());
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
    // Get the selection model for the table view
    QItemSelectionModel* selectionModel = ui->TV_items->selectionModel();

    // Get the currently selected index
    QModelIndex selectedIndex = selectionModel->currentIndex();

    if (selectedIndex.isValid()) {
        int row = selectedIndex.row();
        addItemToInvoice(row);
    }
}

void purchase_widget::onAddToInvoiceDialogClosed(){
    ui->LE_searchBar->setText("");
    ui->LV_brandList->clearSelection();
    ui->LV_categoryList->clearSelection();
    updateTable();
}

void purchase_widget::on_LE_searchBar_textChanged(const QString &arg1){
    ui->LV_brandList->clearSelection();
    ui->LV_categoryList->clearSelection();
    search(arg1);
}

void purchase_widget::on_PB_brand_clicked(){
    QModelIndex selectedIndex = ui->LV_brandList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString brand = selectedIndex.data(Qt::DisplayRole).toString();

        updateTableViewWithSearchCriteria(brand.toLower(), &InvoiceItem::getBrand);
        ui->LE_searchBar->setText("");
    }

    ui->LV_categoryList->clearSelection();
}

void purchase_widget::on_PB_category_clicked(){
    QModelIndex selectedIndex = ui->LV_categoryList->currentIndex();

    if (selectedIndex.isValid()) {
        // Get the selected text directly from the model
        QString category = selectedIndex.data(Qt::DisplayRole).toString();

        updateTableViewWithSearchCriteria(category.toLower(), &InvoiceItem::getCategory);
        ui->LE_searchBar->setText("");
    }

    ui->LV_brandList->clearSelection();
}

void purchase_widget::onSelectionChangedBrands(const QItemSelection &selected, const QItemSelection &deselected){
    if (!selected.isEmpty())
        ui->PB_brand->setEnabled(true);
    else
        ui->PB_brand->setEnabled(false);
}

void purchase_widget::onSelectionChangedCategories(const QItemSelection &selected, const QItemSelection &deselected){
    if (!selected.isEmpty())
        ui->PB_category->setEnabled(true);
    else
        ui->PB_category->setEnabled(false);
}

void purchase_widget::on_TV_items_doubleClicked(const QModelIndex &index){
    const int row = index.row();

    // Extract the SKU from the table view model
    std::string sku = m_tableViewModel.item(row, 0)->data(Qt::DisplayRole).toString().toStdString();

    // Get the corresponding InvoiceItem using the SKU
    const InvoiceItem& item = m_provider->getInvoiceItemsModel().getItem(sku);

    product_information_window* informationWindow = new product_information_window(m_user, &item, this);
    informationWindow->setModal(true);
    informationWindow->show();
}

void purchase_widget::handleHeaderDoubleClicked(int logicalIndex){
    if (m_provider){
        switch (logicalIndex){
        case 0:
            m_provider->editInvoiceItems().sortBySKU();
            break;
        case 1:
            m_provider->editInvoiceItems().sortByName();
            break;
        case 2:
            m_provider->editInvoiceItems().sortByBrand();
            break;
        case 3:
            m_provider->editInvoiceItems().sortByCategory();
            break;
        case 4:
            m_provider->editInvoiceItems().sortByPrice();
            break;
        case 5:
            m_provider->editInvoiceItems().sortByInventory();
            break;
        case 7:
            m_provider->editInvoiceItems().sortByUnit();
            break;
        case 8:
            m_provider->editInvoiceItems().sortByAddDate();
            break;
        case 9:
            m_provider->editInvoiceItems().sortByExDate();
            break;
        }

        updateTable();
    }
}

void purchase_widget::handleHeaderClicked(int logicalIndex){
    if (m_provider){
        switch (logicalIndex){
        case 0:
            m_provider->editInvoiceItems().sortBySkuDes();
            break;
        case 1:
            m_provider->editInvoiceItems().sortByNameDes();
            break;
        case 2:
            m_provider->editInvoiceItems().sortByBrandDes();
            break;
        case 3:
            m_provider->editInvoiceItems().sortByCategoryDes();
            break;
        case 4:
            m_provider->editInvoiceItems().sortByPriceDes();
            break;
        case 5:
            m_provider->editInvoiceItems().sortByInventoryDes();
            break;
        case 7:
            m_provider->editInvoiceItems().sortByUnitDes();
            break;
        case 8:
            m_provider->editInvoiceItems().sortByAddDateDes();
            break;
        case 9:
            m_provider->editInvoiceItems().sortByExDateDes();
            break;
        }

        updateTable();
    }
}
