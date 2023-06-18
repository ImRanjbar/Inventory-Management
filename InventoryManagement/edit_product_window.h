#ifndef EDIT_PRODUCT_WINDOW_H
#define EDIT_PRODUCT_WINDOW_H
#include "seller.h"
#include <QDialog>

namespace Ui {
class edit_product_window;
}

class edit_product_window : public QDialog
{
    Q_OBJECT

public:
    explicit edit_product_window(Seller* user,Product* product,QWidget *parent = nullptr);
    ~edit_product_window();

    void resetLabels();

    void hideError();

    bool isEmpty();

    bool skuValidation(const QString& desired);

    void editProduct();

    void savedMessage();

signals:
    void windowClosed();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_PB_reset_clicked();

    void on_PB_cancel_clicked();

    void on_PB_delete_clicked();

    void on_PB_save_clicked();

private:
    Ui::edit_product_window *ui;
    Seller* m_user;
    Product* m_product;
};

#endif // EDIT_PRODUCT_WINDOW_H
