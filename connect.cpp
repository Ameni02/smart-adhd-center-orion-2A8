#include "connect.h"

connect::connect()
{


}

bool connect::createconnect()
{
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hyperflow");
db.setUserName("moataz");//inserer nom de l'utilisateur
db.setPassword("moataz");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;

}
void connect::closeConnect()
{
    db.close();
}
