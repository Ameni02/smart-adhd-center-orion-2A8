#include "patient.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
Patient::Patient()
{
id_patient = 0;
}
Patient::Patient(QString nom_patient,QString prenom_patient,QDateTime DOB,QString photo_patient,int num_patient,int num_urg,QString etat_patient)
{

  this->nom_patient=nom_patient;
  this->prenom_patient=prenom_patient;
  this->DOB=DOB;
  this->photo_patient=photo_patient;
  this->num_patient=num_patient;
  this->num_urg=num_urg;
  this->etat_patient=etat_patient;
}
 bool Patient::ajouter_patient()
 {
     QSqlQuery query;
     QVariant nup = QVariant(num_patient);
     QVariant nur = QVariant(num_urg);
     query.prepare("INSERT INTO PATIENTS (NOM,PRENOM,DOB,PHOTO,NUMPERSO,NUMURGENCE,ETAT) values (:nom_patient,:prenom_patient , :DOB , :photo_patient,:num_patient , :num_urg, :etat_patient  )");

     query.bindValue(":nom_patient",nom_patient);
     query.bindValue(":prenom_patient",prenom_patient);
     query.bindValue(":DOB",DOB);
     query.bindValue(":photo_patient",photo_patient);
     query.bindValue(":num_patient",num_patient);
     query.bindValue(":num_urg",num_urg);
     query.bindValue(":etat_patient",etat_patient);

     return query.exec();
 }
QSqlQueryModel * Patient::afficher_patient()
 {
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENTS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    return model;
 }
bool Patient::supprimer_patient(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("DELETE FROM PATIENTS where IDPATIENT= :id");
    query.bindValue(":id",res);
    return query.exec();
}