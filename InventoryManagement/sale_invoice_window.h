#ifndef SALE_INVOICE_WINDOW_H
#define SALE_INVOICE_WINDOW_H

#include "Invoice.h"
#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class sale_invoice_window;
}

class sale_invoice_window : public QDialog
{
    Q_OBJECT

public:
    explicit sale_invoice_window(Invoice& invoice,QWidget *parent = nullptr);
    ~sale_invoice_window();

    void setLabels();

    void setTableColumns();

    void addItems();

private slots:
    void on_TV_items_doubleClicked(const QModelIndex &index);

    void on_PB_print_clicked();

private:
    Ui::sale_invoice_window *ui;
    Invoice m_invoice;
    QStandardItemModel m_itemsModel;
};

#endif // SALE_INVOICE_WINDOW_H
