#include "invoice_widget.h"
#include "ui_invoice_widget.h"
#include <QDate>
#include "currency.h"

invoice_widget::invoice_widget(Manufacturers *manufacturer, Seller *user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::invoice_widget)
{
    ui->setupUi(this);

    m_manufacturers = manufacturer;
    m_user = user;
    if (m_user->getInvoice().getProviderID() != ""){
        qDebug() << "the provide ID is " << m_user->getInvoice().getProviderID() << '\n';
        m_provider = m_manufacturers->editSellerByMID(m_user->getInvoice().getProviderID());
    }
    setTableColumns();
    setLabels();
}

invoice_widget::~invoice_widget()
{
    qDebug() << "invoice_widget destructure\n";
    delete ui;
}

void invoice_widget::setTableColumns(){
    qDebug() << "Set table columns func\n";
    m_tableViewModel.setHorizontalHeaderItem(0 ,new QStandardItem("SKU"));
    m_tableViewModel.setHorizontalHeaderItem(1 ,new QStandardItem("Name"));
    m_tableViewModel.setHorizontalHeaderItem(2 ,new QStandardItem("Brand"));
    m_tableViewModel.setHorizontalHeaderItem(3 ,new QStandardItem("Category"));
    m_tableViewModel.setHorizontalHeaderItem(4 ,new QStandardItem("Price"));
    m_tableViewModel.setHorizontalHeaderItem(5 ,new QStandardItem("Selected"));
    m_tableViewModel.setHorizontalHeaderItem(6 ,new QStandardItem("Unit"));
    m_tableViewModel.setHorizontalHeaderItem(7 ,new QStandardItem("Expration Date"));

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
        else if (column == 6)
            ui->TV_items->setColumnWidth(column, 80);
        else
            ui->TV_items->setColumnWidth(column, columnWidth);
    }

}

void invoice_widget::setLabels(){
    QDate currentDate = QDate::currentDate();
    ui->LB_invoiceDate->setText(currentDate.toString("yyyy/MM/dd"));
    m_user->editInvoice().setDate(currentDate.toString("yyyy/MM/dd").toStdString());

    ui->LB_error->setVisible(false);

    std::string providerID = m_user->getInvoice().getProviderID();

    if ( !providerID.empty()){
        ui->LB_invoiceNumber->setText("INV-" + QString::number(m_user->getInvoice().getInvoiceNumber()));

        Seller provider = m_manufacturers->getSellerByMID(providerID);
        ui->LB_manuName->setText(QString::fromStdString(m_manufacturers->getSellerByMID(providerID).getManufactureName()));
        ui->LB_MID->setText(QString::fromStdString(providerID));

        m_user->editInvoice().updateAmount();
        ui->LB_amountDue->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(m_user->getInvoice().getTotalAmount(), 'f', 2));

        m_user->editInvoice().updateNumSelectedItems();
        ui->LB_nSellected->setText(QString::number(m_user->getInvoice().getNumSelectedItems()));

        updateTable();

    }
    else {
        ui->LB_manuName->setText("NOT SELECTED");
        ui->LB_MID->setText("NOT SELECTED");
        ui->LB_nSellected->setText("0");
        ui->LB_amountDue->setText(QString::fromStdString(Currency::currencySymbol) + "0");
    }

}

void invoice_widget::updateTable(){
    const std::vector<InvoiceItem>& items = m_user->getInvoice().getInvoiceItemModel().getItems();

    clearTable();

    int row = 0;
    for (const InvoiceItem& item : items){
        QStandardItem* SKU = new QStandardItem(QString::fromStdString(item.getSku()));
        SKU->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        m_tableViewModel.setItem(row,0 ,SKU);
        m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
        m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
        m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
        m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
        m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
        m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::fromStdString(item.getUnit())));
        m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getExDate())));
        row++;
    }

    ui->LE_search->setText("");
    qDebug() << "updateTable func done\n ";
}

void invoice_widget::clearTable(){
    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());
}

void invoice_widget::clear(){
    m_user->editInvoice().clearInvoice();
    updateTable();

    ui->LB_amountDue->setText(QString::fromStdString(Currency::currencySymbol) + "0");
    ui->LB_nSellected->setText("0");
}



void invoice_widget::on_PB_purchase_clicked(){
    if (m_user->getInvoice().getInvoiceItemModel().getItems().size() == 0){
        ui->LB_error->setText("You Haven't select any item");
        ui->LB_error->setVisible(true);
    }
    else {
        m_user->purchase();
        m_provider->sold(m_user->getInvoice());
        m_user->editInvoice().clearInvoice();

        setTableColumns();
        setLabels();
        updateTable();
    }
}


void invoice_widget::on_PB_clear_clicked(){
    clear();
}

