#include "edit_exchange_rate_window.h"
#include "ui_edit_exchange_rate_window.h"
#include <QValidator>
#include <QMessageBox>

edit_exchange_rate_window::edit_exchange_rate_window(CurrencyConverter* currency,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_exchange_rate_window)
{
    ui->setupUi(this);
    m_currency = currency;

    this->setWindowTitle("Edit Exchang Rate");

    setComboBoxes();

    ui->LE_rate->setValidator(new QDoubleValidator(0,100, 10, this));

    connect(ui->LE_rate, &QLineEdit::textChanged, this, &edit_exchange_rate_window::handleTextChanged);
    connect(m_baseCurrency, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &edit_exchange_rate_window::handleComboBoxIndexChanged);
    connect(m_quoteCurrency, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &edit_exchange_rate_window::handleComboBoxIndexChanged);

}

edit_exchange_rate_window::~edit_exchange_rate_window()
{
    delete ui;
}

void edit_exchange_rate_window::setComboBoxes(){
    CustomComboBox* CB_baseCurrency = new CustomComboBox(this);
    for (int i = 0; i < 24; i++){
        CB_baseCurrency->addItem("");
    }

    CB_baseCurrency->setFixedSize(235,50);
    CB_baseCurrency->setGeometry(100, 100, 235,50);

    CB_baseCurrency->show();


    CustomComboBox* CB_quoteCurrency = new CustomComboBox(this);
    for (int i = 0; i < 24; i++){
        CB_quoteCurrency->addItem("");
    }

    CB_baseCurrency->setFixedSize(235,50);
    CB_quoteCurrency->setGeometry(400, 100, 235, 50);

    CB_quoteCurrency->show();

    m_baseCurrency = CB_baseCurrency;
    m_quoteCurrency = CB_quoteCurrency;
}

const std::string edit_exchange_rate_window::getString(int index){
    CurrencyIndex currency = static_cast<CurrencyIndex>(index);

    switch (currency) {
    case AED:
        return "AED";
    case AUD:
        return "AUD";
    case BRL:
        return "BRL";
    case CAD:
        return "CAD";
    case CHF:
        return "CHF";
    case CNY:
        return "CNY";
    case EGP:
        return "EGP";
    case EUR:
        return "EUR";
    case GBP:
        return "GBP";
    case HKD:
        return "HKD";
    case INR:
        return "INR";
    case IRR:
        return "IRR";
    case JPY:
        return "JPY";
    case KRW:
        return "KRW";
    case MXN:
        return "MXN";
    case NOK:
        return "NOK";
    case NZD:
        return "NZD";
    case PLN:
        return "PLN";
    case RUB:
        return "RUB";
    case SAR:
        return "SAR";
    case SEK:
        return "SEK";
    case TRY:
        return "TRY";
    case USD:
        return "USD";
    case ZAR:
        return "ZAR";
    default:
        return "Unknown";
    }
}

void edit_exchange_rate_window::handleTextChanged(){
    if (m_baseCurrency->currentIndex() != m_quoteCurrency->currentIndex()){
        ui->PB_reset->setEnabled(true);
        ui->PB_applyChanges->setEnabled(true);
    }
}

void edit_exchange_rate_window::handleComboBoxIndexChanged(){
    ui->LB_error->setVisible(false);

    if (m_baseCurrency->currentIndex() == m_quoteCurrency->currentIndex()){
        ui->LB_error->setText("Invalid Currency Pair");
        ui->LB_error->setVisible(true);
        ui->LE_rate->setText("1");
        ui->LE_rate->setValidator(new QDoubleValidator(0,100, 10, this));

        ui->PB_applyChanges->setEnabled(false);
        ui->PB_reset->setEnabled(false);
    }
    else {
        std::string base = getString(m_baseCurrency->currentIndex());
        std::string quote = getString(m_quoteCurrency->currentIndex());
        setLineEditRate(base, quote);
    }
}

void edit_exchange_rate_window::setLineEditRate(std::string &base, std::string quote){
    double rate = m_currency->getRate(base, quote);
    ui->LE_rate->setValidator(new QDoubleValidator(0,100, 10, this));
    ui->LE_rate->setText(QString::number(rate, 'f', 7));
    ui->PB_reset->setEnabled(false);
    ui->PB_applyChanges->setEnabled(false);
}

void edit_exchange_rate_window::changeExchangetRate(const std::string &base, const std::string &quote){
    double newRate = ui->LE_rate->text().trimmed().toDouble();
    m_currency->setConversionRate(base, quote, newRate);
    m_currency->setConversionRate(quote, base, 1/newRate);
}

void edit_exchange_rate_window::showMessage(){
    QMessageBox* messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("Result");
    messageBox->setText("The currency exchange rate has been updated successfully");
    messageBox->setIcon(QMessageBox::Information);
    messageBox->show();
}

void edit_exchange_rate_window::on_PB_applyChanges_clicked(){
    ui->LB_error->setVisible(false);
    if (ui->LE_rate->text().trimmed().isEmpty()){
        ui->LB_error->setText("Field cannot be left empty");
        ui->LB_error->setVisible(true);
    }
    else {
        std::string baseCurrency = getString(m_baseCurrency->currentIndex());
        std::string quoteCurrency = getString(m_quoteCurrency->currentIndex());
        changeExchangetRate(baseCurrency, quoteCurrency);
        showMessage();
    }
}


void edit_exchange_rate_window::on_PB_reset_clicked(){
    std::string baseCurrency = getString(m_baseCurrency->currentIndex());
    std::string quoteCurrency = getString(m_quoteCurrency->currentIndex());
    setLineEditRate(baseCurrency, quoteCurrency);
}


void edit_exchange_rate_window::on_PB_cancel_clicked(){
    this->deleteLater();
}
