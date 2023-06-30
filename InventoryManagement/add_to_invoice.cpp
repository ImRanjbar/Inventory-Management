#include "add_to_invoice.h"
#include "ui_add_to_invoice.h"
#include <QValidator>
#include <QMessageBox>

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
    if (!m_itemExistence){
        ui->LB_error->setVisible(false);
        ui->LB_itemAvailable->setText(QString::number(m_item->getInventory())
                                      + " " + QString::fromStdString(m_item->getUnit()));
    }
    else {
        double selected = m_user->getInvoice().getInvoiceItemModel().getItem(m_item->getSku()).getInventory();
        ui->LE_selected->setText(QString::number(selected));
        ui->LB_itemAvailable->setText(QString::number(m_item->getInventory() - selected)
                                      + " " + QString::fromStdString(m_item->getUnit()));
    }
    ui->LB_selectedError->setVisible(false);
    ui->LB_itemName->setText(QString::fromStdString(m_item->getName()));
    ui->LB_itemSKU->setText(QString::fromStdString(m_item->getSku()));
}

void add_to_invoice::addItem() {
    // Check if the current provider ID matches the provider ID of the user's invoice
    if (m_user->getInvoice().getProviderID() == m_provider->getMID()) {
        // Check if the item already exists in the invoice
        if (!m_itemExistence) {
            // Create a new invoice item, set its inventory, and add it to the user's invoice
            InvoiceItem item = *m_item;
            item.setInventory(ui->LE_selected->text().toDouble());
            m_user->editInvoice().addItem(item);
        } else {
            // Update the existing invoice item's inventory
            m_user->editInvoice().editInvoiceItemModel().editItem(m_item->getSku())
                .setInventory(ui->LE_selected->text().toDouble());
        }
    }
    // If the user's invoice has no provider ID (i.e., no existing invoice)
    else if (m_user->getInvoice().getProviderID().empty()) {
        // Set the provider ID, provider name, and create an invoice number for the user's new invoice
        m_user->editInvoice().setProviderID(m_provider->getMID());
        m_user->editInvoice().setProviderName(m_provider->getManufactureName());
        m_user->editInvoice().createInvoiceNumber();

        // Create a new invoice item, set its inventory, and add it to the user's invoice
        InvoiceItem item = *m_item;
        item.setInventory(ui->LE_selected->text().toDouble());
        m_user->editInvoice().addItem(item);
    }
    // If the user's invoice is associated with a different provider, prompt for confirmation
    else if (m_user->getInvoice().getProviderID() != m_provider->getMID()) {
        // Show a message box to confirm if the user wants to create a new invoice
        QMessageBox messageBox(this);
        messageBox.setText("Creating a new invoice will close the previous invoice from " +
                           QString::fromStdString(m_user->getInvoice().getProviderName()) + ".");
        messageBox.setInformativeText("Are you sure you want to create a new invoice?");
        messageBox.setWindowTitle("New Invoice");
        messageBox.addButton(QMessageBox::Yes);
        messageBox.addButton(QMessageBox::No);

        // Wait for the user to make a choice (Yes or No)
        int buttonClicked = messageBox.exec();

        // Check if the user clicked "Yes"
        if (buttonClicked == QMessageBox::Yes) {
            // Clear the current invoice and create a new one with the new provider
            m_user->editInvoice().clearInvoice();
            qDebug() << "Creating a new invoice for the user with a new provider.\n";
            m_user->editInvoice().setProviderName(m_provider->getManufactureName());
            m_user->editInvoice().setProviderID(m_provider->getMID());
            m_user->editInvoice().createInvoiceNumber();
            // Create a new invoice item, set its inventory, and add it to the user's invoice
            InvoiceItem item = *m_item;
            item.setInventory(ui->LE_selected->text().toDouble());
            m_user->editInvoice().addItem(item);
        }
        else {
            return;
        }
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
        ui->LB_selectedError->setText("Not enough stock available for desired quantity");
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

void add_to_invoice::on_PB_cancel_clicked(){
    qDebug() << "Cancel clicked\n";
    this->close();
}
