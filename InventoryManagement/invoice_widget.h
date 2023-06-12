#ifndef INVOICE_WIDGET_H
#define INVOICE_WIDGET_H

#include "manufacturers.h"

#include <QWidget>
#include <QStandardItem>

namespace Ui {
class invoice_widget;
}

class invoice_widget : public QWidget
{
    Q_OBJECT

public:
    explicit invoice_widget(Manufacturers* manufacturer, Seller* user,QWidget *parent = nullptr);
    ~invoice_widget();

    void setTableColumns();

    void setLabels();

    void updateTable();

    void clearTable();

    void clear();

private slots:
    void on_PB_purchase_clicked();

    void on_PB_clear_clicked();

private:
    Ui::invoice_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    Seller* m_provider;
    QStandardItemModel m_tableViewModel;
};

#endif // INVOICE_WIDGET_H
