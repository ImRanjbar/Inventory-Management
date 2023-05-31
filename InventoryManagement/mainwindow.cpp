
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customer_signup_page.h"

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
    else if (true){
        ui->LB_errorUsername->setText("Username is incorrect");
        ui->LB_errorUsername->setVisible(true);
        return;
    }
    else if (true){
        ui->LB_errorPassword->setText("Password is incorrect");
        ui->LB_errorPassword->setVisible(true);
        return;
    }
}

void MainWindow::on_PB_signin_clicked()
{
    hideMainWindowLabels();
    if(ui->RDB_seller->isChecked()){
        qDebug() << "RDB_seller have checked\n";
        return;
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
