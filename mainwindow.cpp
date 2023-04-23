#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"equipements.h"
#include"connection.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QIntValidator>
#include<QRegExpValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include"Qrcode.h"
#include <QPixmap>

#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtCore/QBuffer>
#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtGui/QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QUrl>
#include <QUrlQuery>
#include<QSystemTrayIcon>
#include<notification.h>
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Notification n ;
      n.notification_ajoutEquipement();

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
      // ui->ajout_TYPE->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
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
           ui->ajout_TYPE_3->setPlaceholderText("Ajoutez le type : Soin,Decor,Autre...");
           ui->ajout_prix->setPlaceholderText("Ajoutez le prix...");
           ui->ajout_descrip->setPlaceholderText("Ajoutez une description...");
           ui->ajout_quantite->setPlaceholderText("Ajoutez la quantité...");
            ui->entrer_recherche->setPlaceholderText("Donner le nom ...");

   //affichage

   ui->table_equip->setModel(E.afficher()); //remplir un tableau via un model

   //NOTIFICATION
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
     ui->stackedWidget_in->setCurrentIndex(3);
}

void MainWindow::on_supprimer_equipement_clicked()
{
  ui->stackedWidget_in->setCurrentIndex(6);
}


void MainWindow::on_consulter_equipement_pb_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::on_consulter_equipement_pb_2_clicked()
{
      ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::on_modifier_equipement_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(2);
}

void MainWindow::on_consulter_equipement_pb_3_clicked()
{
   ui->stackedWidget_in->setCurrentIndex(4);
}


void MainWindow::on_consulter_equipement_pb_4_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(4);
}





void MainWindow::on_validation_ajout_clicked()

{


    //recuperation des infos de l'interface graphique
    int IDEQUIPEMENT=ui->ajout_id->text().toInt();
    QString NOM=ui->ajout_nom->text() ;
    QString DESCRIPTION=ui->ajout_descrip->text();
    QString TYPE=ui->ajout_TYPE_3->text();
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
    ui->table_equip->setModel(E.tri_PrixC());
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









void MainWindow::on_pdf_btn_clicked()
{
    QPdfWriter pdf("C:/Users/zbira/Desktop/Projetameni/pdf/ameni.pdf");
       QPainter painter(&pdf);
      int i = 4000;
           painter.setPen(Qt::red);
           painter.setFont(QFont("Comic Sans MS", 30));
           painter.drawText(1100,1100,"Liste Des Equipemets ");
           //painter.setPen(Qt::blue);
           painter.setFont(QFont("Comic Sans MS", 50));
          // painter.drawRect(100,100,7300,1900);
           //painter.setPen(Qt::blue);
           painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/zbira/Desktop/Projetameni/LOGO.png"));
          // painter.drawRect(0,3000,9600,500);
           painter.setPen(Qt::blue);

           painter.setFont(QFont("Comic Sans MS", 15));
           painter.drawText(200,3300,"Identifiant");
           painter.drawText(1750,3300,"Nom");
           painter.drawText(2800,3300,"Type");
           painter.drawText(3700,3300,"Quantite");
           painter.drawText(5200,3300,"Description");
           painter.drawText(6800,3300,"Prix unitaire");





           QSqlQuery query;
           query.prepare("select * from EQUIPEMENTS");
           query.exec();
           while (query.next())
           {
               painter.setPen(Qt::red);
               painter.drawText(500,i,query.value(0).toString());
               painter.setPen(Qt::black);
               painter.drawText(1800,i,query.value(1).toString());
               painter.drawText(2900,i,query.value(2).toString());
               painter.drawText(4000,i,query.value(3).toString());
               painter.drawText(5200,i,query.value(4).toString());
               painter.drawText(6800,i,query.value(5).toString());


               painter.setPen(Qt::blue);




              i = i + 700;
           }
           int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
               if (reponse == QMessageBox::Yes)
               {
                   QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/zbira/Desktop/Projetameni/pdf/ameni.pdf"));
                   painter.end();
               }
               if (reponse == QMessageBox::No)
               {
                    painter.end();
               }
}



void MainWindow::on_statistic_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(1);
    Equipements e;

    QGridLayout *StatsLayout = ui->stackedWidget_in->findChild<QGridLayout*>("gridLayout");
    StatsLayout->addWidget(e.stat_type(), 0, 0);
}

void MainWindow::on_qrcode_clicked()
{ /*

    int tabeq=ui->table_equip->currentIndex().row(); //track selected item
               QVariant idd=ui->table_equip->model()->data(ui->table_equip->model()->index(tabeq,0));
               QString IDEQUIPEMENT=idd.toString();
               QString QUANTITE=idd.toString();
               QString  PRIX=idd.toString();

               QSqlQuery qry;
               qry.prepare("select * from Equipements where IDEQUIPEMENT=:id");
               qry.bindValue(":id",IDEQUIPEMENT);
               qry.exec();

                QString NOM, DESCRIPTION , TYPE;//attributs



              while(qry.next()){

                 IDEQUIPEMENT=qry.value(1).toString();
                   NOM=qry.value(2).toInt();
                    DESCRIPTION=qry.value(3).toInt();
                TYPE=qry.value(4).toInt();
                  QUANTITE=qry.value(5).toString();
                   PRIX=qry.value(6).toString();



               }
               IDEQUIPEMENT=QString(IDEQUIPEMENT);
                QUANTITE=QString(QUANTITE);
                 PRIX=QString(PRIX);

                       IDEQUIPEMENT="IDEQUIPEMENT:\t" + IDEQUIPEMENT+ "NOM\t:" +NOM+ "DESCRIPTION:\t" +DESCRIPTION+ "TYPE:\t" +TYPE+ "QUANTITE:\t" +QUANTITE+ "PRIX:\t" +PRIX ;
               QrCode qr = QrCode::encodeText(IDEQUIPEMENT.toUtf8().constData(), QrCode::Ecc::HIGH);

               // Read the black & white pixels
               QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
               for (int y = 0; y < qr.getSize(); y++) {
                   for (int x = 0; x < qr.getSize(); x++) {
                       int color = qr.getModule(x, y);  // 0 for white, 1 for black

                       // You need to modify this part
                       if(color==0)
                           im.setPixel(x, y,qRgb(254, 254, 254));
                       else
                           im.setPixel(x, y,qRgb(0, 0, 0));
                   }
               }
               im=im.scaled(200,200);
              ui->qr_code->setPixmap(QPixmap::fromImage(im));
              */
}



void MainWindow::on_table_equip_activated(const QModelIndex &index)
{

    //int tabeq=ui->table_equip->currentIndex().row(); //track selected item


    QString IDEQUIPEMENT=ui->table_equip->model()->data(index).toString();
               QSqlQuery qry;
               qry.prepare("select * from EQUIPEMENTS where IDEQUIPEMENT=:id");
               qry.bindValue(":id",IDEQUIPEMENT);
               qry.exec();

                QString NOM, TYPE,QUANTITE,DESCRIPTION,PRIX;//attributs

              while(qry.next())
              {
                   IDEQUIPEMENT=qry.value(0).toString().simplified();
                            NOM=qry.value(1).toString().simplified();
                            TYPE=qry.value(2).toString().simplified();
                            QUANTITE=qry.value(3).toString().simplified();
                          DESCRIPTION=qry.value(4).toString().simplified();
                              PRIX=qry.value(5).toString().simplified();


               }


                       QString message="Voici les information d'équipement sous l'identifant " + IDEQUIPEMENT +  ": \n" + "\n NOM:" + NOM + "\n TYPE:" +TYPE + "\n QUANTITE: " +QUANTITE+ " \n DESCRIPTION: " +DESCRIPTION+  " \n PRIX unitaire : " +PRIX + "DT" ;
               QrCode qr = QrCode::encodeText(message.toUtf8().constData(), QrCode::Ecc::MEDIUM);

               // Read the black & white pixels
               QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
               for (int y = 0; y < qr.getSize(); y++) {
                   for (int x = 0; x < qr.getSize(); x++) {
                       int color = qr.getModule(x, y);  // 0 for white, 1 for black

                       // You need to modify this part
                       if(color==0)
                           im.setPixel(x, y,qRgb(254, 254, 254));
                       else
                           im.setPixel(x, y,qRgb(0, 0, 0));
                   }
               }
               im=im.scaled(200,200);
              ui->qr_code_3->setPixmap(QPixmap::fromImage(im));



}



void MainWindow::on_pdf_btn_2_clicked()
{
        ui->stackedWidget_in->setCurrentIndex(4);
}
