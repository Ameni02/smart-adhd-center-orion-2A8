#ifndef CENTEREDTEXTDELEGATE_H
#define CENTEREDTEXTDELEGATE_H

#include <QStyledItemDelegate>

class CenteredTextDelegate : public QStyledItemDelegate
{
public:
    CenteredTextDelegate(QObject* parent = nullptr);

    // Override paint() to draw centered text
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // CENTEREDTEXTDELEGATE_H
