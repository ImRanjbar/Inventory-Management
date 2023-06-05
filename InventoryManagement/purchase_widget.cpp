#include "purchase_widget.h"
#include "ui_purchase_widget.h"

class CustomItemDelegate_QListView : public QStyledItemDelegate {
public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        if (option.state & QStyle::State_Selected) {
            // Customize the selected item's appearance
            painter->save();

            // Draw a rounded border around the selected item
            QColor bgColor("#b3b7ff");        // Background color of the selected item
            int borderRadius = 8;             // Radius of the rounded corners
            int borderWidth = 4;              // Width of the border

            painter->setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing for smooth edges
            painter->setPen(Qt::NoPen);       // No outline pen for the background
            painter->setBrush(bgColor);       // Set the background color
            painter->drawRoundedRect(option.rect.adjusted(borderWidth, borderWidth, -borderWidth, -borderWidth), borderRadius, borderRadius);

            painter->restore();
        } else {
            // Customize the non-selected item's appearance
            painter->fillRect(option.rect, Qt::transparent);
        }

        // Draw the text centered within the item's rectangle
        painter->setPen(Qt::black);            // Set the text color to black
        painter->setFont(QFont("Calibri", 9, QFont::Weight::Medium)); // Set the font and size
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());
    }
};

purchase_widget::purchase_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchase_widget)
{
    ui->setupUi(this);
    QStyledItemDelegate* listDelegate = new QStyledItemDelegate;
    ui->LV_brandList->setItemDelegate(listDelegate);
    ui->LV_categoryList->setItemDelegate(listDelegate);


}

purchase_widget::~purchase_widget()
{
    delete ui;
}
