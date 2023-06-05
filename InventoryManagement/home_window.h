#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include <QDialog>

#include "manufacturers.h"
#include "seller.h"
#include "inventory_widget.h"
#include "purchase_widget.h"
#include "reports_widget.h"
#include "currency_widget.h"
#include "invoice_widget.h"

namespace Ui {
class home_window;
}

class home_window : public QDialog
{
    Q_OBJECT

public:
    explicit home_window(Manufacturers* manufacturers, Seller* user, QWidget *parent = nullptr);
    ~home_window();

private slots:

    void setPushButtonDefaultStyle(QPushButton* button, const QString& iconPath);

    void setPushButtonSelectedtStyle(QPushButton* button, const QString& iconPath);

    void pushButtonsDefaultStyle();

    void closeWidgets();

    void closeChildWidget(QWidget* parent, const QString& widgetName);

    void on_PB_inventory_clicked();

    void on_PB_purchase_clicked();

    void on_PB_reports_clicked();

    void on_PB_currency_clicked();

    void on_PB_invoice_clicked();

    void setLabels();


private:
    Ui::home_window *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
};

#endif // HOME_WINDOW_H
