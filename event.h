#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDateTime>

class Event
{
    int id_event,note_event ;
    QString Titre_event,Desc_event,lieuEvent,genre_event,etat_event;
    QDateTime date_event;
public:
    Event();
    Event(int,QString,QString,QString,QString,QString,QDateTime);


    QString getTitre_event(){return Titre_event;}
    QString getDesc_event(){return Desc_event;}
    QString getlieuEvent(){return lieuEvent;}
    QString getgenre_event(){return genre_event;}
    QString getetat_event(){return etat_event;}
    QDateTime getdate_event(){return date_event;}
    int getnote_event(){return  note_event;}


    void  setTitre_event(QString T){Titre_event=T;}
    void  setDesc_event(QString D){Desc_event=D;}
    void  setlieuEvent(QString L){lieuEvent=L;}
    void  setgenre_event(QString G){genre_event=G;}
    void  setetat_event(QString E){etat_event=E;}
    void  setdate_event(QDateTime da){date_event=da;}
    void  setnote_event(int note){note_event=note;}


    bool ajouter_event();
    QSqlQueryModel * afficher_event();
    bool supprimer_event(int);
};

#endif // EVENT_H
