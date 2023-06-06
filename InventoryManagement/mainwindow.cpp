
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "customer_signup_page.h"
#include "seller_signup_window.h"
#include "home_window.h"

#include <QString>

MainWindow::MainWindow(Manufacturers* data, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_manufacturers = data;
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
    // save data *******************
    delete ui;
}

void MainWindow::on_PB_login_clicked()
{
    hideMainWindowLabels();
    QString username = ui->LE_username->text().trimmed();
    QString password = ui->LE_password->text().trimmed();

    if (m_manufacturers->usernameExistence(username.toStdString()) && !password.isEmpty()){
        qDebug() << "_PBLogin_username is " << username << '\n';
        if (m_manufacturers->checkPassword(username.toStdString(),password.toStdString())){
            qDebug() << "_PBLogin__password is " << password << '\n';
            Seller* user = m_manufacturers->editSeller(username.toStdString());
            qDebug() << "user name is " << user->getName() << '\n';
            home_window* homeWindow = new home_window(m_manufacturers, user, this);
            close();
            homeWindow->show();
        }
        else {
            qDebug() << "_PBLogin__password is " << password << '\n';
            ui->LB_errorPassword->setText("Password is incorrect");
            ui->LB_errorPassword->setVisible(true);
        }
    }
    else {
        if (username.isEmpty()){
            qDebug() << "_PBLogin_username is " << username << '\n';
            ui->LB_errorUsername->setText("This field is required");
            ui->LB_errorUsername->setVisible(true);
        }
//        else if (!username.isEmpty()){
////            if (!m_manufacturers->usernameExistence(username.toStdString())){
////                qDebug() << "_PBLogin_username is " << username << '\n';
////                ui->LB_errorUsername->setText("Incorrect username");
////                ui->LB_errorUsername->setVisible(true);
//            }
        if (password.isEmpty()){
            qDebug() << "_PBLogin__password is " << password << '\n';
            ui->LB_errorPassword->setText("This field is required");
            ui->LB_errorPassword->setVisible(true);
        }
        else {
            qDebug() << "_PBLogin__password is " << password << '\n';
            ui->LB_errorPassword->setText("Incorrect password");
            ui->LB_errorPassword->setVisible(true);
        }
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
