#include "equipements.h"
#include<QSqlQuery>
#include <QtDebug>
#include<QObject>


#include<QSqlQueryModel>
#include<QString>

#include <QFileDialog>
#include <QMessageBox>

#include <QtGui>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QByteArray>

#include <QTableView>
#include<QChartView>





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

QSqlQueryModel * Equipements:: tri_PrixC()

{   QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Equipements ORDER BY PRIX ");
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

QChartView * Equipements ::stat_type()
{
    int soin=0;
    int deco=0;
    int electro=0;
    int autre=0;

    QSqlQuery query;
    query.prepare("select * from Equipements where TYPE  LIKE '%soin%'");
    query.exec();
    while(query.next())
        soin++;
    query.prepare("select * from Equipements where TYPE LIKE '%deco%'");
    query.exec();
    while(query.next())
        deco++;
    query.prepare("select * from Equipements where TYPE LIKE '%electro%'");
    query.exec();
    while(query.next())
        electro++;
    query.prepare("select * from Equipements where TYPE LIKE '%autre%'");
    query.exec();
    while(query.next())
       autre++;

     qDebug() << soin << deco << electro << autre ;


     QPieSeries *series0 = new QPieSeries();
         series0->append("soin",soin);
         series0->append("deco",deco);
              series0->append("electro",electro);
         series0->append("autre",autre);


     QPieSlice *slice3 = series0->slices().at(0);
     slice3->setExploded(true);
     slice3->setColor("#81c1b0");
     QPieSlice *slice4 = series0->slices().at(1);
     slice4->setColor("#b081c1");
     QPieSlice *slice5 = series0->slices().at(2);
     slice5->setColor("#f55d11");


     QChart *chart1 = new QChart();
     chart1->addSeries(series0);
    // chart1->setTitle("type statistics");

     series0->setLabelsVisible();

     QChartView *chartView1 = new QChartView(chart1);
     chartView1->setRenderHint(QPainter::Antialiasing);
     chartView1->chart()->setAnimationOptions(QChart::AllAnimations);
     chartView1->chart()->legend()->hide();
     return chartView1;
}
