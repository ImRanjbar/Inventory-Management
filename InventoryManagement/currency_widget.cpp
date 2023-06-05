#include "currency_widget.h"
#include "ui_currency_widget.h"

currency_widget::currency_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::currency_widget)
{
    ui->setupUi(this);
}

currency_widget::~currency_widget()
{
    delete ui;
}
