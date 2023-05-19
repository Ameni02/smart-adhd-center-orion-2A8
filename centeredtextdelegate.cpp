#include "centeredTextDelegate.h"
#include "qabstractitemmodel.h"
#include <QPainter>

CenteredTextDelegate::CenteredTextDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
}

void CenteredTextDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // Draw the background
    painter->save();
    painter->fillRect(option.rect, option.palette.QPalette::window());
    painter->restore();

    // Get the text to display
    QString text = index.model()->data(index, Qt::DisplayRole).toString();

    // Center-align the text in the cell
    QRect textRect = option.rect;
    textRect.adjust(0, 0, -1, -1); // Adjust for cell borders
    painter->drawText(textRect, Qt::AlignCenter, text);

}
