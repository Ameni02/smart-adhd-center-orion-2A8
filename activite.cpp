#include "activite.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtSql/QSqlQuery>
#include <QApplication>
#include <QCalendarWidget>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QtCore/QtDebug>


activite::activite()
{
idactivite=0;
Nom=" ";
Description=" ";
Genre=" ";
Cible=" ";

}
activite::activite(int idactivite,QString Nom,QString Description,QString Genre,QString Cible)
{
    this->idactivite=idactivite;
    this->Nom=Nom;
    this->Description=Description;
    this->Genre=Genre;
    this->Cible=Cible;


}
Tache::Tache()
{
    idtache=0;
    Nom_inter=" ";
    Nom_tache=" ";
    Etat=" ";
}
Tache::Tache(int idtache, QString Nom_inter, QString Nom_tache, QString Etat)
{
    this->idtache=idtache;
    this->Nom_inter=Nom_inter;
    this->Nom_tache=Nom_tache;
    this->Etat=Etat;
}

int activite::getid(){
    return idactivite;
}
QString activite::getnom(){
    return Nom;
}
QString activite::getdescription(){
    return Description;
}
QString activite::getgenre(){
    return Genre;
}
QString activite::getcible(){
    return Cible;
}


void activite::setid(int idactivite)
{
    this->idactivite=idactivite;
}

void activite::setnom(QString Nom)
{
    this->Nom=Nom;
}
void activite::setcible(QString Cible)
{
    this->Cible=Cible;
}
void activite::setgenre(QString Genre)
{
    this->Genre=Genre;
}
void activite::setdescription(QString Description)
{
    this->Description=Description;
}
bool activite::ajouter()
{

    QSqlQuery query;
    QString res = QString::number(idactivite);
    query.prepare("insert into ACTIVITES (IDACTIVITE, NOM, DESCRIPTION, GENRE, CIBLE)"
                  "VALUES (:idactivite, :Nom, :Description, :Genre, :Cible)");
    query.bindValue(":idactivite",res);
    query.bindValue(":Nom",Nom);
query.bindValue(":Description",Description);
query.bindValue(":Genre",Genre);
query.bindValue(":Cible",Cible);


return query.exec();
}

QSqlQueryModel* activite::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM ACTIVITES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Idactivite"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("Description"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cible"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("Genre"));
       return model;
}


//tache
bool Tache::ajouter_tache()
{

    QSqlQuery query;
    QString res1 = QString::number(idtache);
    query.prepare("insert into TACHE (IDTACHE,NOMINTERVENANT, NOMTACHE, ETAT)"
                  "VALUES (:idtache, :Nom_inter ,:Nom_tache, :Etat)");
    query.bindValue(":idtache",res1);
    query.bindValue(":Nom_inter",Nom_inter);
    query.bindValue(":Nom_tache",Nom_tache);
    query.bindValue(":Etat",Etat);

return query.exec();
}
QSqlQueryModel* Tache::afficher_tache()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM TACHE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDTACHE"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMINTERVENANT"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOMTACHE"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));
 return model;
}




bool activite::supprmier(int id)
{
    QSqlQuery query;

    query.prepare(" Delete from ACTIVITES where IDACTIVITE=:id");
    query.bindValue(0,id);

return query.exec();

    return query.exec();
}

bool activite::modifier(int idactivite)
{

    QSqlQuery query;
        QString id_string=QString::number(idactivite);
        query.prepare("UPDATE activites SET Nom= :Nom,Description= :Description,Genre= :Genre,Cible= :Cible  WHERE idactivite= :idactivite");
        query.bindValue(":idactivite", id_string);
        query.bindValue(":Nom", Nom);
        query.bindValue(":Description", Description);
        query.bindValue(":Genre", Genre);
        query.bindValue(":Cible", Cible);
        if(!query.exec())
        {
            qDebug()<<"failed ";

        }
        else
{
        return query.exec();
}
}
QSqlQueryModel * activite::recherche_NOM(QString NOM)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from ACTIVITES WHERE NOM LIKE '%"+NOM+"%'");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Idactivite"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("Description"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("Cible"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("Genre"));
    return model;
}
QSqlQueryModel *activite :: tri_croissant()
{
     QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select *from ACTIVITES ORDER BY GENRE ASC");
     return model;

}
QSqlQueryModel *activite :: tri_decroissant()
{
     QSqlQueryModel * model = new QSqlQueryModel();
     model->setQuery("select *from ACTIVITES ORDER BY GENRE DESC");
     return model;

}
QChartView *activite::Stat()
{
    int enfant=0;
    int adulte=0;


    QSqlQuery query;
    query.prepare("SELECT *from ACTIVITES WHERE CIBLE='Enfant'");
    query.exec();
    while(query.next())
        enfant++;

    query.prepare("SELECT *from ACTIVITES WHERE CIBLE='Adulte'");
    query.exec();
    while(query.next())
        adulte++;

     qDebug() << enfant << adulte  ;

     QPieSeries *Series = new QPieSeries();
         Series->append("Les activites faites par les enfants",enfant);
         Series->append("Les activites faites par les adultes",adulte);


         QPieSlice *slice = Series->slices().at(0);
         slice->setExploded(true);
         slice->setColor("#ffdaac");
         QPieSlice *slice2 = Series->slices().at(1);
         slice2->setColor("#990000");

         QChart *chart = new QChart();
         chart->addSeries(Series);
         chart->setTitle("Statsitques des activité par rapport au cible");

         Series->setLabelsVisible();

         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->chart()->setAnimationOptions(QChart::AllAnimations);
         chartView->chart()->legend()->hide();
         return chartView;
}

void ajouterActivite(QCalendarWidget *calendrier)
{

    // Récupérer la date sélectionnée
    QDate date = calendrier->selectedDate();

    // Afficher une boîte de dialogue pour saisir les détails de l'activité
    QDialog dialog(calendrier);
    dialog.setWindowTitle("Ajouter une activité");
    dialog.setMinimumSize(300, 200);

    QLabel *titreLabel = new QLabel("Titre :", &dialog);
    QLineEdit *titreEdit = new QLineEdit(&dialog);
    titreLabel->setBuddy(titreEdit);

    QLabel *descriptionLabel = new QLabel("Description :", &dialog);
    QTextEdit *descriptionEdit = new QTextEdit(&dialog);
    descriptionLabel->setBuddy(descriptionEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    QFormLayout *layout = new QFormLayout(&dialog);
    layout->addRow(titreLabel, titreEdit);
    layout->addRow(descriptionLabel, descriptionEdit);
    layout->addRow(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        // Ajouter l'activité à une liste ou une base de données
        QString titre = titreEdit->text();
        QString description = descriptionEdit->toPlainText();
        // ...

        // Mettre à jour la vue du calendrier pour afficher la nouvelle activité
        QTextCharFormat newFormat;
        newFormat.setBackground(Qt::yellow);
        calendrier->setDateTextFormat(date, newFormat);
    }
}
/*
void ajouterActivite(QCalendarWidget *calendrier)
{
    // Récupérer la date sélectionnée
    QDate date = calendrier->selectedDate();

    // Vérifier si une activité existe pour cette date
    bool activiteExistante = checkActiviteExistante(date); // À implémenter

    // Afficher une boîte de dialogue pour saisir les détails de l'activité
    QDialog dialog(calendrier);
    dialog.setWindowTitle("Ajouter une activité");
    dialog.setMinimumSize(300, 200);

    QLabel *titreLabel = new QLabel("Titre :", &dialog);
    QLineEdit *titreEdit = new QLineEdit(&dialog);
    titreLabel->setBuddy(titreEdit);

    QLabel *descriptionLabel = new QLabel("Description :", &dialog);
    QTextEdit *descriptionEdit = new QTextEdit(&dialog);
    descriptionLabel->setBuddy(descriptionEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    QFormLayout *layout = new QFormLayout(&dialog);
    layout->addRow(titreLabel, titreEdit);
    layout->addRow(descriptionLabel, descriptionEdit);
    layout->addRow(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        // Ajouter l'activité à une liste ou une base de données
        QString titre = titreEdit->text();
        QString description = descriptionEdit->toPlainText();
        // ...

        // Mettre à jour la vue du calendrier pour afficher la nouvelle activité
        if (activiteExistante) {
            QTextCharFormat existingFormat = calendrier->dateTextFormat(date);
            existingFormat.setBackground(Qt::yellow);
            calendrier->setDateTextFormat(date, existingFormat);
        } else {
            QTextCharFormat newFormat;
            newFormat.setBackground(Qt::yellow);
            calendrier->setDateTextFormat(date, newFormat);
        }
    }
}

*/

