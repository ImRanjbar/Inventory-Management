
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
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
    if(ui->RDB_seller->isChecked() || ui->RDB_customer->isChecked()){
        qDebug() << "one of them is checked\n";
        return;
    }
    else if (true){
        ui->LB_errorSelection->setText("Select at least one of them");
        ui->LB_errorSelection->setVisible(true);
        return;
    }
}

