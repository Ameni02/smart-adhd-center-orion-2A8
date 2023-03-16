#include "equipements.h"
#include<QSqlQuery>
#include <QtDebug>
#include<QObject>




Equipements:: Equipements(int IDEQUIPEMENT , QString NOM , QString DESCRIPTION , QString TYPE , int QUANTITE , int PRIX)
{
this->IDEQUIPEMENT=IDEQUIPEMENT ;
this->NOM=NOM ;
this->DESCRIPTION=DESCRIPTION ;
this->TYPE=TYPE ;
this->QUANTITE=QUANTITE ;
this->PRIX=PRIX ;
}


 bool Equipements::ajouter()
 {
    QSqlQuery query;
    QString id_stringEquip= QString::number(IDEQUIPEMENT); //injecter des valeur de type string
     QString id_stringQuant= QString::number(QUANTITE);
         QString id_stringPrix=QString::number(PRIX);
         //prepare() prend la requete en parametre pour la preparer à l'exécution
          query.prepare("INSERT INTO EQUIPEMENTS ( IDEQUIPEMENT , NOM , DESCRIPTION,TYPE , QUANTITE , PRIX ) "
                        "VALUES (:IDEQUIPEMENT , :NOM , :DESCRIPTION , :TYPE, :QUANTITE , :PRIX)");
          //vérification des paramétres
          //faire correspondence entre le nom de la variable et la valeur stockéé au niveau de la zone saisie par l'utilisateur
          query.bindValue(":IDEQUIPEMENT",id_stringEquip);
          query.bindValue(":NOM",NOM);
          query.bindValue(":DESCRIPTION",DESCRIPTION);
          query.bindValue(":TYPE",TYPE);
          query.bindValue(":QUANTITE",id_stringQuant);
          query.bindValue(":PRIX",id_stringPrix);
         return query.exec(); // envoie la requete pour l'executer

 }

bool Equipements::supprimer(int IDEQUIPEMENT)
{
    QSqlQuery query;
    QString id_stringEquip= QString::number(IDEQUIPEMENT);

          query.prepare("Delete from EQUIPEMENTS where IDEQUIPEMENT =:idequip");
          query.bindValue(":idequip",id_stringEquip);

         return query.exec();

}

QSqlQueryModel* Equipements::afficher()
  {
       QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT* FROM equipements");
       model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant")); //changer nom de colonne
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));

       return model ;
  }


bool Equipements::modifier(int IDEQUIPEMENT)
{

    QSqlQuery query;

        query.prepare("UPDATE EQUIPEMENTS SET NOM=:NOM,DESCRIPTION=:DESCRIPTION,TYPE=:TYPE,QUANTITE=:QUANTITE,PRIX=:PRIX WHERE IDEQUIPEMENT= :IDEQUIPEMENT");

        query.bindValue(":IDEQUIPEMENT",IDEQUIPEMENT);
        query.bindValue(":NOM",NOM);
        query.bindValue(":DESCRIPTION",DESCRIPTION);
        query.bindValue(":TYPE",TYPE);
        query.bindValue(":QUANTITE",QUANTITE);
        query.bindValue(":PRIX",PRIX);
        return query.exec();
}

QSqlQueryModel * Equipements::recherche_NOM(QString NOM)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from Equipements WHERE NOM LIKE '%"+NOM+"%'");

    model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));
    return model;
}

QSqlQueryModel * Equipements:: tri_id()

{
    QSqlQueryModel * model = new QSqlQueryModel();
       model->setQuery("SELECT * FROM Equipements ORDER BY IDEQUIPEMENT  ASC");
       model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));
         return model;

                }
QSqlQueryModel * Equipements::tri_alphabetique()
{

    QSqlQueryModel * model = new QSqlQueryModel();
       model->setQuery("SELECT * FROM Equipements ORDER BY NOM");
       model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));
       return model;
}
