#ifndef INTERVENANTS_H
#define INTERVENANTS_H
#include <QString>
#include <QDate>
#include<QSqlQuery>
#include <QSqlQueryModel>
#include <Qt>
#include <QtDebug>
#include <QObject>
#include <QImage>

class INTERVENANTS
{
public:
    INTERVENANTS();
    INTERVENANTS(QString nom,QString prenom, int num, QString mdp);
    INTERVENANTS(QString nom,QString prenom,int num,QString mdp,float Sal,QString type,QString etat,QDateTime Date,QByteArray Photo);
    INTERVENANTS(int id,QString nom,QString prenom,int num,float Sal,QString type,QString etat,QDateTime Date,QByteArray Photo);
    INTERVENANTS(int id,QString nom,QString prenom,int num,float Sal,QString type,QString etat,QDateTime Date);

    int getIdIntervenant() const;
       QString getNom() const;
       QString getPrenom() const;
       QString getPhoto() const;
       int getNum() const;
       QDate getDoB() const;
       QString getType() const;
       QString getEtat() const;
       float getSalaire() const;
       QString getMdp() const;

       void setIdIntervenant(int idIntervenant);
       void setNom(QString nom);
       void setPrenom(QString prenom);
       void setPhoto(QString photo);
       void setNum(int num);
       void setDoB(QDate dob);
       void setType(QString type);
       void setEtat(QString etat);
       void setSalaire(float salaire);
       void setMdp(QString mdp);

       bool Signup();
       QSqlQueryModel* afficher();
       bool AjouterIntervenant();
       bool ModifierIntervenant();
       bool ModifierIntervenant1();
       QSqlQueryModel * afficherRecherche(QString NOM);




   private:
       int idIntervenant;
       QString nom;
       QString prenom;
       QByteArray photo;
       int num;
       QDateTime dob;
       QString type;
       QString etat;
       float salaire;
       QString mdp;
   };
void createsession(int id);
void closesession(int id);
#endif // INTERVENANTS_H
