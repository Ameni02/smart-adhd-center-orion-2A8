#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QStyledItemDelegate>

class ButtonDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit ButtonDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

signals:
    void buttonClicked(const QModelIndex& index);

private slots:
    void onButtonClicked();

private:
    QWidget* m_parentWidget;
};

#endif // BUTTONDELEGATE_H
