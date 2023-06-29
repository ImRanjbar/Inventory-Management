#ifndef REPORTS_WIDGET_H
#define REPORTS_WIDGET_H

#include <QWidget>
#include <QStandardItemModel>

#include "manufacturers.h"

namespace Ui {
class reports_widget;
}

class reports_widget : public QWidget
{
    Q_OBJECT

public:
    explicit reports_widget(Manufacturers* manufacturers, Seller* user,QWidget *parent = nullptr);
    ~reports_widget();

    void setTableColumns();

    void updatePurchaseTable();

    void updateSoldTable();

    void setLabels();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_TV_purchase_doubleClicked(const QModelIndex &index);

    void on_TV_solds_doubleClicked(const QModelIndex &index);

private:
    Ui::reports_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    QStandardItemModel m_purchaseItemModel;
    QStandardItemModel m_soldItemModel;
};

#endif // REPORTS_WIDGET_H
