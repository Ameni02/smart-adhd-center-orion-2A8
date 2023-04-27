#ifndef ACTIVITE_H
#define ACTIVITE_H
#include <QString>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QObject>
#include <QDateTime>


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
QSqlQueryModel * recherche_NOM(QString);
QSqlQueryModel * tri_croissant();
QSqlQueryModel * tri_decroissant();
QChartView * Stat();
//calender
void ajouterActivite(QCalendarWidget *calendrier);


private:

};
class Tache
{
    int idtache;
    QString Nom_inter,Nom_tache,Etat;
public:

   Tache();
   Tache(int,QString,QString,QString);

  int getid_tache();
   void setid_tache(int);
bool ajouter_tache();
QSqlQueryModel * afficher_tache();
bool supprmier_tache(int);
private:

};

#endif // ACTIVITE_H
