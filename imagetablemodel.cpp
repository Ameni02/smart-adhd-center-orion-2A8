
// Assuming you have an existing QSqlDatabase connection 'db' and a table 'images' with columns 'id' and 'image_data'

// Define a custom QSqlTableModel
#include "qimage.h"
#include "qpixmap.h"
#include "qsqlrecord.h"
#include "qsqltablemodel.h"
#include "ImageTableModel.h"


ImageTableModel::ImageTableModel(QObject *parent)
    : QSqlTableModel(parent)
{
    // Constructor implementation
}
// Implement the custom data() method
QVariant ImageTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DecorationRole && index.column() == 8) {
        // Retrieve image data from the 'image_data' column in the database for the given row
     //   QSqlRecord record = QSqlTableModel::record(index.row());
       // QByteArray imageData = record.value("PHOTO").toByteArray();
        QByteArray imageData = record(index.row()).value("PHOTO").toByteArray();

        // Load image from byte array
        QImage image;
        image.loadFromData(imageData);
        QSize imageSize(100, 100); // Change the size as per your requirement
        QImage scaledImage = image.scaled(imageSize, Qt::KeepAspectRatio);

        // Convert image to QPixmap for display in table view
        QPixmap pixmap = QPixmap::fromImage(scaledImage);

        // Return QPixmap as QVariant for display in table view
        return QVariant(pixmap);
    }

    // Return default data for other columns or roles
    return QSqlTableModel::data(index, role);
}


