
#include "mytablemodel.h"

MyTableModel::MyTableModel(QObject *parent)
    : QSqlTableModel{parent}
{

}
MyTableModel(QObject* parent = nullptr
    : QSqlTableModel(parent, db)
{
    setTable("myTable"); // Set the table name
    select(); // Fetch data from the table
}

// Override the data() function to handle image data
QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
{
    if (role == Qt::DecorationRole && index.column() == 1) // Check for image data
    {
        // Retrieve the image data from the model
        QByteArray imageData = QSqlTableModel::data(index).toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        return pixmap;
    }

    return QSqlTableModel::data(index, role);
}
};


