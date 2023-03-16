#include "activite.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include<QObject>
activite::activite()
{
idactivite=0;
Nom=" ";
Description=" ";
Genre=" ";
Cible=" ";

}
activite::activite(int idactivite,QString Nom,QString Description,QString Genre,QString Cible)
{
    this->idactivite=idactivite;
    this->Nom=Nom;
    this->Description=Description;
    this->Genre=Genre;
    this->Cible=Cible;


}
int activite::getid(){
    return idactivite;
}
QString activite::getnom(){
    return Nom;
}
QString activite::getdescription(){
    return Description;
}
QString activite::getgenre(){
    return Genre;
}
QString activite::getcible(){
    return Cible;
}


void activite::setid(int idactivite)
{
    this->idactivite=idactivite;
}

void activite::setnom(QString Nom)
{
    this->Nom=Nom;
}
void activite::setcible(QString Cible)
{
    this->Cible=Cible;
}
void activite::setgenre(QString Genre)
{
    this->Genre=Genre;
}
void activite::setdescription(QString Description)
{
    this->Description=Description;
}
bool activite::ajouter()
{

    QSqlQuery query;
    QString res = QString::number(idactivite);
    query.prepare("insert into ACTIVITES (IDACTIVITE, NOM, DESCRIPTION, GENRE, CIBLE)"
                  "VALUES (:idactivite, :Nom, :Description, :Genre, :Cible)");
    query.bindValue(":idactivite",res);
    query.bindValue(":Nom",Nom);
query.bindValue(":Description",Description);
query.bindValue(":Genre",Genre);
query.bindValue(":Cible",Cible);


return query.exec();
}
bool activite::supprmier(int id)
{
    QSqlQuery query;

    query.prepare(" Delete from ACTIVITES where IDACTIVITE=:id");
    query.bindValue(0,id);

return query.exec();

    return query.exec();
}
QSqlQueryModel* activite::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM ACTIVITES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Idactivite"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("Description"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cible"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("Genre"));
       return model;
}





bool activite::modifier(int idactivite)
{

    QSqlQuery query;
        QString id_string=QString::number(idactivite);
        query.prepare("UPDATE activites SET Nom= :Nom,Description= :Description,Genre= :Genre,Cible= :Cible  WHERE idactivite= :idactivite");
        query.bindValue(":idactivite", id_string);
        query.bindValue(":Nom", Nom);
        query.bindValue(":Description", Description);
        query.bindValue(":Genre", Genre);
        query.bindValue(":Cible", Cible);
        if(!query.exec())
        {
            qDebug()<<"failed ";

        }
        else
{
        return query.exec();
}
}
