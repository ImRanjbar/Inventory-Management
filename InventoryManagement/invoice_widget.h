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

    void initializeTableView();

    void setLabels();

    void setComboBox();

    void updateTable();

    void clearTable();

    void clear();

    void search(const QString& text);

    template <typename MemberFunction>
    void updateTableViewWithSearchCriteria(const QString& text, MemberFunction memberFunction);

private slots:
    void on_PB_purchase_clicked();

    void on_PB_clear_clicked();

    void on_PB_remove_clicked();

    void on_LE_search_textChanged(const QString &arg1);

private:
    Ui::invoice_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    Seller* m_provider;
    QStandardItemModel m_tableViewModel;
};

#endif // INVOICE_WIDGET_H
