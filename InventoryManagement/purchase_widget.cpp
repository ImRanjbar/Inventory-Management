#include "purchase_widget.h"
#include "ui_purchase_widget.h"



purchase_widget::purchase_widget(Manufacturers* manufacturers, Seller* user ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchase_widget)
{
    ui->setupUi(this);
    m_manufacturers = manufacturers;
    m_user = user;

    customizeListItems();

    setSearchComboBox();
    setProvidersComboBox();
    setTableColumns();
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
    m_tableViewModel.setHorizontalHeaderItem(7 ,new QStandardItem("Added Date"));
    m_tableViewModel.setHorizontalHeaderItem(8 ,new QStandardItem("Expration Date"));

    ui->TV_items->setModel(&m_tableViewModel);
    ui->TV_items->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TV_items->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Set the size of each column
    const int numColumns = 9;
    const int columnWidth = 100;
    for (int column = 0; column < numColumns; ++column) {
        if (column == 4)
            ui->TV_items->setColumnWidth(column, 70);
        else if (column == 5 || column == 6)
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
        const std::vector<invoiceItem>& items = m_provider->getInvoiceItemsModel().getItems();
        int row = 0;
        for (const invoiceItem& item : items){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(item.getPrice())));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem("0"));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getAddedDate())));
            m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
            qDebug() << item.getName() << " have add to table model\n";
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
        for (const invoiceItem& item : m_provider->getInvoiceItemsModel().getItems()){
            brands << QString::fromStdString(item.getBrand());
        }

        m_brandFilterList.setStringList(brands);

        ui->LV_brandList->setModel(&m_brandFilterList);
    }
}

void purchase_widget::updateFilterCategory(){
    m_categoryFilterList.removeRows(0, m_categoryFilterList.rowCount());

    if (m_provider){
        QStringList categories;
        for (const invoiceItem& item : m_provider->getInvoiceItemsModel().getItems()){
            categories << QString::fromStdString(item.getCategory());
        }

        m_categoryFilterList.setStringList(categories);

        ui->LV_categoryList->setModel(&m_categoryFilterList);
    }
}



void purchase_widget::on_CB_providers_currentTextChanged(const QString &arg1){
    qDebug() << "in currentTextChanged provider combo box in purchase widget arg1: " << arg1 << '\n' ;
    if (arg1 != "none"){
        m_provider = m_manufacturers->editSellerByManuName(arg1.toStdString());
        qDebug() << "m_provider is " << m_provider->getUsername() << "\n";
        updateTable();
        updateFilterBrand();
        updateFilterCategory();
    }
    else {
        m_provider = nullptr;
        updateTable();
        updateFilterBrand();
        updateFilterCategory();
    }


}

