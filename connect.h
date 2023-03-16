#ifndef CONNECT_H
#define CONNECT_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class connect
{
   QSqlDatabase db ;
public:
    connect();


    bool createconnect();
    void closeConnect();
};

#endif // CONNECT_H
