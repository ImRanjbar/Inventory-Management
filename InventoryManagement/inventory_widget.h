#ifndef INVENTORY_WIDGET_H
#define INVENTORY_WIDGET_H

#include "manufacturers.h"

#include <QWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QStringListModel>

namespace Ui {
class inventory_widget;
}

class inventory_widget : public QWidget
{
    Q_OBJECT

public:
    explicit inventory_widget(Manufacturers* manufacturers, Seller* user,QWidget *parent = nullptr);
    ~inventory_widget();

    void customizeListItems();

    void setSearchComboBox();

    void setTableColumns();

    void updateTable();

    void updateFilterBrand();

    void updateFilterCategory();


private slots:
    void on_TV_products_doubleClicked(const QModelIndex &index);

    void on_TV_products_activated(const QModelIndex &index);

    void on_PB_add_clicked();

    void onDialogClosed(); // ->

private:
    Ui::inventory_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    QStandardItemModel m_tableViewModel;
    QStringListModel m_brandFilterList;
    QStringListModel m_categoryFilterList;


};

#endif // INVENTORY_WIDGET_H
