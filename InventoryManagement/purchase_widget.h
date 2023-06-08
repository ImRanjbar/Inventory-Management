#ifndef PURCHASE_WIDGET_H
#define PURCHASE_WIDGET_H

#include "manufacturers.h"

#include <QWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QStringListModel>

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

private slots:
    void on_CB_providers_currentTextChanged(const QString &arg1);

    void on_PB_addToInvoice_clicked();

    void onAddToInvoiceDialogClosed();

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
