#ifndef ACTIVITE_H
#define ACTIVITE_H
#include <QString>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
class activite
{
    int idactivite;
    QString Nom,Description,Genre,Cible;

public:
    activite();
    activite(int,QString,QString,QString,QString);
    int getid();
    QString getnom();
    QString getdescription();
   QString getgenre();
   QString getcible();


   void setid(int);
   void setnom(QString);
   void setdescription(QString);
   void setgenre(QString);
   void setcible(QString);

bool ajouter();
QSqlQueryModel * afficher();
bool supprmier(int);
bool modifier(int);
private:

};

#endif // ACTIVITE_H
