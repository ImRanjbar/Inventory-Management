#include "purchase_invoice_window.h"
#include "product_information_window.h"
#include "ui_purchase_invoice_window.h"
#include "../Currency.h"
#include "../datahandler.h"
#include <QFileDialog>
#include <QStyledItemDelegate>

purchase_invoice_window::purchase_invoice_window(Invoice &invoice, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::purchase_invoice_window)
{
    ui->setupUi(this);
    m_invoice = invoice;

    this->setWindowTitle("Invoice");

    initializeTableView();
    setComboBox();
    addItems();
    setLabels();
}

purchase_invoice_window::~purchase_invoice_window()
{
    delete ui;
}

void purchase_invoice_window::setLabels(){
    ui->LB_invoiceNumber->setText(QString::number(m_invoice.getInvoiceNumber()));
    ui->LB_date->setText(QString::fromStdString(m_invoice.getDate()));
    ui->LB_manufacturerName->setText(QString::fromStdString(m_invoice.getProviderName()));
    ui->LB_MID->setText(QString::fromStdString(m_invoice.getProviderID()));
    ui->LB_amount->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(m_invoice.getTotalAmount()));
}

void purchase_invoice_window::initializeTableView(){
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

    m_itemsModel.setHorizontalHeaderItem(0, new QStandardItem("SKU"));
    m_itemsModel.setHorizontalHeaderItem(1, new QStandardItem("Name"));
    m_itemsModel.setHorizontalHeaderItem(2, new QStandardItem("Quantity"));
    m_itemsModel.setHorizontalHeaderItem(3, new QStandardItem("Unit Price"));
    m_itemsModel.setHorizontalHeaderItem(4, new QStandardItem("Total"));

    ui->TV_items->setModel(&m_itemsModel);
    ui->TV_items->setEditTriggers(QAbstractItemView::NoEditTriggers);

    const int columnWidth = 100;
    for (int column = 0; column < 5; column++){
        ui->TV_items->setColumnWidth(column, columnWidth);
    }
    ui->TV_items->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void purchase_invoice_window::setComboBox(){
    ui->CB_searchBy->addItem("Name");
    ui->CB_searchBy->addItem("SKU");
    ui->CB_searchBy->addItem("Category");
    ui->CB_searchBy->addItem("Brand");
    ui->CB_searchBy->addItem("Unit");
}

void purchase_invoice_window::addItems(){
    const std::vector<InvoiceItem>& items = m_invoice.getInvoiceItemModel().getItems();

    int row = 0;
    for (const InvoiceItem& item : items){
        m_itemsModel.setItem(row, 0, new QStandardItem(QString::fromStdString(item.getSku())));
        m_itemsModel.setItem(row, 1, new QStandardItem(QString::fromStdString(item.getName())));

        QString quantity = QString::number(item.getInventory()) + " " + QString::fromStdString(item.getUnit());
        m_itemsModel.setItem(row, 2, new QStandardItem(quantity));

        QString price = QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f' , 2);
        m_itemsModel.setItem(row, 3, new QStandardItem(price));

        const double total = item.getPrice()*item.getInventory();
        QString totalStr = QString::fromStdString(Currency::currencySymbol) + QString::number(total, 'f' , 2);
        m_itemsModel.setItem(row, 4, new QStandardItem(totalStr));
        row++;
    }
}

void purchase_invoice_window::search(const QString &text){
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
void purchase_invoice_window::updateTableViewWithSearchCriteria(const QString &text, MemberFunction memberFunction){
    const std::vector<InvoiceItem>& items = m_invoice.getInvoiceItemModel().getItems();

    // Clear the table
    m_itemsModel.removeRows(0, m_itemsModel.rowCount());

    int row = 0;

    for (const InvoiceItem& item : items) {
        QString value = QString::fromStdString((item.*memberFunction)()).toLower();

        if (value.startsWith(text)) {
            m_itemsModel.setItem(row, 0, new QStandardItem(QString::fromStdString(item.getSku())));
            m_itemsModel.setItem(row, 1, new QStandardItem(QString::fromStdString(item.getName())));

            QString quantity = QString::number(item.getInventory()) + " " + QString::fromStdString(item.getUnit());
            m_itemsModel.setItem(row, 2, new QStandardItem(quantity));

            QString price = QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f' , 2);
            m_itemsModel.setItem(row, 3, new QStandardItem(price));

            const double total = item.getPrice()*item.getInventory();
            QString totalStr = QString::fromStdString(Currency::currencySymbol) + QString::number(total, 'f' , 2);
            m_itemsModel.setItem(row, 4, new QStandardItem(totalStr));
            row++;
        }
    }
}

void purchase_invoice_window::on_TV_items_doubleClicked(const QModelIndex &index){
    const int row = index.row();
    const std::string sku = m_itemsModel.item(row,0)->data(Qt::DisplayRole).toString().toStdString();

    const InvoiceItem& item = m_invoice.getInvoiceItemModel().getItem(sku);

    product_information_window* productInfWindow = new product_information_window(&item,this);
    productInfWindow->setModal(true);
    productInfWindow->show();
}

void purchase_invoice_window::on_PB_print_clicked(){
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("csv");
    dialog.setNameFilter("CSV Files (*.csv)");

    if (dialog.exec() == QDialog::Accepted){
        QString filePath = dialog.selectedFiles().at(0);
        DataHandler data;
        data.printInvoice(filePath.toStdString(), m_invoice);
    }
}

void purchase_invoice_window::on_LE_search_textChanged(const QString &arg1){
    search(arg1);
}
