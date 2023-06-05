#include "seller_signup_window.h"
#include "ui_seller_signup_window.h"

seller_signup_window::seller_signup_window(MainWindow* previouseWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seller_signup_window)
{
    m_previouseWindow = previouseWindow;
    ui->setupUi(this);

    putPlaceHolders();
    hideLBs();
}

void seller_signup_window::putPlaceHolders(){
    ui->LE_marketName->setPlaceholderText("Market name");
    ui->LE_lastName->setPlaceholderText("Last name");
    ui->LE_name->setPlaceholderText("Name");
    ui->LE_NIN->setPlaceholderText("National Identification Number");
    ui->LE_phoneNumber->setPlaceholderText("Phone number");
    ui->LE_sellerID->setPlaceholderText("Creat customerID");
    ui->LE_username->setPlaceholderText("Create username");
    ui->LE_password->setPlaceholderText("Create password");
    ui->LE_passwordAgain->setPlaceholderText("Enter password again");
}

void seller_signup_window::hideLBs(){
    ui->LB_errorMarketName->setVisible(false);
    ui->LB_errorName->setVisible(false);
    ui->LB_errorLastName->setVisible(false);
    ui->LB_errorNIN->setVisible(false);
    ui->LB_errorPhoneNumber->setVisible(false);
    ui->LB_errorSellerID->setVisible(false);
    ui->LB_errorUsername->setVisible(false);
    ui->LB_errorPassword->setVisible(false);
    ui->LB_errorPasswordAgain->setVisible(false);
}


seller_signup_window::~seller_signup_window()
{
    delete ui;
}

void seller_signup_window::on_PB_login_clicked()
{
    close();
    m_previouseWindow->show();

}


void seller_signup_window::on_PB_signUp_clicked()
{
    hideLBs();
    QString marketName = ui->LE_marketName->text();
    QString name = ui->LE_name->text();
    QString lastName = ui->LE_lastName->text();
    QString NIN = ui->LE_NIN->text();
    QString phoneNumber = ui->LE_phoneNumber->text();
    QString customerID = ui->LE_sellerID->text();
    QString username = ui->LE_username->text();
    QString password = ui->LE_password->text();
    QString password_ = ui->LE_passwordAgain->text();

    if (marketName.isEmpty()){
        ui->LB_errorMarketName->setText("The market name field is required");
        ui->LB_errorMarketName->setVisible(true);
    }
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
        ui->LB_errorSellerID->setText("The customer ID field is required");
        ui->LB_errorSellerID->setVisible(true);
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
}

