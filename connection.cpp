#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("hyperflow");
db.setUserName("ameni");//inserer nom de l'utilisateur
db.setPassword("ameni");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}


void Connection::closeConnection()
{db.close();}
