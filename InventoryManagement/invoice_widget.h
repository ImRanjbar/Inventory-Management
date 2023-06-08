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

private:
    Ui::invoice_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    QStandardItemModel m_tableViewModel;
};

#endif // INVOICE_WIDGET_H
