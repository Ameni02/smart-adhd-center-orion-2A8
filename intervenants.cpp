#include "intervenants.h"

INTERVENANTS::INTERVENANTS()
{

}
bool INTERVENANTS::Signup()
{
    QSqlQuery query;
    query.prepare("INSERT INTO INTERVENANTS (NOM,PRENOM,NUM,MDP) values (:nom , :prenom , :num, :mdp)");

    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":num",num);
    query.bindValue(":mdp",mdp);
    return query.exec();
}

INTERVENANTS::INTERVENANTS(QString nom,QString prenom, int num, QString mdp)
{
  this->nom=nom;
  this->prenom=prenom;
  this->num=num;
  this->mdp=mdp;
}
INTERVENANTS::INTERVENANTS(QString nom,QString prenom,int num,QString mdp,float Sal,QString type,QString etat,QDateTime date,QByteArray Photo)
{
    this->nom=nom;
    this->prenom=prenom;
    this->num=num;
    this->mdp=mdp;
    this->salaire=Sal;
    this->type=type;
    this->etat=etat;
    this->dob=date;
    this->photo=Photo;
}

INTERVENANTS::INTERVENANTS(int id,QString nom,QString prenom,int num,float Sal,QString type,QString etat,QDateTime date,QByteArray Photo)
{
    this->idIntervenant = id;
    this->nom=nom;
    this->prenom=prenom;
    this->num=num;
    this->salaire=Sal;
    this->type=type;
    this->etat=etat;
    this->dob=date;
    this->photo=Photo;
}

INTERVENANTS::INTERVENANTS(int id,QString nom,QString prenom,int num,float Sal,QString type,QString etat,QDateTime date)
{
    this->idIntervenant = id;
    this->nom=nom;
    this->prenom=prenom;
    this->num=num;
    this->salaire=Sal;
    this->type=type;
    this->etat=etat;
    this->dob=date;
}

void createsession(int id)
{
    QSqlQuery query;
    query.prepare("INSERT INTO SESSIONS (IDINTERVENANT) values (:id)");
    query.bindValue(":id",id);
    query.exec();
}

void closesession(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SESSIONS WHERE IDINTERVENANT = :id");
    query.bindValue(":id",id);
    query.exec();
}

QSqlQueryModel* INTERVENANTS::afficher()
{
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("Select IDINTERVENANT,NOM,PRENOM,NUM,DOB,TYPE,ETAT,SALAIRE from INTERVENANTS");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Phone Number"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date Of Birth"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Type"));
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("Etat"));
     model->setHeaderData(7,Qt::Horizontal,QObject::tr("Salary"));
return model;
}

bool INTERVENANTS::AjouterIntervenant()
{
    QSqlQuery query;
    query.prepare("INSERT INTO INTERVENANTS (NOM,PRENOM,NUM,MDP,SALAIRE,TYPE,ETAT,DOB,PHOTO) values (:nom , :prenom , :num, :mdp, :salaire, :Type, :Etat, :dob, :photo)");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":num",num);
    query.bindValue(":mdp",mdp);
    query.bindValue(":salaire",salaire);
    query.bindValue(":Type",type);
    query.bindValue(":Etat",etat);
    query.bindValue(":dob",dob);
    query.bindValue(":photo",photo);
    return query.exec();
}


bool INTERVENANTS::ModifierIntervenant()
{
    QSqlQuery query;
    query.prepare("UPDATE INTERVENANTS SET NOM = :nom, PRENOM= :prenom,NUM = :num,SALAIRE = :salaire, TYPE= :Type,ETAT= :Etat, DOB= :dob, PHOTO = :photo WHERE IDIntervenant = :id");
    query.bindValue(":id",idIntervenant);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":num",num);
    query.bindValue(":salaire",salaire);
    query.bindValue(":Type",type);
    query.bindValue(":Etat",etat);
    query.bindValue(":dob",dob);
    query.bindValue(":photo",photo);
    return query.exec();
}



bool INTERVENANTS::ModifierIntervenant1()
{
    QSqlQuery query;
    query.prepare("UPDATE INTERVENANTS SET NOM = :nom, PRENOM= :prenom,NUM = :num,SALAIRE = :salaire, TYPE= :Type,ETAT= :Etat, DOB= :dob WHERE IDIntervenant = :id");
    query.bindValue(":id",idIntervenant);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":num",num);
    query.bindValue(":salaire",salaire);
    query.bindValue(":Type",type);
    query.bindValue(":Etat",etat);
    query.bindValue(":dob",dob);
    return query.exec();
}
