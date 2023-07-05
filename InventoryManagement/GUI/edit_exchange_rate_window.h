#ifndef EDIT_EXCHANGE_RATE_WINDOW_H
#define EDIT_EXCHANGE_RATE_WINDOW_H

#include <QDialog>
#include "../CurrencyConverter.h"
#include <QApplication>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPixmap>


class BackgroundDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override{
        QStyledItemDelegate::paint(painter, option, index);

        QList<QPixmap> backgroundImages;
        backgroundImages.append(QPixmap(":/Images/icons/countries/AED.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/AUD.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/BRL.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/CAD.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/CHF.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/CNY.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/EGP.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/EUR.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/GBP.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/HKD.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/INR.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/IRR.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/JPY.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/KRW.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/MXN.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/NOK.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/NZD.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/PLN.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/RUB.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/SAR.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/SEK.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/TRY.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/USD.png"));
        backgroundImages.append(QPixmap(":/Images/icons/countries/ZAR.png"));

        // Get the index of the current item
        int itemIndex = index.row();

        // Check if the item index is within the range of the background images list
        if (itemIndex >= 0 && itemIndex < backgroundImages.size()){
            QPixmap backgroundImage = backgroundImages[itemIndex];

            QRect targetRect = option.rect;

            if (option.state & QStyle::State_Selected){
                painter->fillRect(targetRect, Qt::lightGray);
                painter->drawPixmap(targetRect, backgroundImage);
            }
            else{
                painter->drawPixmap(targetRect, backgroundImage);
            }
        }
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override{
        QSize size = QStyledItemDelegate::sizeHint(option, index);

        int borderWidth = 235;
        int borderHeight = 50;

        size.setWidth(borderWidth);
        size.setHeight(borderHeight);

        return size;
    }
};

class CustomComboBox : public QComboBox
{
public:
    CustomComboBox(QWidget* parent = nullptr) : QComboBox(parent) {
        setItemDelegate(new BackgroundDelegate());
    }

    void paintEvent(QPaintEvent* event) override{

        setStyleSheet(
            "QComboBox {"
            "    background-color: #d9e5f8;"
            "    border: none;"
            "    border-radius: 0px;"
            "    padding: 0px 0px;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: right;"
            "    width: 30px;"
            "    border-left-width: 0px;"
            "    border-left-color: #CCCCCC;"
            "    border-left-style: solid;"
            "    border-top-right-radius: 3px;"
            "    border-bottom-right-radius: 4px;"
            "    background: transparent;"
            "}"
            "QComboBox::down-arrow {"
            "    image: url(:/Images/icons/downChevronComboBox.png);"
            "}"
            );

        QComboBox::paintEvent(event);

        if (currentIndex() >= 0 && currentIndex() < count()){
            QList<QPixmap> backgroundImages;
            backgroundImages.append(QPixmap(":/Images/icons/countries/AED.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/AUD.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/BRL.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/CAD.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/CHF.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/CNY.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/EGP.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/EUR.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/GBP.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/HKD.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/INR.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/IRR.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/JPY.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/KRW.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/MXN.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/NOK.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/NZD.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/PLN.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/RUB.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/SAR.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/SEK.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/TRY.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/USD.png"));
            backgroundImages.append(QPixmap(":/Images/icons/countries/ZAR.png"));
            
            // Check if the index is within the range of the background images list
            if (currentIndex() >= 0 && currentIndex() < backgroundImages.size()){
                QPixmap backgroundImage = backgroundImages[currentIndex()];

                QStyleOptionComboBox viewOptions;
                viewOptions.initFrom(this);

                // Get the rectangle of the selected item
                QRect targetRect = viewOptions.rect;
                targetRect.setHeight(50);

                QPainter painter(this);

                painter.drawPixmap(targetRect, backgroundImage);
            }
        }
    }

protected:
    void enterEvent(QEnterEvent* event) override {
        QComboBox::enterEvent(event);
        setCursor(Qt::PointingHandCursor);
    }

    void leaveEvent(QEvent* event) override {
        QComboBox::leaveEvent(event);
        unsetCursor();
    }
};

enum CurrencyIndex {
    AED,
    AUD,
    BRL,
    CAD,
    CHF,
    CNY,
    EGP,
    EUR,
    GBP,
    HKD,
    INR,
    IRR,
    JPY,
    KRW,
    MXN,
    NOK,
    NZD,
    PLN,
    RUB,
    SAR,
    SEK,
    TRY,
    USD,
    ZAR
};

namespace Ui {
class edit_exchange_rate_window;
}

class edit_exchange_rate_window : public QDialog
{
    Q_OBJECT

public:
    explicit edit_exchange_rate_window(CurrencyConverter* currency,QWidget *parent = nullptr);
    ~edit_exchange_rate_window();

    void setComboBoxes();

    const std::string getString(int index);

    void setLineEditRate(std::string& base, std::string quote);

    void changeExchangetRate(const std::string& base, const std::string& quote);

    void showMessage();

private slots:
    void handleTextChanged();

    void handleComboBoxIndexChanged();

    void on_PB_applyChanges_clicked();

    void on_PB_reset_clicked();

    void on_PB_cancel_clicked();

private:
    Ui::edit_exchange_rate_window *ui;
    CurrencyConverter* m_currency;
    CustomComboBox* m_baseCurrency;
    CustomComboBox* m_quoteCurrency;
};


#endif // EDIT_EXCHANGE_RATE_WINDOW_H
