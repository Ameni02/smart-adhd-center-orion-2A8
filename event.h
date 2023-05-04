#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDateTime>
#include <QByteArray>

#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include <QChartView>

class Event
{

    QString Titre_event,Desc_event,lieuEvent,genre_event,etat_event;
    QDateTime date_event;
    QByteArray image_e;


public:
    Event();
    Event(QString,QString,QString,QString,QString,QDateTime,QByteArray);


    QString getTitre_event(){return Titre_event;}
    QString getDesc_event(){return Desc_event;}
    QString getlieuEvent(){return lieuEvent;}
    QString getgenre_event(){return genre_event;}
    QString getetat_event(){return etat_event;}
    QDateTime getdate_event(){return date_event;}
     //QString getimage_event(){return image_event;}
   // QString getintervenant_event(){return  intervenant_event;}


    void  setTitre_event(QString T){Titre_event=T;}
    void  setDesc_event(QString D){Desc_event=D;}
    void  setlieuEvent(QString L){lieuEvent=L;}
    void  setgenre_event(QString G){genre_event=G;}
    void  setetat_event(QString E){etat_event=E;}
    void  setdate_event(QDateTime da){date_event=da;}
    //void  setimage_event(QString I){image_event=I;}
    //void  setintervenant_event(int inter){intervenant_event=inter;}


    bool ajouter_event();
    QSqlQueryModel * afficher_event();
    bool supprimer_event(int);
    bool modifier_event(int i);
    bool modifier_eventimage(int i);
    QSqlQueryModel * recherche_titreEvent(QString);
    QChartView * stat_gender();
    QChartView *stat_type();
    QSqlQueryModel * trier_event();
    void exportToPDF(QTableView *tableView);
    QSqlQueryModel *trierC();               //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    QSqlQueryModel *trierD();

};

#endif // EVENT_H
