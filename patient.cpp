#include "patient.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlTableModel>
#include<QString>
#include "QByteArray"
#include "QBuffer"
//#include "ImageTableModel.cpp"
Patient::Patient()
{
id_patient = 0;
}

Patient::Patient(QString nom_patient,QString prenom_patient,QDateTime DOB,int num_patient,int num_urg,QString etat_patient,QByteArray photo_patient)
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
  query.prepare("INSERT INTO PATIENTS (NOM,PRENOM,DOB,NUMPERSO,NUMURGENCE,ETAT,PHOTO) values (:nom_patient,:prenom_patient , :DOB,:num_patient , :num_urg, :etat_patient  , :photo_patient)");

  query.bindValue(":nom_patient", nom_patient);
  query.bindValue(":prenom_patient", prenom_patient);
  query.bindValue(":DOB", DOB);
  query.bindValue(":photo_patient", photo_patient);
  query.bindValue(":num_patient", nup);
  query.bindValue(":num_urg", nur);
  query.bindValue(":etat_patient", etat_patient);

  return query.exec();
}


QSqlQueryModel * Patient::afficher_patient()
 {
   QSqlQueryModel* model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM PATIENTS");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date De Naissance"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numero Personelle"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Numero d'urgence"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Point Dex Recompence"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Photo"));

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
bool Patient::modifier(int i)
{

    QSqlQuery query;
    QVariant nup = QVariant(num_patient);
    QVariant nur = QVariant(num_urg);
        query.prepare("UPDATE PATIENTS SET NOM=:nom_patient , PRENOM=:prenom_patient , DOB=:DOB , PHOTO= :photo_patient , NUMPERSO = :num_patient,NUMURGENCE=:num_urg , ETAT=:etat_patient  WHERE IDPATIENT=:id_patient");
        query.bindValue(":id_patient",i);
        query.bindValue(":nom_patient",nom_patient);
        query.bindValue(":prenom_patient",prenom_patient);
        query.bindValue(":DOB",DOB);
        query.bindValue(":photo_patient",photo_patient);
        query.bindValue(":num_patient",nup);
        query.bindValue(":num_urg",nur);
        query.bindValue(":etat_patient",etat_patient);
        return query.exec();

}

QSqlQueryModel * Patient::afficherRecherche(QString NOM)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from PATIENTS WHERE NOM LIKE '%"+NOM+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    return model;
}

