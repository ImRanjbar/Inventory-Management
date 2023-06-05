
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customer_signup_page.h"
#include "seller_signup_window.h"
#include "home_window.h"

#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hideMainWindowLabels();
}

void MainWindow::hideMainWindowLabels(){
    ui->LB_errorSelection->setVisible(false);
    ui->LB_errorPassword->setVisible(false);
    ui->LB_errorUsername->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_login_clicked()
{
    hideMainWindowLabels();
    QString username = ui->LE_username->text();
    QString password = ui->LE_password->text();
    if (false){
        return;
    }
    else if (false){
        ui->LB_errorUsername->setText("Username is incorrect");
        ui->LB_errorUsername->setVisible(true);
        return;
    }
    else if (false){
        ui->LB_errorPassword->setText("Password is incorrect");
        ui->LB_errorPassword->setVisible(true);
        return;
    }
    else {
        home_window* homeWindow = new home_window(this);
        close();
        homeWindow->show();
    }
}

void MainWindow::on_PB_signin_clicked()
{
    hideMainWindowLabels();
    if(ui->RDB_seller->isChecked()){
        seller_signup_window* sellerSignUpWindow = new seller_signup_window(this);
        close();
        sellerSignUpWindow->show();
    }
    else if (ui->RDB_customer->isChecked()){
        customer_signup_page* customerSignUpPage = new customer_signup_page(this);
        close();
        customerSignUpPage->show();
    }
    else if (true){
        ui->LB_errorSelection->setText("Select at least one of them");
        ui->LB_errorSelection->setVisible(true);
        return;
    }
}
