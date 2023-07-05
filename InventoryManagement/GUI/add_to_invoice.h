#ifndef ADD_TO_INVOICE_H
#define ADD_TO_INVOICE_H

#include <QDialog>

#include "../seller.h"

namespace Ui {
class add_to_invoice;
}

class add_to_invoice : public QDialog
{
    Q_OBJECT

public:
    explicit add_to_invoice(Seller* user, Seller* provider, InvoiceItem* item, QWidget *parent = nullptr);
    ~add_to_invoice();

    void setLabels();

    void addItem();

signals:
    void dialogClosed();


private slots:
    void on_LE_selected_textChanged(const QString &arg1);

    void on_PB_add_clicked();

    void on_PB_cancel_clicked();

private:
    Ui::add_to_invoice *ui;
    Seller* m_user;
    Seller* m_provider;
    InvoiceItem* m_item;
    bool m_itemExistence;

};

#endif // ADD_TO_INVOICE_H
