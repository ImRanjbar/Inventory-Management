#ifndef PRODUCT_INFORMATION_WINDOW_H
#define PRODUCT_INFORMATION_WINDOW_H

#include <QDialog>
#include "../seller.h"

namespace Ui {
class product_information_window;
}

class product_information_window : public QDialog
{
    Q_OBJECT

public:
    explicit product_information_window(Seller* user, const InvoiceItem* item,QWidget *parent = nullptr);
    explicit product_information_window(const InvoiceItem* item,QWidget *parent = nullptr);
    ~product_information_window();

    void setLabels();

    void invoiceSetLabels();

private:
    Ui::product_information_window *ui;
    const InvoiceItem* m_item;
    const Seller* m_user;
};

#endif // INFORMATION_WINDOW_H
