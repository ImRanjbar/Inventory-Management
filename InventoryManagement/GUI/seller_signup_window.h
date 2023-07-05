#ifndef SELLER_SIGNUP_WINDOW_H
#define SELLER_SIGNUP_WINDOW_H

#include <QDialog>
#include "../manufacturers.h"

namespace Ui {
class seller_signup_window;
}

class seller_signup_window : public QDialog
{
    Q_OBJECT

public:
    explicit seller_signup_window(Manufacturers* manufacturers,QWidget* previousWindow, QWidget *parent = nullptr);
    ~seller_signup_window();
    void hideLBs();
    void putPlaceHolders();

    bool checkEmptyLineEdits(const QString &manufacturerName, const QString &name, const QString &lastName
                               , const QString &NIN, const QString &phoneNumber, const QString &MID
                               , const QString &username, const QString &password, const QString &confirmPass);

    bool validateLineEditInput(const QString &manufacturerName, const QString &name, const QString &lastName
                               , const QString &NIN, const QString &phoneNumber, const QString &MID
                               , const QString &username, const QString &password, const QString &confirmPass);

    void signUpUser(const QString &manufacturerName, const QString &name, const QString &lastName
                , const QString &NIN, const QString &phoneNumber, const QString &MID
                , const QString &username, const QString &password);

    void signUpMessage();

    void setValidators();



private slots:
    void on_PB_login_clicked();
    void on_PB_signUp_clicked();

    void handleLoginButton();

private:
    QWidget* m_previousWindow;
    Ui::seller_signup_window *ui;
    Manufacturers* m_manufacturers;
};

#endif // SELLER_SIGNUP_WINDOW_H
