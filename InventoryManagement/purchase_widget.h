#ifndef PURCHASE_WIDGET_H
#define PURCHASE_WIDGET_H

#include "manufacturers.h"

#include <QWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QItemSelection>

namespace Ui {
class purchase_widget;
}

class purchase_widget : public QWidget
{
    Q_OBJECT

public:
    explicit purchase_widget(Manufacturers* manufacturers, Seller* user ,QWidget *parent = nullptr);
    ~purchase_widget();

    void customizeListItems();

    void setSearchComboBox();

    void setProvidersComboBox();

    void setTableColumns();

    void updateTable();

    void updateFilterBrand();

    void updateFilterCategory();

    void addItemToInvoice(int row);

    void search(const QString& text);

    void searchByName(const QString& text);
    void searchBySKU(const QString& text);
    void searchByCategory(const QString& text);
    void searchByBrand(const QString& text);
    void searchByUnit(const QString& text);

    void filterByBrand(const QString& brand);
    void filterByCategory(const QString& category);

private slots:
    void on_CB_providers_currentTextChanged(const QString &arg1);

    void on_PB_addToInvoice_clicked();

    void onAddToInvoiceDialogClosed();

    void on_LE_searchBar_textChanged(const QString &arg1);

    void on_PB_brand_clicked();

    void on_PB_category_clicked();

    void onSelectionChangedBrands(const QItemSelection& selected, const QItemSelection& deselected);

    void onSelectionChangedCategories(const QItemSelection& selected, const QItemSelection& deselected);

private:
    Ui::purchase_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    QStandardItemModel m_tableViewModel;
    QStringListModel m_brandFilterList;
    QStringListModel m_categoryFilterList;
    Seller* m_provider;
};

#endif // PURCHASE_WIDGET_H
