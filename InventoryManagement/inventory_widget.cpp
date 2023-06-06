#include "inventory_widget.h"
#include "ui_inventory_widget.h"
#include "add_product_window.h"
#include <QStringListModel>

inventory_widget::inventory_widget(Manufacturers* manufacturers, Seller* user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inventory_widget)
{
    ui->setupUi(this);

    customizeListItems();

    m_manufacturers = manufacturers;
    m_user = user;

    setSearchComboBox();
    setTableColumns();
    updateTable();
    updateFilterBrand();
    updateFilterCategory();
}

inventory_widget::~inventory_widget()
{
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
    m_tableViewModel.setHorizontalHeaderItem(7 ,new QStandardItem("Added Date"));
    m_tableViewModel.setHorizontalHeaderItem(8 ,new QStandardItem("Expration Date"));

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
        else if (column == 5 || column == 6)
            ui->TV_products->setColumnWidth(column, 70);
        else
            ui->TV_products->setColumnWidth(column, columnWidth);
    }
}

void inventory_widget::updateTable() {
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();
    int row = 0;
    for (const Product& product : products){
        m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(product.getSku())));
        m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(product.getName())));
        m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(product.getBrand())));
        m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(product.getCategory())));
        m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::number(product.getPrice())));
        m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(product.getStock())));
        m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::number(product.getAvailable())));
        m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(product.getAddedDate())));
        m_tableViewModel.setItem(row,8 ,new QStandardItem(QString::fromStdString(product.getExDate())));
        row++;
    }
}

void inventory_widget::updateFilterBrand(){
    QStringList brands;
    for (const Product& product : m_user->getProductsModel().getProducts()){
        qDebug() << product.getBrand() << "have added into filter brand listView\n";
        brands << QString::fromStdString(product.getBrand());
    }
    qDebug() << brands;

    m_brandFilterList.setStringList(brands);

    ui->LV_brandList->setModel(&m_brandFilterList);
}

void inventory_widget::updateFilterCategory(){
    QStringList categories;
    for (const Product& product : m_user->getProductsModel().getProducts()){
        qDebug() << product.getCategory() << "have added into filter category listView\n";
        categories << QString::fromStdString(product.getCategory());
    }
    qDebug() << categories;

    m_categoryFilterList.setStringList(categories);

    ui->LV_categoryList->setModel(&m_categoryFilterList);
}


void inventory_widget::on_TV_products_doubleClicked(const QModelIndex &index)
{
    qDebug() << index << '\n';
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

