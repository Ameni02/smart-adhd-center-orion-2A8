#include "connect.h"

connect::connect()
{


}

bool connect::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hyperflow");
db.setUserName("moataz");
db.setPassword("moataz");

if (db.open())
test=true;
    return  test;/*
db.open();
QSqlQuery query(db);
test=true;
return  test;*/

}
void connect::closeConnect()
{
    db.close();
}
