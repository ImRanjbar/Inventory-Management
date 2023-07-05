#include "reports_widget.h"
#include "purchase_invoice_window.h"
#include "sale_invoice_window.h"
#include "ui_reports_widget.h"
#include "../currency.h"
#include "../datahandler.h"
#include <QPainter>
#include <QStyledItemDelegate>

reports_widget::reports_widget(Manufacturers* manufacturers, Seller* user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reports_widget)
{
    ui->setupUi(this);
    m_manufacturers = manufacturers;
    m_user = user;

    initializeTablesView();

    updatePurchaseTable();

    updateSoldTable();

    setLabels();
    setComboBoxes();
}

reports_widget::~reports_widget()
{
    delete ui;
}

void reports_widget::initializeTablesView(){
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

    class CustomHeaderView : public QHeaderView {
    public:
        explicit CustomHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr)
            : QHeaderView(orientation, parent) {
        }

    protected:
        void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override {
            painter->save();
            painter->setFont(QFont("Arial", 12, QFont::Bold));
            painter->fillRect(rect, QColor(50, 100, 150)); // Replace with your desired background color
            painter->setPen(Qt::white);
            painter->drawText(rect, Qt::AlignCenter, model()->headerData(logicalIndex, orientation()).toString());
            painter->restore();
        }
    };

    // Create and set the custom delegate for center alignment
    ui->TV_purchase->setItemDelegate(new CenterAlignmentDelegate(ui->TV_purchase));

    ui->TV_solds->setItemDelegate(new CenterAlignmentDelegate(ui->TV_solds));

    // Set the custom header view
    ui->TV_purchase->setHorizontalHeader(new CustomHeaderView(Qt::Horizontal, ui->TV_purchase));

    ui->TV_solds->setHorizontalHeader(new CustomHeaderView(Qt::Horizontal, ui->TV_solds));



    // Set the headers for the purchase invoices table
    m_purchaseItemModel.setHorizontalHeaderItem(0, new QStandardItem("Invoice Number"));
    m_purchaseItemModel.setHorizontalHeaderItem(1, new QStandardItem("Date"));
    m_purchaseItemModel.setHorizontalHeaderItem(2, new QStandardItem("Provider"));
    m_purchaseItemModel.setHorizontalHeaderItem(3, new QStandardItem("Amount"));

    // Set the headers for the sold invoices table
    m_soldItemModel.setHorizontalHeaderItem(0, new QStandardItem("Invoice Number"));
    m_soldItemModel.setHorizontalHeaderItem(1, new QStandardItem("Date"));
    m_soldItemModel.setHorizontalHeaderItem(2, new QStandardItem("Customer"));
    m_soldItemModel.setHorizontalHeaderItem(3, new QStandardItem("Amount"));

    // Set the models for the table views
    ui->TV_purchase->setModel(&m_purchaseItemModel);
    ui->TV_purchase->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TV_purchase->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->TV_solds->setModel(&m_soldItemModel);
    ui->TV_solds->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TV_solds->setSelectionMode(QAbstractItemView::SingleSelection);


    for (int column = 0; column < 4; column++){
        ui->TV_purchase->setColumnWidth(column, 182);
        ui->TV_solds->setColumnWidth(column, 182);
    }

}

void reports_widget::updatePurchaseTable(){
    const std::vector<Invoice>& invoices = m_user->getPurchaseModel().getInvoices();

    int row = 0;
    for (const Invoice& invoice : invoices){
        m_purchaseItemModel.setItem(row, 0, new QStandardItem(QString::number(invoice.getInvoiceNumber())));
        m_purchaseItemModel.setItem(row, 1, new QStandardItem(QString::fromStdString(invoice.getDate())));
        m_purchaseItemModel.setItem(row, 2, new QStandardItem(QString::fromStdString(invoice.getProviderName())));
        m_purchaseItemModel.setItem(row, 3, new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(invoice.getTotalAmount(), 'f', 2)));
        row++;
    }
}

void reports_widget::updateSoldTable(){
    const std::vector<Invoice>& invoices = m_user->getSoldModel().getInvoices();

    int row = 0;
    for (const Invoice& invoice : invoices){
        m_soldItemModel.setItem(row, 0, new QStandardItem(QString::number(invoice.getInvoiceNumber())));
        m_soldItemModel.setItem(row, 1, new QStandardItem(QString::fromStdString(invoice.getDate())));
        m_soldItemModel.setItem(row, 2, new QStandardItem(QString::fromStdString(invoice.getCustomerName())));
        m_soldItemModel.setItem(row, 3, new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(invoice.getTotalAmount(), 'f', 2)));
        row++;
    }
}

void reports_widget::setLabels(){
    // Set the label for the total number of purchase invoices
    const int purchaseInvoicesNumber = static_cast<int>(m_user->getPurchaseModel().getInvoices().size());
    ui->LB_nPurchasInvoices->setText(QString::number(purchaseInvoicesNumber));

    // Set the label for the favorite company in purchase invoices
    const QString favorite = QString::fromStdString(calculateFavoriteCompany(true));
    if (!favorite.isEmpty())
        ui->LB_favoriteComp->setText(favorite);
    else
        ui->LB_favoriteComp->setText("None");

    // Calculate and set the label for the total cost of purchase invoices
    double totalCost{0};
    for (const Invoice& invoice : m_user->getPurchaseModel().getInvoices()){
        totalCost += invoice.getTotalAmount();
    }
    if (totalCost > 10000)
        ui->LB_totalCost->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalCost/1000, 'f', 2) + "K");
    else
        ui->LB_totalCost->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalCost, 'f', 2));


    // Set the label for the total number of sold invoices
    const int totalSaleInvoices = static_cast<int>(m_user->getSoldModel().getInvoices().size());
    ui->LB_nSoldInvoices->setText(QString::number(totalSaleInvoices));

    // Set the label for the top buyer in sold invoices
    const QString bestBuyer = QString::fromStdString(calculateFavoriteCompany(false));
    if (!bestBuyer.isEmpty())
        ui->LB_topBuyer->setText(bestBuyer);
    else
        ui->LB_topBuyer->setText("None");

    // Calculate and set the label for the total revenue from sold invoices
    double totalRevenue{0};
    for (const Invoice& invoice : m_user->getSoldModel().getInvoices()){
        totalRevenue += invoice.getTotalAmount();
    }

    if (totalRevenue > 10000)
        ui->LB_totalRevenue->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalRevenue/1000, 'f', 2) + "K");
    else
        ui->LB_totalRevenue->setText(QString::fromStdString(Currency::currencySymbol) + QString::number(totalRevenue, 'f', 2));
}

void reports_widget::setComboBoxes(){
    ui->CB_purchase->addItem("Invoice Number");
    ui->CB_purchase->addItem("Provider");
    ui->CB_purchase->addItem("Date");

    ui->CB_sale->addItem("Invoice Number");
    ui->CB_sale->addItem("Customer");
    ui->CB_sale->addItem("Date");
}

std::string reports_widget::calculateFavoriteCompany(bool isPurchase) {
    // Get the appropriate list of invoices based on the 'isPurchase' flag
    const std::vector<Invoice>& invoices = isPurchase ? m_user->getPurchaseModel().getInvoices() : m_user->getSoldModel().getInvoices();

    std::unordered_map<std::string, double> companyAmountMap;

    // Iterate through the invoices and calculate the total amount for each company
    for (const Invoice& invoice : invoices) {
        std::string companyName = isPurchase ? invoice.getProviderName() : invoice.getCustomerName();
        companyAmountMap[companyName] += invoice.getTotalAmount();
    }

    std::string favoriteCompany;
    double maxAmount = 0.0;

    // Find the company with the highest total amount
    for (const auto& [companyName, amount] : companyAmountMap) {
        if (amount > maxAmount) {
            maxAmount = amount;
            favoriteCompany = companyName;
        }
    }

    return favoriteCompany;
}

void reports_widget::search(const QString &text, bool isPurchase){
    QString searchBy{};
    if (isPurchase)
        searchBy = ui->CB_purchase->currentText();
    else
        searchBy = ui->CB_sale->currentText();

    if (searchBy == "Invoice Number")
        updateTableViewWithSearchCriteria(text, &Invoice::getInvoiceNumberStr, isPurchase);
    else if (searchBy == "Provider")
        updateTableViewWithSearchCriteria(text, &Invoice::getProviderName, true);
    else if (searchBy == "Customer")
        updateTableViewWithSearchCriteria(text, &Invoice::getCustomerName, false);
    else if (searchBy == "Date")
        updateTableViewWithSearchCriteria(text, &Invoice::getDate, isPurchase);
}

void reports_widget::on_TV_purchase_doubleClicked(const QModelIndex &index){
    const int row = index.row();

    const int invoiceNumber = m_purchaseItemModel.item(row,0)->data(Qt::DisplayRole).toInt();
    Invoice& invoice = m_user->editPurchaseModel().editInvoice(invoiceNumber);

    DataHandler data;
    data.readInvoiceItems(invoice);

    purchase_invoice_window* purchaseInvoice = new purchase_invoice_window(invoice,this);
    purchaseInvoice->setModal(true);
    purchaseInvoice->show();
}

void reports_widget::on_TV_solds_doubleClicked(const QModelIndex &index){
    const int row = index.row();

    const int invoiceNumber = m_soldItemModel.item(row,0)->data(Qt::DisplayRole).toInt();
    Invoice& invoice = m_user->editSoldModel().editInvoice(invoiceNumber);

    DataHandler data;
    data.readInvoiceItems(invoice);

    sale_invoice_window* purchaseInvoice = new sale_invoice_window(invoice,this);
    purchaseInvoice->setModal(true);
    purchaseInvoice->show();
}

void reports_widget::on_LE_purchaseSearch_textChanged(const QString &arg1){
    search(arg1, true);
}


void reports_widget::on_LE_saleSearch_textChanged(const QString &arg1){
    search(arg1,false);
}


template<typename MemberFunction>
void reports_widget::updateTableViewWithSearchCriteria(const QString &text, MemberFunction memberFunction, bool isPurchase){
    const std::vector<Invoice>* invoices;
    QStandardItemModel* tableViewModel;
    if (isPurchase){
        tableViewModel = &m_purchaseItemModel;
        invoices = &m_user->getPurchaseModel().getInvoices();
    }
    else{
        tableViewModel = &m_soldItemModel;
        invoices = &m_user->getSoldModel().getInvoices();
    }

    // Clear the table
    tableViewModel->removeRows(0, tableViewModel->rowCount());

    int row = 0;

    for (const Invoice& invoice : *invoices){
        QString value = QString::fromStdString((invoice.*memberFunction)());

        if (value.startsWith(text)){
            tableViewModel->setItem(row, 0, new QStandardItem(QString::number(invoice.getInvoiceNumber())));
            tableViewModel->setItem(row, 1, new QStandardItem(QString::fromStdString(invoice.getDate())));
            if (isPurchase)
                tableViewModel->setItem(row, 2, new QStandardItem(QString::fromStdString(invoice.getProviderName())));
            else
                tableViewModel->setItem(row, 2, new QStandardItem(QString::fromStdString(invoice.getCustomerName())));
            tableViewModel->setItem(row, 3, new QStandardItem(QString::fromStdString(Currency::currencySymbol) + QString::number(invoice.getTotalAmount(), 'f', 2)));
            row++;
        }
    }
}
