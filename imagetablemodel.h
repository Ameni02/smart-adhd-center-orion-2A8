
#ifndef IMAGETABLEMODEL_H
#define IMAGETABLEMODEL_H

#include <QSqlTableModel>
#include <QImage>
#include <QPixmap>
#include <QSqlRecord>
#include "ImageTableModel.h"

class ImageTableModel : public QSqlTableModel
{
   QSqlQueryModel imageTableModel;
public:
    ImageTableModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // IMAGETABLEMODEL_H
