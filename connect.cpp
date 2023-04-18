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
///db.setConnectOptions("MYSQL_OPT_CONNECT_ATTR_SET=utf8");

if (db.open())
test=true;

    return  test;

}
void connect::closeConnect()
{
    db.close();
}
