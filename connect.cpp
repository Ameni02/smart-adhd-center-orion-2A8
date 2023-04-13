#include "connect.h"

connec::connec()
{


}

bool connec::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hyperflow");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("amine");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;

}
void connec::closeConnect()
{
    db.close();
}
