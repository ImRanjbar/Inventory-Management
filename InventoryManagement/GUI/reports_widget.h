#ifndef REPORTS_WIDGET_H
#define REPORTS_WIDGET_H

#include <QWidget>
#include <QStandardItemModel>

#include "../manufacturers.h"

namespace Ui {
class reports_widget;
}

class reports_widget : public QWidget
{
    Q_OBJECT

public:
    explicit reports_widget(Manufacturers* manufacturers, Seller* user,QWidget *parent = nullptr);
    ~reports_widget();
    
    void initializeTablesView();

    void updatePurchaseTable();

    void updateSoldTable();

    void setLabels();

    void setComboBoxes();

    std::string calculateFavoriteCompany(bool isPurchase);

    void search(const QString& text, bool isPurchase);

    template<typename MemberFunction>
    void updateTableViewWithSearchCriteria(const QString& text, MemberFunction memberFunction, bool isPurchase);



private slots:
    void on_TV_purchase_doubleClicked(const QModelIndex &index);

    void on_TV_solds_doubleClicked(const QModelIndex &index);

    void on_LE_purchaseSearch_textChanged(const QString &arg1);

    void on_LE_saleSearch_textChanged(const QString &arg1);

private:
    Ui::reports_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
    QStandardItemModel m_purchaseItemModel;
    QStandardItemModel m_soldItemModel;
};

#endif // REPORTS_WIDGET_H
