#ifndef PATIENT_H
#define PATIENT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDateTime>

class Patient
{
    int id_patient,num_patient,num_urg ;
    QString nom_patient,prenom_patient,photo_patient,etat_patient;
    QDateTime DOB;
public:
    Patient();
    Patient(QString,QString,QDateTime,QString,int,int,QString);


    QString getnom_patient(){return nom_patient;}
    QString getprenom_patient(){return prenom_patient;}
    QString getphoto_patient(){return photo_patient;}
    QDateTime getDOB(){return DOB;}
    int getnum_patient(){return num_patient;}
    int getnum_urg(){return num_urg;}
    QString getetat_patient(){return etat_patient;}


    void  setnom_patient(QString np){nom_patient=np;}
    void  setprenom_patient(QString pp){prenom_patient=pp;}
    void  setphoto_patient(QString php){photo_patient=php;}
    void  setDOB(QDateTime dob){dob=DOB;}
    void  setnum_patient(int nup){num_patient=nup;}
    void  setnum_urg(int nur){num_urg=nur;}
    void  setetat_patient(QString ep){etat_patient=ep;}


    bool ajouter_patient();
    QSqlQueryModel * afficher_patient();
    bool supprimer_patient(int);
};

#endif // PATIENT_H
