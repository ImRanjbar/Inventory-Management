#ifndef INVENTORY_WIDGET_H
#define INVENTORY_WIDGET_H

#include "manufacturers.h"
#include "ui_inventory_widget.h"

#include <QWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QItemSelection>

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

    void removeProduct(int row);

    void updateTableBrand(const std::string_view brand);

    void updateTableCategory(const std::string_view category);

    void search(const QString& text);

    void searchByName(const QString& text);
    void searchBySKU(const QString& text);
    void searchByCategory(const QString& text);
    void searchByBrand(const QString& text);
    void searchByUnit(const QString& text);


private slots:
    void on_TV_products_doubleClicked(const QModelIndex &index);

    void on_TV_products_activated(const QModelIndex &index);

    void on_PB_add_clicked();

    void onDialogClosed(); // ->

    void on_PB_remove_clicked();

    void on_PB_brandFilter_clicked();

    void onSelectionChangedBrands(const QItemSelection& selected, const QItemSelection& deselected);

    void onSelectionChangedCategories(const QItemSelection& selected, const QItemSelection& deselected);

    void on_PB_categoryFilter_clicked();

    void handleHeaderDoubleClicked(int logicalIndex);

    void handleHeaderClicked(int logicalIndex);

    void onTextChanged(const QString& text);

private:
    Ui::inventory_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    QStandardItemModel m_tableViewModel;
    QStringListModel m_brandFilterList;
    QStringListModel m_categoryFilterList;




};

#endif // INVENTORY_WIDGET_H
