#include "add_product_window.h"
#include "ui_add_product_window.h"

add_product_window::add_product_window(Seller *user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_product_window)
{
    m_parent = parent;
    m_user = user;

    // Connect the finished() signal of the dialog to the dialogClosed() signal
    connect(this, &QDialog::finished, this, &add_product_window::dialogClosed);

    ui->setupUi(this);
    hideErrors();
    expDateEdit();
}

add_product_window::~add_product_window()
{
    delete ui;
}

void add_product_window::hideErrors(){
    ui->LB_nameError->setText("");
    ui->LB_skuError->setText("");
    ui->LB_priceError->setText("");
    ui->LB_brandError->setText("");
    ui->LB_categoryError->setText("");
    ui->LB_stockError->setText("");
    ui->LB_availableError->setText("");
    ui->LB_unitError->setText("");
}

void add_product_window::expDateEdit(){
    if (ui->CB_expCheckBox->isChecked()){
        ui->DE_exDate->show();
        ui->LB_expDate->show();
    }
    else {
        ui->DE_exDate->hide();
        ui->LB_expDate->hide();
    }
}

bool add_product_window::checkIfEmpty(){

    bool empty = false;
    if (ui->LE_name->text().trimmed().isEmpty()){
        ui->LB_nameError->setText("This field is required");
        empty = true;
    }
    if(ui->LE_SKU->text().trimmed().isEmpty()){
        ui->LB_skuError->setText("This field is required");
        empty = true;
    }
    if (ui->LE_price->text().trimmed().isEmpty()){
        ui->LB_priceError->setText("This field is required");
        empty = true;
    }
    if (ui->LE_brand->text().trimmed().isEmpty()){
        ui->LB_brandError->setText("This field is required");
        empty = true;
    }
    if (ui->LB_categoryError->text().trimmed().isEmpty()){
        ui->LB_categoryError->setText("This field is required");
        empty = true;
    }
    if (ui->LE_stock->text().trimmed().isEmpty()){
        ui->LB_stockError->setText("This field is required");
        empty = true;
    }
    if (ui->LE_available->text().trimmed().isEmpty()){
        ui->LB_availableError->setText("This field is required");
        empty = true;
    }
    if (ui->LE_unit->text().trimmed().isEmpty()){
        ui->LB_unitError->setText("This field is required");
        empty = true;
    }

    return empty;
}

void add_product_window::addProductToInventory(){
    const std::string name = ui->LE_name->text().trimmed().toStdString();
    const std::string sku = ui->LE_SKU->text().trimmed().toStdString();
    const double price = ui->LE_price->text().trimmed().toDouble();

    const std::string brand = ui->LE_brand->text().trimmed().toStdString();
    const std::string category = ui->LE_category->text().trimmed().toStdString();

    const double stock = ui->LE_stock->text().trimmed().toDouble();
    const double available = ui->LE_available->text().trimmed().toDouble();
    const std::string unit = ui->LE_unit->text().trimmed().toStdString();

    const std::string description = ui->TE_description->toPlainText().toStdString();

    QDate qAddedDate = ui->DE_addedDate->date();
    const std::string addedDate = qAddedDate.toString("yyyy/MM/dd").toStdString();

    std::string exDate;
    if (ui->CB_expCheckBox->isChecked())
        exDate = ui->DE_exDate->date().toString("yyyy/MM/dd").toStdString();
    else
        exDate = "none";

    bool availability = ([available](){ return available > 0; })();

    Product newProduct(name, category, sku, brand, stock, available, price, unit, description, addedDate, exDate, availability);
    m_user->addProduct(newProduct);
}

void add_product_window::on_PB_addProduct_clicked()
{
    hideErrors();
    if (checkIfEmpty()){
        return;
    }
    else {
        bool skuExist = m_user->getProductsModel().existence(ui->LE_SKU->text().trimmed().toStdString());
        if (skuExist){
            ui->LB_skuError->setText("We already have a product with the provided SKU");
        }
        else{
            addProductToInventory();
            this->close();
        }
    }

}


void add_product_window::on_CB_expCheckBox_stateChanged(int arg1){
    expDateEdit();
}

