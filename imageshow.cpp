
#include "imageshow.h"


imageshow::imageshow(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant imageshow::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int imageshow::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int imageshow::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant imageshow::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

