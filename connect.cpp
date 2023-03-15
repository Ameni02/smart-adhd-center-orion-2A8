#include "connect.h"

connect::connect()
{


}

bool connect::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hyperflow");
db.setUserName("hyperflow");
db.setPassword("0000");

if (db.open())
test=true;





    return  test;

}
void connect::closeConnect()
{
    db.close();
}

