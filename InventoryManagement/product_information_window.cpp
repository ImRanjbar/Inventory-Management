#include "product_information_window.h"
#include "ui_product_information_window.h"
#include "currency.h"

product_information_window::product_information_window(Seller *user, const InvoiceItem *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::product_information_window)
{
    ui->setupUi(this);
    m_item = item;
    m_user = user;

    setLabels();
}

product_information_window::~product_information_window()
{
    delete ui;
}

void product_information_window::setLabels(){
    qDebug() << "in information_window::setLabels() item sku: " << m_item->getSku() << '\n';
    ui->LB_name->setText(QString::fromStdString(m_item->getName()));
    ui->LB_brand->setText(QString::fromStdString(m_item->getBrand()));
    ui->LB_category->setText(QString::fromStdString(m_item->getCategory()));
    ui->LB_price->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(m_item->getPrice()));
    ui->LB_inventory->setText(QString::number(m_item->getInventory()));
    ui->LB_addDate->setText(QString::fromStdString(m_item->getAddedDate()));
    ui->Lb_exDate->setText(QString::fromStdString(m_item->getExDate()));
    ui->descriptionTextBrowser->setText(QString::fromStdString(m_item->getDescription()));
    ui->LB_sku->setText(QString::fromStdString(m_item->getSku()));

    double selected{};
    if (m_user->getInvoice().getInvoiceItemModel().existence(m_item->getSku())){
        selected = m_user->getInvoice().getInvoiceItemModel().getItem(m_item->getSku()).getInventory();
    }
    ui->LB_selected->setText(QString::number(selected));
}
