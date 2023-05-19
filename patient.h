#ifndef PATIENT_H
#define PATIENT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlTableModel>
#include<QDateTime>

class Patient
{
    int id_patient,num_patient,num_urg,point ;
    QString nom_patient,prenom_patient,etat_patient,mailpat;
    QDateTime DOB;
    QByteArray photo_patient;
public:
    Patient();
    Patient(QString,QString,QDateTime,int,int,QString,QByteArray,QString);


    QString getnom_patient(){return nom_patient;}
    QString getprenom_patient(){return prenom_patient;}
    QByteArray getphoto_patient(){return photo_patient;}
    QDateTime getDOB(){return DOB;}
    int getnum_patient(){return num_patient;}
    int getnum_urg(){return num_urg;}
    QString getetat_patient(){return etat_patient;}
    int getpoint(){return point;}
    QString getmailpat(){return mailpat;}


    void  setnom_patient(QString np){nom_patient=np;}
    void  setprenom_patient(QString pp){prenom_patient=pp;}
    void  setphoto_patient(QByteArray php){photo_patient=php;}
    void  setDOB(QDateTime dob){dob=DOB;}
    void  setnum_patient(int nup){num_patient=nup;}
    void  setnum_urg(int nur){num_urg=nur;}
    void  setetat_patient(QString ep){etat_patient=ep;}
    void  setpoint(int pnt){point=pnt;}
    void  setmailpat(QString mp){mailpat=mp;}


    bool ajouter_patient();
    QSqlQueryModel * afficher_patient();
    bool supprimer_patient(int);
    bool modifier(int);
    QSqlQueryModel *afficherRecherche(QString );

    bool supprimer_patients();
};

#endif // PATIENT_H
