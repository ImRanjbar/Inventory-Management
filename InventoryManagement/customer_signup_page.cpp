#include "customer_signup_page.h"
#include "ui_customer_signup_page.h"

customer_signup_page::customer_signup_page(QWidget* previousWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customer_signup_page)
{
    m_previouseWindow = previousWindow;
    ui->setupUi(this);

    putPlaceHolders();
    hideLBs();
}

customer_signup_page::~customer_signup_page()
{
    qDebug() << "customer_signup_page destructure\n";
    delete ui;
}

void customer_signup_page::putPlaceHolders(){
    ui->LE_lastName->setPlaceholderText("Last name");
    ui->LE_name->setPlaceholderText("Name");
    ui->LE_NIN->setPlaceholderText("National Identification Number");
    ui->LE_phoneNumber->setPlaceholderText("Phone number");
    ui->LE_customerID->setPlaceholderText("Creat customerID");
    ui->LE_username->setPlaceholderText("Create username");
    ui->LE_password->setPlaceholderText("Create password");
    ui->LE_passwordAgain->setPlaceholderText("Enter password again");
}

void customer_signup_page::hideLBs(){
    ui->LB_errorName->setVisible(false);
    ui->LB_errorLastName->setVisible(false);
    ui->LB_errorNIN->setVisible(false);
    ui->LB_errorPhoneNumber->setVisible(false);
    ui->LB_errorCustomerID->setVisible(false);
    ui->LB_errorUsername->setVisible(false);
    ui->LB_errorPassword->setVisible(false);
    ui->LB_errorPasswordAgain->setVisible(false);
}

void customer_signup_page::on_PB_signUp_clicked(){
    hideLBs();
    QString name = ui->LE_name->text();
    QString lastName = ui->LE_lastName->text();
    QString NIN = ui->LE_NIN->text();
    QString phoneNumber = ui->LE_phoneNumber->text();
    QString customerID = ui->LE_customerID->text();
    QString username = ui->LE_username->text();
    QString password = ui->LE_password->text();
    QString password_ = ui->LE_passwordAgain->text();

    if(name.isEmpty()){
        ui->LB_errorName->setText("The name field is required");
        ui->LB_errorName->setVisible(true);
    }
    if(lastName.isEmpty()){
        ui->LB_errorLastName->setText("The last name field is required");
        ui->LB_errorLastName->setVisible(true);
    }
    if(NIN.isEmpty()){
        ui->LB_errorNIN->setText("The NIN field is required");
        ui->LB_errorNIN->setVisible(true);
    }
    if(phoneNumber.isEmpty()){
        ui->LB_errorPhoneNumber->setText("The phone number field is required");
        ui->LB_errorPhoneNumber->setVisible(true);
    }
    if(customerID.isEmpty()){
        ui->LB_errorCustomerID->setText("The customer ID field is required");
        ui->LB_errorCustomerID->setVisible(true);
    }
    if(username.isEmpty()){
        ui->LB_errorUsername->setText("Please enter a username");
        ui->LB_errorUsername->setVisible(true);
    }
    if(password.isEmpty()){
        ui->LB_errorPassword->setText("Please enter a password");
        ui->LB_errorPassword->setVisible(true);
    }
    if(password_.isEmpty()){
        ui->LB_errorPasswordAgain->setText("Please enter your password again");
        ui->LB_errorPasswordAgain->setVisible(true);
    }
    // add else if for search!


}


void customer_signup_page::on_PB_login_clicked()
{
    this->deleteLater();
    this->m_previouseWindow->show();
}

