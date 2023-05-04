#ifndef EQUIPEMENTS_H
#define EQUIPEMENTS_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include <QChartView>




class Equipements
{
  QString NOM, DESCRIPTION , TYPE ;
int   IDEQUIPEMENT , QUANTITE,PRIX ;
public:
    //constructeurs
    Equipements(){}
    Equipements(int,QString,QString,QString,int,int);
    //getters
    int getIDEQUIPEMENT(){return IDEQUIPEMENT; }
    QString getnom (){return NOM; }
    QString getDESCRIPTION (){return DESCRIPTION; }
    QString gettype (){return TYPE; }
    int getquantite(){return QUANTITE; }
    int getprix(){return PRIX; }
//Setters
    void setIDEQUIPEMENT(int IDEQUIPEMENT ){this->IDEQUIPEMENT=IDEQUIPEMENT;}
    void setnom (QString no){NOM=no;}
    void setDESCRIPTION (QString PH){DESCRIPTION=PH;}
    void settype (QString TY){TYPE=TY;}
    void setquantite(int QUANTITE){this->QUANTITE=QUANTITE;}
    void setprix(int PRIX){this->PRIX=PRIX;}
    //fonction
    bool ajouter();
    QSqlQueryModel* afficher(); //retourner un tableau de QSqlQueryModel
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel * recherche_NOM(QString);
    QSqlQueryModel * tri_PrixC();
    QSqlQueryModel * tri_alphabetique();
    QChartView *stat_type();


};


#endif // EQUIPEMENTS_H
