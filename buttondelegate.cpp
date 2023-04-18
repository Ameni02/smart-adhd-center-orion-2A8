#include "buttonDelegate.h"
#include <QPushButton>
#include <QPainter>

ButtonDelegate::ButtonDelegate(QObject* parent)
    : QStyledItemDelegate(parent), m_parentWidget(nullptr) {}

void ButtonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QStyledItemDelegate::paint(painter, option, index);

    // Draw a button on top of the cell for the last column
    if (index.column() == (index.model()->columnCount() - 1)) {
        QPushButton button("Click", m_parentWidget);
        button.setGeometry(option.rect);
        QPixmap pixmap(button.size());
        button.render(&pixmap);
        painter->drawPixmap(option.rect, pixmap);
    }
}

QSize ButtonDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    return QSize(100, option.rect.height());
}

void ButtonDelegate::onButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QModelIndex index = button->property("index").value<QModelIndex>();
        emit buttonClicked(index);
    }
}
