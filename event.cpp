#include "event.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
Event::Event()
{
id_event = 0;
}
Event::Event(int note_event,QString Titre_event, QString Desc_event, QString lieuEvent, QString genre_event, QString etat_event, QDateTime date_event)
{
  this->note_event=note_event;
  this->Desc_event=Desc_event;
  this->lieuEvent=lieuEvent;
  this->Titre_event=Titre_event;
  this->genre_event=genre_event;
  this->etat_event=etat_event;
  this->date_event=date_event;
}
 bool Event::ajouter_event()
 {
     QSqlQuery query;
     QVariant note = QVariant(note_event);
     query.prepare("INSERT INTO Events (NOM,DESCRIPTION,DATEEVENT,LIEU,GENRE,ETAT,NOTE) values (:Titre_event , :Desc_event , :date_event, :lieuEvent , :genre_event ,:etat_event , :note_event )");

     query.bindValue(":note_event",note);
     query.bindValue(":Titre_event",Titre_event);
     query.bindValue(":Desc_event",Desc_event);
     query.bindValue(":date_event",date_event);
     query.bindValue(":lieuEvent",lieuEvent);
     query.bindValue(":genre_event",genre_event);
     query.bindValue(":etat_event",etat_event);

     return query.exec();
 }


