#ifndef CONNECT_H
#define CONNECT_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class connec
{
   QSqlDatabase db ;
public:
    connec();


    bool createconnect();
    void closeConnect();
};

#endif // CONNECT_H
