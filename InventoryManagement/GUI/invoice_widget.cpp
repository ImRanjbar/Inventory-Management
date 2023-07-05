#include "invoice_widget.h"
#include "qstyleditemdelegate.h"
#include "ui_invoice_widget.h"
#include <QDate>
#include "../currency.h"
#include "../datahandler.h"

invoice_widget::invoice_widget(Manufacturers *manufacturer, Seller *user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::invoice_widget)
{
    ui->setupUi(this);

    m_manufacturers = manufacturer;
    m_user = user;
    if (m_user->getInvoice().getProviderID() != ""){
        m_provider = m_manufacturers->editSellerByMID(m_user->getInvoice().getProviderID());
    }
    initializeTableView();
    setLabels();
}

invoice_widget::~invoice_widget()
{
    delete ui;
}

void invoice_widget::initializeTableView(){
    // Custom delegate for center-aligned text
    class CenterAlignmentDelegate : public QStyledItemDelegate {
    public:
        explicit CenterAlignmentDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

        void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
            QStyleOptionViewItem centeredOption = option;
            centeredOption.displayAlignment = Qt::AlignCenter;

            QStyledItemDelegate::paint(painter, centeredOption, index);
        }
    };

    // Create and set the custom delegate for center alignment
    ui->TV_items->setItemDelegate(new CenterAlignmentDelegate(ui->TV_items));

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
    ui->TV_items->setSelectionMode(QAbstractItemView::SingleSelection);
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

        ui->LB_nSellected->setText(QString::number(m_user->getInvoice().getInvoiceItemModel().getItems().size()));

        updateTable();
        ui->LE_search->setText("");
        setComboBox();
    }
    else {
        ui->LB_manuName->setText("NOT SELECTED");
        ui->LB_MID->setText("NOT SELECTED");
        ui->LB_invoiceNumber->setText("INV-0");
        ui->LB_nSellected->setText("0");
        ui->LB_amountDue->setText(QString::fromStdString(Currency::currencySymbol) + "0");
    }
}

void invoice_widget::setComboBox(){
    ui->CB_searchBy->addItem("Name");
    ui->CB_searchBy->addItem("SKU");
    ui->CB_searchBy->addItem("Category");
    ui->CB_searchBy->addItem("Brand");
    ui->CB_searchBy->addItem("Unit");
}

void invoice_widget::updateTable(){
    const std::vector<InvoiceItem>& items = m_user->getInvoice().getInvoiceItemModel().getItems();

    clearTable();

    int row = 0;
    for (const InvoiceItem& item : items){
        m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
        m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
        m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
        m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
        m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
        m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
        m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::fromStdString(item.getUnit())));
        m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getExDate())));
        row++;
    }
}

void invoice_widget::clearTable(){
    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());
}

void invoice_widget::clear(){
    m_user->editInvoice().clearInvoice();
    updateTable();

    ui->LE_search->setText("");
    ui->LB_manuName->setText("NOT SELECTED");
    ui->LB_MID->setText("NOT SELECTED");
    ui->LB_invoiceNumber->setText("INV-0");
    ui->LB_amountDue->setText(QString::fromStdString(Currency::currencySymbol) + "0");
    ui->LB_nSellected->setText("0");
}

void invoice_widget::search(const QString &text){
    QString searchBy = ui->CB_searchBy->currentText();

    if (searchBy == "Name")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getName);
    else if (searchBy == "SKU")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getSku);
    else if (searchBy == "Category")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getCategory);
    else if (searchBy =="Brand")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getBrand);
    else if (searchBy == "Unit")
        updateTableViewWithSearchCriteria(text.toLower(), &InvoiceItem::getUnit);
}

void invoice_widget::on_PB_purchase_clicked(){
    if (m_user->getInvoice().getInvoiceItemModel().getItems().size() == 0){
        ui->LB_error->setText("You Haven't select any item");
        ui->LB_error->setVisible(true);
    }
    else {
        DataHandler data;
        data.updateCustomerProducts(*m_user, m_user->getInvoice());
        data.updateProviderProducts(*m_provider, m_user->getInvoice());
        data.addInvoice(m_user->getInvoice());

        m_user->purchase();
        m_provider->sold(m_user->getInvoice());
        m_user->editInvoice().clearInvoice();

        initializeTableView();
        setLabels();
        updateTable();
    }
}


void invoice_widget::on_PB_clear_clicked(){
    clear();
}


void invoice_widget::on_PB_remove_clicked(){
    QModelIndex selectedIndex = ui->TV_items->currentIndex();
    if (selectedIndex.isValid()){
        int row = selectedIndex.row();
        // Get the index of the selected cell
        QModelIndex selectedCellIndex = ui->TV_items->model()->index(row, 0);

        // Extract the SKU from the selected cell
        QString selectedSku = ui->TV_items->model()->data(selectedCellIndex, Qt::DisplayRole).toString();

        m_user->editInvoice().removeItem(selectedSku.toStdString());

        setLabels();
    }
}


void invoice_widget::on_LE_search_textChanged(const QString &arg1){
    search(arg1);
}


template<typename MemberFunction>
void invoice_widget::updateTableViewWithSearchCriteria(const QString &text, MemberFunction memberFunction){
    const std::vector<InvoiceItem>& items = m_user->getInvoice().getInvoiceItemModel().getItems();

    // Clear the table
    m_tableViewModel.removeRows(0, m_tableViewModel.rowCount());

    int row = 0;

    for (const InvoiceItem& item : items){
        QString value = QString::fromStdString((item.*memberFunction)()).toLower();

        if (value.startsWith(text)){
            m_tableViewModel.setItem(row,0 ,new QStandardItem(QString::fromStdString(item.getSku())));
            m_tableViewModel.setItem(row,1 ,new QStandardItem(QString::fromStdString(item.getName())));
            m_tableViewModel.setItem(row,2 ,new QStandardItem(QString::fromStdString(item.getBrand())));
            m_tableViewModel.setItem(row,3 ,new QStandardItem(QString::fromStdString(item.getCategory())));
            m_tableViewModel.setItem(row,4 ,new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(item.getPrice(), 'f', 2)));
            m_tableViewModel.setItem(row,5 ,new QStandardItem(QString::number(item.getInventory())));
            m_tableViewModel.setItem(row,6 ,new QStandardItem(QString::fromStdString(item.getUnit())));
            m_tableViewModel.setItem(row,7 ,new QStandardItem(QString::fromStdString(item.getExDate())));
            row++;
        }
    }
}
