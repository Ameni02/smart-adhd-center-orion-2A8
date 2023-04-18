
#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QSqlTableModel>

#include <QWidget>


class MyTableModel : public QSqlTableModel
{
public:
    explicit MyTableModel(QObject *parent = nullptr);
};

#endif // MYTABLEMODEL_H
