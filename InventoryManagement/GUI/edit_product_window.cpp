#include "edit_product_window.h"
#include "../datahandler.h"
#include "ui_edit_product_window.h"
#include <QValidator>
#include <QMessageBox>

edit_product_window::edit_product_window(Seller* user,Product* product,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_product_window)
{
    ui->setupUi(this);
    m_user = user;
    m_product = product;

    this->setWindowTitle("Edit Product");

    ui->LE_price->setValidator(new QDoubleValidator(0,100, 5, this));
    ui->LE_stock->setValidator(new QDoubleValidator(0,100, 5, this));
    ui->LE_available->setValidator(new QDoubleValidator(0,100, 5, this));

    ui->DE_addDate->setDisplayFormat("yyyy/MM/dd");
    ui->DE_exDate->setDisplayFormat("yyyy/MM/dd");

    connect(this, &QDialog::finished, this, &edit_product_window::windowClosed);

    resetLabels();
}

edit_product_window::~edit_product_window()
{
    delete ui;
}

void edit_product_window::resetLabels(){
    hideError();
    ui->LE_name->setText(QString::fromStdString(m_product->getName()));
    ui->LE_brand->setText(QString::fromStdString(m_product->getBrand()));
    ui->LE_category->setText(QString::fromStdString(m_product->getCategory()));
    ui->LE_price->setText(QString::number(m_product->getPrice()));
    ui->LE_stock->setText(QString::number(m_product->getStock()));
    ui->LE_unit->setText(QString::fromStdString(m_product->getUnit()));
    ui->LE_available->setText(QString::number(m_product->getAvailable()));
    ui->LE_SKU->setText(QString::fromStdString(m_product->getSku()));
    ui->textEdit->setText(QString::fromStdString(m_product->getDescription()));

    QDate addDate = QDate::fromString(QString::fromStdString(m_product->getAddedDate()), "yyyy/MM/dd");
    ui->DE_addDate->setDate(addDate);

    if (m_product->getExDate() != "none"){
        ui->exparationDate_checkBox->setChecked(true);
        QDate exDate = QDate::fromString(QString::fromStdString(m_product->getExDate()), "yyyy/MM/dd");
        ui->DE_exDate->setDate(exDate);
        ui->LB_exDate->setVisible(true);
    }
    else{
        ui->LB_exDate->setVisible(false);
        ui->DE_exDate->setVisible(false);
        ui->exparationDate_checkBox->setChecked(false);
    }

}

void edit_product_window::hideError(){
    ui->LB_nameError->setVisible(false);
    ui->LB_brandError->setVisible(false);
    ui->LB_categoryError->setVisible(false);
    ui->LB_priceError->setVisible(false);
    ui->LB_stockError->setVisible(false);
    ui->LB_unitError->setVisible(false);
    ui->LB_availableError->setVisible(false);
    ui->LB_SKUerror->setVisible(false);
}

bool edit_product_window::isEmpty(){
    bool empty = false;
    if (ui->LE_name->text().trimmed().isEmpty()){
        ui->LB_nameError->setText("This field is required");
        ui->LB_nameError->setVisible(true);
        empty = true;
    }
    if (ui->LE_brand->text().trimmed().isEmpty()){
        ui->LB_brandError->setText("This field is required");
        ui->LB_brandError->setVisible(true);
        empty = true;
    }
    if (ui->LE_category->text().trimmed().isEmpty()){
        ui->LB_categoryError->setText("This field is required");
        ui->LB_categoryError->setVisible(true);
        empty = true;
    }
    if (ui->LE_price->text().trimmed().isEmpty()){
        ui->LB_priceError->setText("This field is required");
        ui->LB_priceError->setVisible(true);
        empty = true;
    }
    if (ui->LE_available->text().trimmed().isEmpty()){
        ui->LB_availableError->setText("This field is required");
        ui->LB_availableError->setVisible(true);
        empty = true;
    }
    if (ui->LE_stock->text().trimmed().isEmpty()){
        ui->LB_stockError->setText("This field is required");
        ui->LB_stockError->setVisible(true);
        empty = true;
    }
    if (ui->LE_unit->text().trimmed().isEmpty()){
        ui->LB_unitError->setText("This field is required");
        ui->LB_unitError->setVisible(true);
        empty = true;
    }
    if (ui->LE_SKU->text().trimmed().isEmpty()){
        ui->LB_SKUerror->setText("This field is required");
        ui->LB_SKUerror->setVisible(true);
        empty = true;
    }

    return empty;
}

bool edit_product_window::skuValidation(const QString &desiredSKU){
    const std::vector<Product>& products = m_user->getProductsModel().getProducts();
    for (const Product& product : products){
        if (product.getSku() == m_product->getSku())
            continue;
        else {
            if (product.getSku() == desiredSKU.toStdString()){
                return false;
            }
        }
    }

    return true;
}

void edit_product_window::editProduct(){
    std::string name = ui->LE_name->text().trimmed().toStdString();
    std::string brand = ui->LE_brand->text().trimmed().toStdString();
    std::string category = ui->LE_category->text().trimmed().toStdString();
    double price = std::stod(ui->LE_price->text().trimmed().toStdString());
    double stock = std::stod(ui->LE_stock->text().trimmed().toStdString());
    std::string unit = ui->LE_unit->text().trimmed().toStdString();
    double available = std::stod(ui->LE_available->text().trimmed().toStdString());
    std::string sku = ui->LE_SKU->text().trimmed().toStdString();
    std::string description = ui->textEdit->toPlainText().toStdString();

    QDate addedDate = ui->DE_addDate->date();
    std::string addedDateStr = addedDate.toString("yyyy/MM/dd").toStdString();

    std::string exDateStr = "none";
    if (ui->exparationDate_checkBox->isChecked()){
        QDate exDate = ui->DE_exDate->date();
        exDateStr = exDate.toString("yyyy/MM/dd").toStdString();
    }
    else{
        exDateStr = "none";
    }
    bool availability = available > 0;

    std::string currentSKU = m_product->getSku();

    m_user->editProduct(m_product->getSku(), name, category, sku, brand, stock, available, price
                        , unit, description, addedDateStr, exDateStr, availability);
    m_product = &(m_user->editProducts().editProduct(sku));

    DataHandler data;
    data.updateProduct(currentSKU, *m_product, m_user->getMID());
}

void edit_product_window::savedMessage(){
    QMessageBox* message = new QMessageBox(this);

    message->setWindowTitle("Changes applied successfully");
    message->setText("Edits saved successfully.");
    message->setIcon(QMessageBox::Information);

    QPushButton* okPB = message->addButton("Okey", QMessageBox::AcceptRole);

    message->show();

    connect(okPB, &QPushButton::clicked, this, &QDialog::close);
}

void edit_product_window::on_exparationDate_checkBox_stateChanged(int arg1){
    if (arg1 == 0){
        ui->LB_exDate->setVisible(false);
        ui->DE_exDate->setVisible(false);
    }
    else{
        ui->LB_exDate->setVisible(true);
        ui->DE_exDate->setVisible(true);
    }
}

void edit_product_window::on_PB_reset_clicked(){
    resetLabels();
}

void edit_product_window::on_PB_cancel_clicked(){
    this->deleteLater();
}

void edit_product_window::on_PB_delete_clicked(){
    QString productSKU = QString::fromStdString(m_product->getSku());

    // Create a message box to confirm the removal of the product
    QMessageBox* messageBox = new QMessageBox(this);
    messageBox->setText("Are you sure you want to remove the product with SKU code " + productSKU + " from your inventory?");
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

        this->close();
    }
    else
        return;
}

void edit_product_window::on_PB_save_clicked(){
    hideError();
    if (!isEmpty()){
        if (!skuValidation(ui->LE_SKU->text().trimmed())){
            ui->LB_SKUerror->setText("This product code is already assigned to another item");
            ui->LB_SKUerror->setVisible(true);
        }
        else {
            editProduct();
            savedMessage();
        }
    }
    else
        return;
}
