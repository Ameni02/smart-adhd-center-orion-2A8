#ifndef CONNECT_H
#define CONNECT_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connect
{
   QSqlDatabase db ;
public:
    Connect();


    bool createconnect();
    void closeConnect();
};

#endif // CONNECT_H
