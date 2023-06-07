#ifndef INVOICE_WIDGET_H
#define INVOICE_WIDGET_H

#include <QWidget>
#include <QStandardItem>

namespace Ui {
class invoice_widget;
}

class invoice_widget : public QWidget
{
    Q_OBJECT

public:
    explicit invoice_widget(QWidget *parent = nullptr);
    ~invoice_widget();

    void setTableColumns();

private:
    Ui::invoice_widget *ui;
    QStandardItemModel m_tableViewModel;
};

#endif // INVOICE_WIDGET_H
