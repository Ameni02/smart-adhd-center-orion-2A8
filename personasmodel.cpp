
#include "personasmodel.h"
#include <QSqlTableModel>


PersonasModel::PersonasModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant PersonasModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

bool PersonasModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int PersonasModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int PersonasModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

bool PersonasModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

bool PersonasModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void PersonasModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant PersonasModel::data(const QModelIndex &idx, int role) const
{
    if ( idx.column() == 5 )
    {
        QString imgFile = QSqlTableModel::data( idx, Qt::DisplayRole );
        if ( Qt::DisplayRole == role )
        {
            return QString();
        }
        if ( !QFile::exists( imgFile ))
        {
            imgFile = ":/centinela/images/picture_unavailable.jpg";
        }
        QPixmap pixmap( imgFile );
        if ( role == Qt::DecorationRole )
        {
            return pixmap;
        }
        if(role == Qt::SizeHintRole)
        {
            return pixmap.size();
        }
    }
    return QSqlTableModel::data( idx, role );
}

bool PersonasModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags PersonasModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool PersonasModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool PersonasModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return true;
}

bool PersonasModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

bool PersonasModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return true;
}

