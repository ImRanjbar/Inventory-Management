#include "currency_widget.h"
#include "ui_currency_widget.h"
#include "../currency.h"
#include "../datahandler.h"
#include "edit_exchange_rate_window.h"

currency_widget::currency_widget(Manufacturers* manufacturers,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::currency_widget)
{
    ui->setupUi(this);


    m_manufacturers = manufacturers;
    m_currency = new CurrencyConverter;
    m_currency->setCurrentCurrency(Currency::currentCurrency);

    DataHandler data;
    data.readCurrencyRates(*m_currency);


    setCurrentCurrencyRB();
}

currency_widget::~currency_widget()
{
    DataHandler data;
    data.saveCurrencyRates(*m_currency);
    delete ui;
}

void currency_widget::setCurrentCurrencyRB(){
    
    if (Currency::currentCurrency == "AED")
        ui->RB_AED->click();
    else if (Currency::currentCurrency == "AUD")
        ui->RB_AUD->click();
    else if (Currency::currentCurrency == "BRL")
        ui->RB_BRL->click();
    else if (Currency::currentCurrency == "CAD")
        ui->RB_CAD->click();
    else if (Currency::currentCurrency == "CHF")
        ui->RB_CHF->click();
    else if (Currency::currentCurrency == "CNY")
        ui->RB_CNY->click();
    else if (Currency::currentCurrency == "EGP")
        ui->RB_EGP->click();
    else if (Currency::currentCurrency == "EUR")
        ui->RB_EUR->click();
    else if (Currency::currentCurrency == "GBP")
        ui->RB_GBP->click();
    else if (Currency::currentCurrency == "HKD")
        ui->RB_HKD->click();
    else if (Currency::currentCurrency == "INR")
        ui->RB_INR->click();
    else if (Currency::currentCurrency == "IRR")
        ui->RB_IRR->click();
    else if (Currency::currentCurrency == "JPY")
        ui->RB_JPY->click();
    else if (Currency::currentCurrency == "KRW")
        ui->RB_KRW->click();
    else if (Currency::currentCurrency == "MXN")
        ui->RB_MXN->click();
    else if (Currency::currentCurrency == "NOK")
        ui->RB_NOK->click();
    else if (Currency::currentCurrency == "NZD")
        ui->RB_NZD->click();
    else if (Currency::currentCurrency == "PLN")
        ui->RB_PLN->click();
    else if (Currency::currentCurrency == "RUB")
        ui->RB_RUB->click();
    else if (Currency::currentCurrency == "SAR")
        ui->RB_SAR->click();
    else if (Currency::currentCurrency == "SEK")
        ui->RB_SEK->click();
    else if (Currency::currentCurrency == "TRY")
        ui->RB_TRY->click();
    else if (Currency::currentCurrency == "USD")
        ui->RB_USD->click();
    else if (Currency::currentCurrency == "ZAR")
        ui->RB_ZAR->click();
}

void currency_widget::on_RB_AED_clicked() {
    if (Currency::currentCurrency == "AED")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "AED");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_AUD_clicked() {
    if (Currency::currentCurrency == "AUD")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "AUD");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_BRL_clicked() {
    if (Currency::currentCurrency == "BRL")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "BRL");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_CAD_clicked() {
    if (Currency::currentCurrency == "CAD")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "CAD");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_CHF_clicked() {
    if (Currency::currentCurrency == "CHF")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "CHF");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_CNY_clicked() {
    if (Currency::currentCurrency == "CNY")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "CNY");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_EGP_clicked() {
    if (Currency::currentCurrency == "EGP")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "EGP");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_EUR_clicked() {
    if (Currency::currentCurrency == "EUR")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "EUR");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_GBP_clicked() {
    if (Currency::currentCurrency == "GBP")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "GBP");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_HKD_clicked() {
    if (Currency::currentCurrency == "HKD")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "HKD");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_INR_clicked() {
    if (Currency::currentCurrency == "INR")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "INR");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_IRR_clicked() {
    if (Currency::currentCurrency == "IRR")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "IRR");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_JPY_clicked() {
    if (Currency::currentCurrency == "JPY")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "JPY");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_KRW_clicked() {
    if (Currency::currentCurrency == "KRW")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "KRW");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_MXN_clicked() {
    if (Currency::currentCurrency == "MXN")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "MXN");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_NOK_clicked() {
    if (Currency::currentCurrency == "NOK")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "NOK");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_NZD_clicked() {
    if (Currency::currentCurrency == "NZD")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "NZD");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_PLN_clicked() {
    if (Currency::currentCurrency == "PLN")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "PLN");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_RUB_clicked() {
    if (Currency::currentCurrency == "RUB")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "RUB");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_SAR_clicked() {
    if (Currency::currentCurrency == "SAR")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "SAR");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_SEK_clicked() {
    if (Currency::currentCurrency == "SEK")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "SEK");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_TRY_clicked() {
    if (Currency::currentCurrency == "TRY")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "TRY");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_USD_clicked() {
    if (Currency::currentCurrency == "USD")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "USD");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}

void currency_widget::on_RB_ZAR_clicked() {
    if (Currency::currentCurrency == "ZAR")
        return;
    m_currency->convertCurrency(m_manufacturers, Currency::currentCurrency, "ZAR");
    Currency::currentCurrency = m_currency->getCurrentCurrency();
    Currency::currencySymbol = m_currency->getSymbol();
}




void currency_widget::on_PB_editRate_clicked(){
    edit_exchange_rate_window* editExchangeRateWindow = new edit_exchange_rate_window(m_currency, this);
    editExchangeRateWindow->setModal(true);
    editExchangeRateWindow->show();
}

