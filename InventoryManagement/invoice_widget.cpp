#include "invoice_widget.h"
#include "ui_invoice_widget.h"

invoice_widget::invoice_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::invoice_widget)
{
    ui->setupUi(this);
}

invoice_widget::~invoice_widget()
{
    delete ui;
}
