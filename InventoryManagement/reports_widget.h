#ifndef REPORTS_WIDGET_H
#define REPORTS_WIDGET_H

#include <QWidget>

namespace Ui {
class reports_widget;
}

class reports_widget : public QWidget
{
    Q_OBJECT

public:
    explicit reports_widget(QWidget *parent = nullptr);
    ~reports_widget();

private:
    Ui::reports_widget *ui;
};

#endif // REPORTS_WIDGET_H
