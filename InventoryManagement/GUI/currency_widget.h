#ifndef CURRENCY_WIDGET_H
#define CURRENCY_WIDGET_H

#include "../CurrencyConverter.h"
#include <QWidget>

namespace Ui {
class currency_widget;
}

class currency_widget : public QWidget
{
    Q_OBJECT

public:
    explicit currency_widget(Manufacturers* manufacturers, QWidget *parent = nullptr);
    ~currency_widget();

    void setCurrentCurrencyRB();

private slots:
    void on_RB_AED_clicked();

    void on_RB_AUD_clicked();


    void on_RB_BRL_clicked();

    void on_RB_CAD_clicked();

    void on_RB_CHF_clicked();

    void on_RB_CNY_clicked();

    void on_RB_EGP_clicked();

    void on_RB_EUR_clicked();

    void on_RB_GBP_clicked();

    void on_RB_HKD_clicked();

    void on_RB_INR_clicked();

    void on_RB_IRR_clicked();

    void on_RB_JPY_clicked();

    void on_RB_KRW_clicked();

    void on_RB_MXN_clicked();

    void on_RB_NOK_clicked();

    void on_RB_NZD_clicked();

    void on_RB_PLN_clicked();

    void on_RB_RUB_clicked();

    void on_RB_SAR_clicked();

    void on_RB_SEK_clicked();

    void on_RB_TRY_clicked();

    void on_RB_USD_clicked();

    void on_RB_ZAR_clicked();

    void on_PB_editRate_clicked();

private:
    Ui::currency_widget *ui;
    Manufacturers* m_manufacturers;
    CurrencyConverter* m_currency;
};

#endif // CURRENCY_WIDGET_H
