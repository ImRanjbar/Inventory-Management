#include "invoice_widget.h"
#include "ui_invoice_widget.h"

invoice_widget::invoice_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::invoice_widget)
{
    ui->setupUi(this);

    setTableColumns();
}

invoice_widget::~invoice_widget()
{
    qDebug() << "invoice_widget destructure\n";
    delete ui;
}

void invoice_widget::setTableColumns(){
    m_tableViewModel.setHorizontalHeaderItem(0 ,new QStandardItem("SKU"));
    m_tableViewModel.setHorizontalHeaderItem(1 ,new QStandardItem("Name"));
    m_tableViewModel.setHorizontalHeaderItem(2 ,new QStandardItem("Brand"));
    m_tableViewModel.setHorizontalHeaderItem(3 ,new QStandardItem("Category"));
    m_tableViewModel.setHorizontalHeaderItem(4 ,new QStandardItem("Price"));
    m_tableViewModel.setHorizontalHeaderItem(5 ,new QStandardItem("Selected"));
    m_tableViewModel.setHorizontalHeaderItem(6 ,new QStandardItem("Expration Date"));

    ui->TV_items->setModel(&m_tableViewModel);
    ui->TV_items->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    ui->TV_products->setCursor(Qt::PointingHandCursor);
    ui->TV_items->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // Set the size of each column
    const int numColumns = 9;
    const int columnWidth = 100;
    for (int column = 0; column < numColumns; ++column) {
        if (column == 4 || column == 5)
            ui->TV_items->setColumnWidth(column, 70);
        else
            ui->TV_items->setColumnWidth(column, columnWidth);
    }

}
