#ifndef PURCHASE_WIDGET_H
#define PURCHASE_WIDGET_H

#include "manufacturers.h"

#include <QWidget>
#include <QPainter>
#include <QStyledItemDelegate>

namespace Ui {
class purchase_widget;
}

class purchase_widget : public QWidget
{
    Q_OBJECT

public:
    explicit purchase_widget(Manufacturers* manufacturers, Seller* user ,QWidget *parent = nullptr);
    ~purchase_widget();

private:
    Ui::purchase_widget *ui;
    Manufacturers* m_manufacturers;
    Seller* m_user;
};

#endif // PURCHASE_WIDGET_H
