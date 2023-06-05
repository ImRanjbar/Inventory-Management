#ifndef SELLER_SIGNUP_WINDOW_H
#define SELLER_SIGNUP_WINDOW_H

#include <QDialog>
#include <qDebug>

namespace Ui {
class seller_signup_window;
}

class seller_signup_window : public QDialog
{
    Q_OBJECT

public:
    explicit seller_signup_window(QWidget* previouseWindow, QWidget *parent = nullptr);
    ~seller_signup_window();
    void hideLBs();
    void putPlaceHolders();


private slots:
    void on_PB_login_clicked();
    void on_PB_signUp_clicked();

private:
    QWidget* m_previouseWindow;
    Ui::seller_signup_window *ui;
};

#endif // SELLER_SIGNUP_WINDOW_H
