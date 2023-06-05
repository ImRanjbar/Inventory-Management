#include "reports_widget.h"
#include "ui_reports_widget.h"

reports_widget::reports_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reports_widget)
{
    ui->setupUi(this);
}

reports_widget::~reports_widget()
{
    delete ui;
}
