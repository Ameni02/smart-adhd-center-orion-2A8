#include "connect.h"

Connect::Connect()
{


}

bool Connect::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hyperflow");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("sarah147");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;

}
void Connect::closeConnect()
{
    db.close();
}
