
#include "imageshop.h"


imageshop::imageshop(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant imageshop::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int imageshop::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int imageshop::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant imageshop::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

