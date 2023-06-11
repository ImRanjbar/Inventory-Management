#include "add_to_invoice.h"
#include "ui_add_to_invoice.h"
#include <QValidator>

add_to_invoice::add_to_invoice(Seller *user, Seller *provider, InvoiceItem* item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_to_invoice)
{
    m_user = user;
    m_provider = provider;
    m_item = item;
    ui->setupUi(this);

    m_user->editInvoice().setCustomerName(m_user->getManufactureName());
    m_user->editInvoice().setCustomerID(m_user->getMID());

    m_itemExistence = m_user->getInvoice().getInvoiceItemModel().existence(m_item->getSku());

    ui->LE_selected->setValidator(new QDoubleValidator(0,100, 5, this));

    connect(this, &QDialog::finished, this, &add_to_invoice::dialogClosed);

    setLabels();
}

add_to_invoice::~add_to_invoice()
{
    delete ui;
}

void add_to_invoice::setLabels(){
    if (!m_itemExistence)
        ui->LB_error->setVisible(false);
    else {
        ui->LE_selected->setText(QString::number(m_user->getInvoice().getInvoiceItemModel().getItem(m_item->getSku()).getInventory()));
    }
    ui->LB_selectedError->setVisible(false);
    ui->LB_itemName->setText(QString::fromStdString(m_item->getName()));
    ui->LB_itemSKU->setText(QString::fromStdString(m_item->getSku()));
    ui->LB_itemAvailable->setText(QString::number(m_item->getInventory())
                                  + " " + QString::fromStdString(m_item->getUnit()));
}

void add_to_invoice::addItem(){

    if (m_user->getInvoice().getProviderID() == m_provider->getMID()){
        if (!m_itemExistence){
            InvoiceItem item = *m_item;
            item.setInventory(ui->LE_selected->text().toDouble());
            m_user->editInvoice().addItem(item);
        }
        else {
            m_user->editInvoice().editInvoiceItemModel().editItem(m_item->getSku()).setInventory(ui->LE_selected->text().toDouble());
        }
    }
    else if (m_user->getInvoice().getProviderID() == ""){
        qDebug() << "new Invoice for user\n";
        m_user->editInvoice().setProviderID(m_provider->getMID());
        m_user->editInvoice().setProviderName(m_provider->getManufactureName());
        m_user->editInvoice().createInvoiceNumber();
        InvoiceItem item = *m_item;
        item.setInventory(ui->LE_selected->text().toDouble());
        m_user->editInvoice().addItem(item);
    }
    else if (m_user->getInvoice().getProviderID() != m_provider->getMID()){
        qDebug() << "clear Invoice\n";
        m_user->editInvoice().clearInvoice();
        qDebug() << "new Invoice for user with new provider\n";
        m_user->editInvoice().setProviderName(m_provider->getManufactureName());
        m_user->editInvoice().setProviderID(m_provider->getMID());
        m_user->editInvoice().createInvoiceNumber();
        InvoiceItem item = *m_item;
        item.setInventory(ui->LE_selected->text().toDouble());
        m_user->editInvoice().addItem(item);
    }
}


void add_to_invoice::on_LE_selected_textChanged(const QString &arg1){
    double available = m_item->getInventory();
    available -= arg1.toDouble();

    if (available > 0){
        ui->LB_itemAvailable->setText(QString::number(available) + " " + QString::fromStdString(m_item->getUnit()));
    }
    else
        ui->LB_itemAvailable->setText(QString::number(available) + " " + QString::fromStdString(m_item->getUnit()));

}



void add_to_invoice::on_PB_add_clicked(){

    ui->LB_selectedError->setVisible(false);

    double available = m_item->getInventory();
    QString lineEditText = ui->LE_selected->text();
    double selected = lineEditText.toDouble();

    if (selected > available){
        ui->LB_selectedError->setVisible(true);
        ui->LB_selectedError->setText("The stock level is insufficient to meet the selected quantity");
    }
    else if (lineEditText.trimmed().isEmpty()){
        ui->LB_selectedError->setVisible(true);
        ui->LB_selectedError->setText("This field is required");
    }
    else if (selected <= 0.0){
        ui->LB_selectedError->setVisible(true);
        ui->LB_selectedError->setText("Invalid");
    }
    else{
        addItem();
        this->close();
    }
}

