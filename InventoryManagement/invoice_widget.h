#ifndef INVOICE_WIDGET_H
#define INVOICE_WIDGET_H

#include <QWidget>

namespace Ui {
class invoice_widget;
}

class invoice_widget : public QWidget
{
    Q_OBJECT

public:
    explicit invoice_widget(QWidget *parent = nullptr);
    ~invoice_widget();

private:
    Ui::invoice_widget *ui;
};

#endif // INVOICE_WIDGET_H
