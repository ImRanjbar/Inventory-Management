#ifndef ADD_PRODUCT_WINDOW_H
#define ADD_PRODUCT_WINDOW_H
#include "seller.h"
#include <QDialog>

namespace Ui {
class add_product_window;
}

class add_product_window : public QDialog
{
    Q_OBJECT

public:
    explicit add_product_window(Seller* user, QWidget *parent = nullptr);
    ~add_product_window();

    void hideErrors();

    void expDateEdit();

    bool checkIfEmpty();

    void addProductToInventory();

signals :
    void dialogClosed();

private slots:
    void on_PB_addProduct_clicked();

    void on_CB_expCheckBox_stateChanged(int arg1);

    void on_PB_cancel_clicked();

private:
    Ui::add_product_window *ui;
    QWidget* m_parent;
    Seller* m_user;
};

#endif // ADD_PRODUCT_WINDOW_H
