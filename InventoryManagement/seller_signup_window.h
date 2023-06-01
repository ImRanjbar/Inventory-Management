#ifndef SELLER_SIGNUP_WINDOW_H
#define SELLER_SIGNUP_WINDOW_H

#include <QDialog>
#include <qDebug>
#include "mainwindow.h"

namespace Ui {
class seller_signup_window;
}

class seller_signup_window : public QDialog
{
    Q_OBJECT

public:
    explicit seller_signup_window(MainWindow* previouseWindow, QWidget *parent = nullptr);
    ~seller_signup_window();
    void hideLBs();
    void putPlaceHolders();


private slots:
    void on_PB_login_clicked();
    void on_PB_signUp_clicked();

private:
    MainWindow* m_previouseWindow;
    Ui::seller_signup_window *ui;
};

#endif // SELLER_SIGNUP_WINDOW_H
