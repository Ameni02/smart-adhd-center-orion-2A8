#include "event.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include <QObject>
#include <QLCDNumber>
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QtGui>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QByteArray>

Event::Event()
{

}


Event::Event(QString Titre_event, QString Desc_event, QString lieuEvent, QString genre_event, QString etat_event, QDateTime date_event,QByteArray image_e)
{

  this->Desc_event=Desc_event;
  this->lieuEvent=lieuEvent;
  this->Titre_event=Titre_event;
  this->genre_event=genre_event;
  this->etat_event=etat_event;
  this->date_event=date_event;

   this->image_e=image_e;


}

 bool Event::ajouter_event()
 {



     QSqlQuery query;

      //QVariant id = QVariant(id_event);
query.prepare("INSERT INTO EVENTS (NOM,DESCRIPTION,DATEEVENT,LIEU,GENRE,ETAT,AFFICHE)""VALUES(:Titre_event, :Desc_event, :date_event, :lieuEvent, :genre_event, :etat_event, :image_e)");



     // query.bindValue(":id_event",id);

     query.bindValue(":Titre_event",Titre_event);
     query.bindValue(":Desc_event",Desc_event);
     query.bindValue(":date_event",date_event);
     query.bindValue(":lieuEvent",lieuEvent);
     query.bindValue(":genre_event",genre_event);
     query.bindValue(":etat_event",etat_event);
     query.bindValue(":image_e",image_e);
     //query.bindValue(":intervenant_event",intervenant_event);




     return query.exec();
 }
  QSqlQueryModel * Event::afficher_event()
  {
      QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("SELECT * FROM Events");
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("IDEVENT"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("DESCRIPTION"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATEEVENT"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("LIEU"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("GENRE"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("ETAT"));

      return model;
  }
    bool Event::supprimer_event(int id)
    {
        QSqlQuery query;
        //QString res=QString::number(id);
        query.prepare("DELETE FROM EVENTS where IDEVENT= :id ");
        query.bindValue(":id",id);
         return query.exec();
    }

   bool Event::modifier_event(int id)
   {
       QSqlQuery query;
       query.prepare("UPDATE EVENTS set NOM=:Titre_event,DESCRIPTION=:Desc_event,DATEEVENT=:date_event,LIEU=:lieuEvent,GENRE=:genre_event,ETAT=:etat_event where IDEVENT=:id");
       query.bindValue(":id",id);
       query.bindValue(":Titre_event",Titre_event);
       query.bindValue(":Desc_event",Desc_event);
       query.bindValue(":date_event",date_event);
       query.bindValue(":lieuEvent",lieuEvent);
       query.bindValue(":genre_event",genre_event);
       query.bindValue(":etat_event",etat_event);
       //query.bindValue(":image_e",image_e);
       //query.bindValue(":intervenant_event",intervenant_event);
       qDebug() << "Updated";
       return query.exec();

   }

   bool Event::modifier_eventimage(int id)
   {
       QSqlQuery query;
       query.prepare("update EVENTS set NOM=:Titre_event,DESCRIPTION=:Desc_event,DATEEVENT=:date_event,LIEU=:lieuEvent,GENRE=:genre_event,ETAT=:etat_event,AFFICHE=:image_e where IDEVENT=:id");
       query.bindValue(":id",id);
       query.bindValue(":Titre_event",Titre_event);
       query.bindValue(":Desc_event",Desc_event);
       query.bindValue(":date_event",date_event);
       query.bindValue(":lieuEvent",lieuEvent);
       query.bindValue(":genre_event",genre_event);
       query.bindValue(":etat_event",etat_event);
       query.bindValue(":image_e",image_e);
       //query.bindValue(":intervenant_event",intervenant_event);
       qDebug() << "Updated";
       return query.exec();

   }


