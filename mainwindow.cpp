#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"equipements.h"
#include"connection.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QIntValidator>
#include<QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    //ctrl de saisie number
   ui->ajout_id->setValidator(new QIntValidator(1000,9999, this));
   ui->ajout_quantite->setValidator(new QIntValidator(0,9999, this));
   ui->ajout_prix->setValidator(new QIntValidator(0,9999999, this));
 //ctrl de saisie string
   QRegExpValidator *validator = new QRegExpValidator(QRegExp("[a-zA-Z]+"), ui->ajout_nom);
   ui->ajout_nom->setValidator(validator);
*/
    //ctrl de saisie
    ui->ajout_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
       ui->ajout_nom->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{10}")));
       ui->ajout_TYPE->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
       ui->ajout_prix->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}")));
       ui->ajout_descrip->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{100}")));
       ui->ajout_quantite->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}")));
       ui->id_supp->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
       ui->ajout_id_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
          ui->ajout_nom_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{10}")));
          ui->ajout_TYPE_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
          ui->ajout_prix_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}")));
          ui->ajout_descrip_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{100}")));
          ui->ajout_quantite_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}")));


       // placeholder
       ui->ajout_id->setPlaceholderText("Ajoutez l'id...");
           ui->ajout_nom->setPlaceholderText("Ajoutez le nom...");
           ui->ajout_TYPE->setPlaceholderText("Ajoutez le type...");
           ui->ajout_prix->setPlaceholderText("Ajoutez le prix...");
           ui->ajout_descrip->setPlaceholderText("Ajoutez une description...");
           ui->ajout_quantite->setPlaceholderText("Ajoutez la quantité...");
            ui->entrer_recherche->setPlaceholderText("Donner le nom ...");
   //affichage

   ui->table_equip->setModel(E.afficher()); //remplir un tableau via un model
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ajouter_equipement_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(0);
}
void MainWindow::on_Ajouter_equipement_2_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(0);
}


void MainWindow::on_Equipements_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(2);
}

void MainWindow::on_supprimer_equipement_clicked()
{
  ui->stackedWidget_in->setCurrentIndex(4);
}


void MainWindow::on_consulter_equipement_pb_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(3);
}

void MainWindow::on_consulter_equipement_pb_2_clicked()
{
      ui->stackedWidget_in->setCurrentIndex(3);
}

void MainWindow::on_modifier_equipement_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_consulter_equipement_pb_3_clicked()
{
   ui->stackedWidget_in->setCurrentIndex(3);
}


void MainWindow::on_consulter_equipement_pb_4_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(3);
}





void MainWindow::on_validation_ajout_clicked()

{
    //recuperation des infos de l'interface graphique
    int IDEQUIPEMENT=ui->ajout_id->text().toInt();
    QString NOM=ui->ajout_nom->text() ;
    QString DESCRIPTION=ui->ajout_descrip->text();
    QString TYPE=ui->ajout_TYPE->text();
    int QUANTITE=ui->ajout_quantite->text().toInt();
    int PRIX=ui->ajout_prix->text().toInt();


  Equipements E( IDEQUIPEMENT,NOM ,DESCRIPTION,TYPE,QUANTITE,PRIX ); //instancier un objet de la classe equipement
                                                                    //en utilisant les infos saisies dans l'interface
  if (NOM.isEmpty()) {
      QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                  QObject::tr(" il faut ajouter un nom.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      return;
  }
  if (DESCRIPTION.isEmpty()) {
      QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                  QObject::tr(" il faut ajouter une description.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      return;
  }
  if (TYPE.isEmpty()) {
      QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                  QObject::tr(" il faut préciser le type.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      return;
  }

  bool test=E.ajouter(); //insertion dans la table et recuperer

  if(test) //si la requete executée
  {


      QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("bien ajouté.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
      //refresh
 ui->table_equip->setModel(E.afficher());
         }
             else

  {

                 QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                             QObject::tr("non ajouté.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
  }
}





void MainWindow::on_SUPP_clicked()
{

E.setIDEQUIPEMENT(ui->id_supp->text().toInt()); //recuperer id au niveau de l'interface graphique


bool test=E.supprimer(E.getIDEQUIPEMENT()); //Appel de la méthode supprimer() via l’attribut E

if(test)
{
    //refresh

    QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("bien supprimé.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
 ui->table_equip->setModel(E.afficher());
       }
           else
{
               QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                           QObject::tr("non supprimé.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

}








void MainWindow::on_search_btn_clicked()
{
    ui->table_equip->setModel(E.recherche_NOM(ui->entrer_recherche->text()));

/*
                    QMessageBox::information(nullptr,QObject::tr("OK"),
                                              QObject::tr("recherche done.\n"
                                                          "clic cancel to exit."),QMessageBox::Cancel); */
}

void MainWindow::on_tri_btn_clicked()
{
    ui->table_equip->setModel(E.tri_id());
}

void MainWindow::on_tri_btn_2_clicked()
{
    ui->table_equip->setModel(E.tri_alphabetique());
}

void MainWindow::on_modifier_equipement_2_clicked()
{
    int IDEQUIPEMENT=ui->ajout_id_2->text().toInt();
    QString NOM=ui->ajout_nom_2->text() ;
    QString DESCRIPTION=ui->ajout_descrip_2->text();
    QString TYPE=ui->ajout_TYPE_2->text();
    int QUANTITE=ui->ajout_quantite_2->text().toInt();
    int PRIX=ui->ajout_prix_2->text().toInt();
             Equipements E( IDEQUIPEMENT,NOM ,DESCRIPTION,TYPE,QUANTITE,PRIX );
              bool test=E.modifier( IDEQUIPEMENT);
              if (test)
              {

                  QMessageBox::information(nullptr, QObject::tr("OK"),
                                         QObject::tr("bien modifié.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
               ui->table_equip->setModel(E.afficher());
                     }
                         else
              {
                             QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                                         QObject::tr("non modifié.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
              }

}





