#include "seller_signup_window.h"
#include "ui_seller_signup_window.h"

#include <QMessageBox>
#include <QRegularExpressionValidator>
#include "../datahandler.h"


seller_signup_window::seller_signup_window(Manufacturers* manufacturers,QWidget* previousWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seller_signup_window)
{
    m_previousWindow = previousWindow;
    m_manufacturers = manufacturers;
    ui->setupUi(this);

    this->setWindowTitle("SignUp");
    QIcon icon(":/Images/icons/signUp.png");
    this->setWindowIcon(icon);

    setValidators();

    putPlaceHolders();
    hideLBs();
}

seller_signup_window::~seller_signup_window(){
    delete ui;
}

void seller_signup_window::putPlaceHolders(){
    ui->LE_manufacturerName->setPlaceholderText("Manufacturer name");
    ui->LE_lastName->setPlaceholderText("Last name");
    ui->LE_name->setPlaceholderText("Name");
    ui->LE_NIN->setPlaceholderText("National Identification Number");
    ui->LE_phoneNumber->setPlaceholderText("Phone number");
    ui->LE_MID->setPlaceholderText("MID code");
    ui->LE_username->setPlaceholderText("Create username");
    ui->LE_password->setPlaceholderText("Create password");
    ui->LE_confirmPass->setPlaceholderText("Confirm password");
}

bool seller_signup_window::checkEmptyLineEdits(const QString& marketName, const QString& name, const QString& lastName
                                               , const QString& NIN, const QString& phoneNumber, const QString& MID
                                               , const QString& username, const QString& password, const QString& confirmPass){

    bool valid = true;

    if (marketName.isEmpty()){
        ui->LB_errorManufacturerName->setText("The market name field is required");
        ui->LB_errorManufacturerName->setVisible(true);
        valid = false;
    }
    if(name.isEmpty()){
        ui->LB_errorName->setText("The name field is required");
        ui->LB_errorName->setVisible(true);
        valid = false;
    }
    if(lastName.isEmpty()){
        ui->LB_errorLastName->setText("The last name field is required");
        ui->LB_errorLastName->setVisible(true);
        valid = false;
    }
    if(NIN.isEmpty()){
        ui->LB_errorNIN->setText("The NIN field is required");
        ui->LB_errorNIN->setVisible(true);
        valid = false;
    }
    if(phoneNumber.isEmpty()){
        ui->LB_errorPhoneNumber->setText("The phone number field is required");
        ui->LB_errorPhoneNumber->setVisible(true);
        valid = false;
    }
    if(MID.isEmpty()){
        ui->LB_errorMID->setText("The customer ID field is required");
        ui->LB_errorMID->setVisible(true);
        valid = false;
    }
    if(username.isEmpty()){
        ui->LB_errorUsername->setText("Please enter a username");
        ui->LB_errorUsername->setVisible(true);
        valid = false;
    }
    if(password.isEmpty()){
        ui->LB_errorPassword->setText("Please enter a password");
        ui->LB_errorPassword->setVisible(true);
        valid = false;
    }
    if(confirmPass.isEmpty()){
        ui->LB_errorPasswordAgain->setText("Please enter your password again");
        ui->LB_errorPasswordAgain->setVisible(true);
        valid = false;
    }

    return valid;
}

bool seller_signup_window::validateLineEditInput(const QString &manufacturerName, const QString &name, const QString &lastName
                                                 , const QString &NIN, const QString &phoneNumber, const QString &MID
                                                 , const QString &username, const QString &password, const QString &confirmPass){

    bool valid = true;

    if (m_manufacturers->usernameExistence(username.toStdString())){
        ui->LB_errorUsername->setText("The username you have chosen is already taken");
        ui->LB_errorUsername->setVisible(true);
        valid = false;
    }
    if (m_manufacturers->MIDexistence(MID.toStdString())){
        ui->LB_errorMID->setText("There is already an existing manufacturer with this MID");
        ui->LB_errorMID->setVisible(true);
        valid = false;
    }
    if(m_manufacturers->NINexistence(NIN.toStdString())){
        ui->LB_errorNIN->setText("A user with this NIN has already registered");
        ui->LB_errorNIN->setVisible(true);
        valid = false;
    }
    if(m_manufacturers->phoneNumberExistence(phoneNumber.toStdString())){
        ui->LB_errorPhoneNumber->setText("This phone number is already in use");
        ui->LB_errorPhoneNumber->setVisible(true);
        valid = false;
    }
    if (password != confirmPass){
        ui->LB_errorPasswordAgain->setText("The passwords do not match");
        ui->LB_errorPasswordAgain->setVisible(true);
        valid = false;
    }

    return valid;
}

void seller_signup_window::signUpUser(const QString &manufacturerName, const QString &name, const QString &lastName
                                  , const QString &NIN, const QString &phoneNumber, const QString &MID
                                  , const QString &username, const QString &password){
    Seller* newSeller = new Seller;
    newSeller->setName(name.toStdString());
    newSeller->setLastName(lastName.toStdString());
    newSeller->setUsername(username.toStdString());
    newSeller->setPassword(password.toStdString());
    newSeller->setPhoneNumber(phoneNumber.toStdString());
    newSeller->setManufactureName(manufacturerName.toStdString());
    newSeller->setMID(MID.toStdString());
    newSeller->setNIN(NIN.toStdString());

    m_manufacturers->addManufact(newSeller);

    DataHandler data;
    data.addUser(newSeller);
}

void seller_signup_window::signUpMessage(){
    QMessageBox* message = new QMessageBox(this);

    message->setWindowTitle("Sign Up");
    message->setText("Sign up successful!");
    message->setIcon(QMessageBox::Information);

    QPushButton* loginButton = message->addButton("Login",QMessageBox::AcceptRole);

    message->show();

    // Connect the clicked() signal of the loginButton to a slot function
    connect(loginButton, &QPushButton::clicked, this, &seller_signup_window::handleLoginButton);

}

void seller_signup_window::setValidators(){
    QIntValidator* intValidator = new QIntValidator(ui->LE_NIN);
    ui->LE_NIN->setValidator(intValidator);

    QRegularExpression regex("[A-Za-z0-9._]*");
    QValidator* validator = new QRegularExpressionValidator(regex, ui->LE_username);
    ui->LE_username->setValidator(validator);
    ui->LE_password->setValidator(validator);
    ui->LE_confirmPass->setValidator(validator);

    QValidator* phoneValidator = new QRegularExpressionValidator(QRegularExpression("[0-9+]*"), ui->LE_username);
    ui->LE_phoneNumber->setValidator(phoneValidator);
}

void seller_signup_window::hideLBs(){
    ui->LB_errorManufacturerName->setVisible(false);
    ui->LB_errorName->setVisible(false);
    ui->LB_errorLastName->setVisible(false);
    ui->LB_errorNIN->setVisible(false);
    ui->LB_errorPhoneNumber->setVisible(false);
    ui->LB_errorMID->setVisible(false);
    ui->LB_errorUsername->setVisible(false);
    ui->LB_errorPassword->setVisible(false);
    ui->LB_errorPasswordAgain->setVisible(false);
}

void seller_signup_window::on_PB_login_clicked(){
    this->deleteLater();
    m_previousWindow->show();

}

void seller_signup_window::on_PB_signUp_clicked()
{
    hideLBs();
    QString manufacturerName = ui->LE_manufacturerName->text().trimmed();
    QString name = ui->LE_name->text().trimmed();
    QString lastName = ui->LE_lastName->text().trimmed();
    QString NIN = ui->LE_NIN->text().trimmed();
    QString phoneNumber = ui->LE_phoneNumber->text().trimmed();
    QString MID = ui->LE_MID->text().trimmed();
    QString username = ui->LE_username->text().trimmed();
    QString password = ui->LE_password->text().trimmed();
    QString confirmPass = ui->LE_confirmPass->text().trimmed();

    if (checkEmptyLineEdits(manufacturerName, name, lastName, NIN, phoneNumber, MID, username, password, confirmPass)){
        if(validateLineEditInput(manufacturerName, name, lastName, NIN, phoneNumber, MID, username, password, confirmPass)){
            signUpUser(manufacturerName, name, lastName, NIN, phoneNumber, MID, username, password);
            signUpMessage();
        }
    }

}

void seller_signup_window::handleLoginButton(){
    this->deleteLater();
    m_previousWindow->show();
}

