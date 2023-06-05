#ifndef INVENTORY_WIDGET_H
#define INVENTORY_WIDGET_H

#include <QWidget>

#include <QPainter>
#include <QStyledItemDelegate>

namespace Ui {
class inventory_widget;
}

class inventory_widget : public QWidget
{
    Q_OBJECT

public:
    explicit inventory_widget(QWidget *parent = nullptr);
    ~inventory_widget();

private:
    Ui::inventory_widget *ui;
};

#endif // INVENTORY_WIDGET_H
