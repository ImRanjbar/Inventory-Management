#include "reports_widget.h"
#include "ui_reports_widget.h"
#include "currency.h"

reports_widget::reports_widget(Manufacturers* manufacturers, Seller* user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reports_widget)
{
    ui->setupUi(this);
    m_manufacturers = manufacturers;
    m_user = user;

    setTableColumns();

    updatePurchaseTable();

    updateSoldTable();

    setLabels();

}


reports_widget::~reports_widget()
{
    delete ui;
}

void reports_widget::setTableColumns(){

    m_purchaseItemModel.setHorizontalHeaderItem(0, new QStandardItem("Invoice Number"));
    m_purchaseItemModel.setHorizontalHeaderItem(1, new QStandardItem("Date"));
    m_purchaseItemModel.setHorizontalHeaderItem(2, new QStandardItem("Provider"));
    m_purchaseItemModel.setHorizontalHeaderItem(3, new QStandardItem("Order Count"));
    m_purchaseItemModel.setHorizontalHeaderItem(4, new QStandardItem("Amount"));


    m_soldItemModel.setHorizontalHeaderItem(0, new QStandardItem("Invoice Number"));
    m_soldItemModel.setHorizontalHeaderItem(1, new QStandardItem("Date"));
    m_soldItemModel.setHorizontalHeaderItem(2, new QStandardItem("Buyer"));
    m_soldItemModel.setHorizontalHeaderItem(3, new QStandardItem("Order Count"));
    m_soldItemModel.setHorizontalHeaderItem(4, new QStandardItem("Amount"));

    ui->TV_purchase->setModel(&m_purchaseItemModel);
    ui->TV_purchase->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->TV_solds->setModel(&m_soldItemModel);
    ui->TV_solds->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void reports_widget::updatePurchaseTable(){
    const std::vector<Invoice>& invoices = m_user->getPurchaseHistory().getInvoices();

    int row = 0;
    for (const Invoice& invoice : invoices){
        m_purchaseItemModel.setItem(row, 0, new QStandardItem(QString::number(invoice.getInvoiceNumber())));
        m_purchaseItemModel.setItem(row, 1, new QStandardItem(QString::fromStdString(invoice.getDate())));
        m_purchaseItemModel.setItem(row, 2, new QStandardItem(QString::fromStdString(invoice.getProviderName())));
        m_purchaseItemModel.setItem(row, 3, new QStandardItem(QString::number(invoice.getInvoiceItemModel().getItems().size())));
        m_purchaseItemModel.setItem(row, 4, new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(invoice.getTotalAmount(), 'f', 2)));
        row++;

        qDebug() << QString::number(invoice.getInvoiceNumber()) << " invoice have added to purchase history\n";
    }
}

void reports_widget::updateSoldTable(){
    const std::vector<Invoice>& invoices = m_user->getSoldHistory().getInvoices();

    int row = 0;
    for (const Invoice& invoice : invoices){
        m_soldItemModel.setItem(row, 0, new QStandardItem(QString::number(invoice.getInvoiceNumber())));
        m_soldItemModel.setItem(row, 1, new QStandardItem(QString::fromStdString(invoice.getDate())));
        m_soldItemModel.setItem(row, 2, new QStandardItem(QString::fromStdString(invoice.getCustomerName())));
        m_soldItemModel.setItem(row, 3, new QStandardItem(QString::number(invoice.getInvoiceItemModel().getItems().size())));
        m_soldItemModel.setItem(row, 4, new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(invoice.getTotalAmount(), 'f', 2)));
        row++;

        qDebug() << QString::number(invoice.getInvoiceNumber()) << " invoice have added to sold history\n";
    }
}

void reports_widget::setLabels(){
    double totalCost{0};
    int totalOrders{0};

    for (const Invoice& invoice : m_user->getPurchaseHistory().getInvoices()){
        totalCost += invoice.getTotalAmount();
        totalOrders += static_cast<int>(invoice.getInvoiceItemModel().getItems().size());
    }
    if (totalCost > 10000)
        ui->LB_totalCost->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalCost/1000, 'f', 2) + "K");
    else
        ui->LB_totalCost->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalCost, 'f', 2));

    ui->LB_totalOrders->setText(QString::number(totalOrders));


    double totalRevenue{0};
    int totalSolds{0};

    for (const Invoice& invoice : m_user->getSoldHistory().getInvoices()){
        totalRevenue += invoice.getTotalAmount();
        totalSolds += static_cast<int>(invoice.getInvoiceItemModel().getItems().size());
    }

    if (totalRevenue > 10000)
        ui->LB_totalRevenue->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalRevenue/1000, 'f', 2) + "K");
    else
        ui->LB_totalRevenue->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalRevenue, 'f', 2));
    ui->LB_ItemsSold->setText(QString::number(totalSolds));

}

void reports_widget::on_tabWidget_tabBarClicked(int index)
{
    qDebug() << index << '\n';
}

