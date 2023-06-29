#include "purchase_invoice_window.h"
#include "product_information_window.h"
#include "ui_purchase_invoice_window.h"
#include "Currency.h"
#include "datahandler.h"
#include <QFileDialog>

purchase_invoice_window::purchase_invoice_window(Invoice &invoice, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::purchase_invoice_window)
{
    ui->setupUi(this);
    m_invoice = invoice;

    setTableColumns();
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

void purchase_invoice_window::setTableColumns(){
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
