#ifndef CURRENCY_WIDGET_H
#define CURRENCY_WIDGET_H

#include <QWidget>

namespace Ui {
class currency_widget;
}

class currency_widget : public QWidget
{
    Q_OBJECT

public:
    explicit currency_widget(QWidget *parent = nullptr);
    ~currency_widget();

private:
    Ui::currency_widget *ui;
};

#endif // CURRENCY_WIDGET_H
