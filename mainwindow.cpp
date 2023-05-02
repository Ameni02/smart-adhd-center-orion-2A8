#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"equipements.h"
#include"connection.h"
#include"Qrcode.h"
#include "event.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QIntValidator>
#include<QRegExpValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
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
#include <QFileDialog>
#include <QMessageBox>
#include <QDateEdit>
#include <QLabel>
#include <QMovie>
#include <QtGui>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QComboBox>
#include <QCheckBox>
#include<QDateTime>
#include <QPrinter>
#include <QStandardPaths>
#include <QPrintDialog>
#include <QAxBase>


using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).




    Notification n ;
      n.notification_ajoutEquipement();
      //Evenements///////////////////////
      //refrech l'affichage
      ui->tableView_events->setModel(Evt.afficher_event());

     //controle de saisir
      // ui->l_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
      ui->lineEditTitre_event->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
      ui->lineEdit_Desc->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
      ui->lineEdit_lieuEvent->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
      //ui->lineEdit_EtatEvent->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
      ui->lineEdit_chercheEvent->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

  //AFFICHAGE DE COMBOX DE LES ID
      QComboBox *Combodelete = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_suppr");
      Combodelete->clear();
      QSqlQuery query_delate;
      query_delate.prepare("SELECT IDEVENT FROM EVENTS");
  // Executing the query and fetching the IDEVENT from the result set
      if (query_delate.exec()) {
          while (query_delate.next()) {
              int id=query_delate.value(0).toInt();
              // Convert the IDEVENT to a string format
              QString intString = QString::number(id);
              // Add the string representation of the ID_EM to the combobox
              Combodelete->addItem(intString);
          }
      }
  //AFFICHAGE DE COMBOX DE LES NOM POUR LA PAGE DE DETAILS EVENTS
      QComboBox *ComboSELECT = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_selest");
      ComboSELECT->clear();
      ComboSELECT->addItem("Select a name of event");

      QSqlQuery query_SELECT;
      query_SELECT.prepare("SELECT NOM FROM EVENTS");

      // Executing the query and fetching the NAME column from the result set
      if (query_SELECT.exec()) {
          while (query_SELECT.next()) {
              QString name = query_SELECT.value(0).toString();
              // Add the name to the combobox
              ComboSELECT->addItem(name);
          }
      }


      //AFFICHAGE DE COMBOX DE LES ID
          QComboBox *comboBox_emmisionCO2 = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_emmisionCO2");
          comboBox_emmisionCO2->clear();
          QSqlQuery query_emmisionCO2;
          query_emmisionCO2.prepare("SELECT IDEVENT FROM EVENTS");
      // Executing the query and fetching the IDEVENT from the result set
          if (query_emmisionCO2.exec()) {
              while (query_emmisionCO2.next()) {
                  int id=query_emmisionCO2.value(0).toInt();
                  // Convert the IDEVENT to a string format
                  QString intString = QString::number(id);
                  // Add the string representation of the ID_EM to the combobox
                  comboBox_emmisionCO2->addItem(intString);
              }
          }

  //comptage des  events

         QSqlQuery query;
         int row_count = 0;
         query.exec("SELECT COUNT(*) FROM EVENTS");
         if(query.first())
         row_count = query.value(0).toInt();
         QLCDNumber *lcdNumber = this->findChild<QLCDNumber*>("lcdNumber");
         ui->lcdNumber->display(row_count);
         ui->tableView_events->setModel(Evt.afficher_event());
/*

  //ajouter des GIF
      QMovie *gif_log = new QMovie("C:\\Users\\Mozrani amine\\Desktop\\cap arduino\\gif1.gif");
      QMovie *gif_profif = new QMovie("C:\\Users\\Mozrani amine\\Desktop\\cap arduino\\hello_GIF.gif");
      QMovie *gif_nbEvent = new QMovie("C:\\Users\\Mozrani amine\\Desktop\\cap arduino\\GIF_event.gif");

      ui->label_GIF->setMovie(gif_log);
      ui->label_GIF_2->setMovie(gif_profif);
      ui->label_nbGIF->setMovie(gif_nbEvent);
      gif_log->start();
      gif_profif->start();
      gif_nbEvent->start();
      ui->label_GIF_2->setFixedSize(481,371);
     //ui->label_nbGIF->setFixedSize(161,131);
*/
      QSettings settings(QSettings::IniFormat, QSettings::UserScope,QCoreApplication::organizationName(), QCoreApplication::applicationName());
      ui->axWidget->dynamicCall("Navigate(const QString&)", "file:///C:/Users/zbira/Desktop/integration_ameni-sarahindex.html");






                     //Activité///////////////////////////////////

      //ui->l_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
        ui->l_nom->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
           ui->l_description->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

              ui->l_genre->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));


              ui->l_id_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
               ui->l_nom_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
                  ui->l_description_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

                     ui->l_genre_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

                     ui->table_act->setModel(Act.afficher()); //chercher

                     QComboBox *ComboCLADER = ui->stackedWidget_in->findChild<QComboBox*>("comboBoxcalander");
                         ComboCLADER->clear();

                         QSqlQuery query_CALANDER;
                         query_CALANDER.prepare("SELECT IDACTIVITE FROM ACTIVITES");
                     // Executing the query and fetching the IDEVENT from the result set
                         if (query_CALANDER.exec()) {
                             while (query_CALANDER.next()) {
                                 int id=query_CALANDER.value(0).toInt();
                                 // Convert the IDEVENT to a string format
                                 QString intString = QString::number(id);
                                 // Add the string representation of the ID_EM to the combobox
                                 ComboCLADER->addItem(intString);


                             }
                         }
   //style agenda


                  /*       QString styleSheet = "QCalendarWidget QAbstractItemView:enabled {"
                                              "background-color: #F0D9FF;"
                                              "color: #000000;"
                                              "selection-background-color: #FFCCCC;"
                                              "selection-color: #FFFFCC;"
                                              "}";

                         ui->calendarWidget->setStyleSheet(styleSheet);
                          QTextCharFormat format = ui->calendarWidget->weekdayTextFormat(Qt::Saturday);
                             format.setForeground(QBrush(Qt::black, Qt::SolidPattern));*/
                             ui->calendarWidget->setStyleSheet("background-color :rgb(240,217,255);selection-background-color:rgb(207, 77, 206);");

    /*
    //ctrl de saisie number
   ui->ajout_id->setValidator(new QIntValidator(1000,9999, this));
   ui->ajout_quantite->setValidator(new QIntValidator(0,9999, this));
   ui->ajout_prix->setValidator(new QIntValidator(0,9999999, this));
 //ctrl de saisie string
   QRegExpValidator *validator = new QRegExpValidator(QRegExp("[a-zA-Z]+"), ui->ajout_nom);
   ui->ajout_nom->setValidator(validator);
*/


                             //Equipements//////////////////////////
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


}


MainWindow::~MainWindow()
{
    delete ui;
}
//Arduino//////////////////////////////////////////////////////////
void MainWindow::update_label()
{
    QString data = A.read_from_arduino().trimmed();
    qDebug() << data;
    QSqlQuery query2;
    query2.prepare("SELECT NOM FROM EQUIPEMENTS WHERE IDEQUIPEMENT = :data");
    query2.bindValue(":data", data);
    if (query2.exec() && query2.next()) {
        qDebug() << "Requête SQL réussie";
        QString titreEvent = query2.value("NOM").toString();
        QByteArray data2 = titreEvent.toUtf8();
        A.write_to_arduino(data2);
    } else {
        qDebug() << "Requête SQL échouée";
    }
}

//Menu

void MainWindow::on_Equipements_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(3);
}
void MainWindow::on_Activites_clicked()
{
   ui->stackedWidget_in->setCurrentIndex(12);
}
void MainWindow::on_Intervenants_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(3);
}



void MainWindow::on_Patients_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(3);
}
//Equipements//////////////////////////
void MainWindow::on_Ajouter_equipement_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(0);
}
void MainWindow::on_Ajouter_equipement_2_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(0);
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

void MainWindow::on_pdf_btn_2_clicked()
{
        ui->stackedWidget_in->setCurrentIndex(4);
}



//Crud equipements


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


//metier equipement
void MainWindow::on_tri_btn_clicked()
{
    ui->table_equip->setModel(E.tri_PrixC());
}

void MainWindow::on_tri_btn_2_clicked()
{
    ui->table_equip->setModel(E.tri_alphabetique());
}


void MainWindow::on_search_btn_clicked()
{
    ui->table_equip->setModel(E.recherche_NOM(ui->entrer_recherche->text()));

/*
                    QMessageBox::information(nullptr,QObject::tr("OK"),
                                              QObject::tr("recherche done.\n"
                                                          "clic cancel to exit."),QMessageBox::Cancel); */
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

    QGridLayout *StatsLayout = ui->stackedWidget_in->findChild<QGridLayout*>("gridLayout_equip");
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


//qr code
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




//Activité///////////////////////////////////

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(0);

}
void MainWindow::on_update_clicked()
{
      ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
  ui->stackedWidget_in->setCurrentIndex(2);
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(8);
}

void MainWindow::on_gestion_activite_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(5);
}
void MainWindow::on_todoo_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(10);
}

void MainWindow::on_uploade_fichier_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir un fichier"), "", tr("Images (*.png *.xpm *.jpg)"));
      if (!fileName.isEmpty()) {
          QImage image(fileName);
          if (image.isNull()) {
              QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
          }
      }
}




void MainWindow::on_valider_ajout_clicked()
{
    int idactivite;
            //=ui->l_id->text().toInt();
     QString Nom=ui->l_nom->text();
      QString Description=ui->l_description->text();
        QString Genre=ui->l_genre->text();
             //QString Cible=ui->l_cible->text();
              QString Cible;
             if(ui->enfant->isChecked()) {
                     Cible = ui->enfant->text();
                 }
                 else if(ui->adulte->isChecked()) {
                     Cible = ui->adulte->text();
                 }

activite Act(idactivite,Nom ,Description ,Genre ,Cible);
qDebug() << "Message à afficher sur la console";
bool test=Act.ajouter();
     if (test)
     {
    ui->table_act->setModel(Act.afficher()); // setmodel hyaaa eli lhyaaa bel affichage fi label table_act

         QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("ajout successful.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);  }
       else

         {
         QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                QObject::tr("ajout failed.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
         }

}


void MainWindow::on_l_supp_clicked()
{
    activite A1;
    A1.setid(ui->le_supp->text().toInt());
    bool test=A1.supprmier(A1.getid());
QMessageBox msgBox;

    if (test)
    {
  ui->table_act->setModel(Act.afficher());//updateeeeeeeeeeeeeee label affichage
        QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("delete successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel); }
      else
        {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                               QObject::tr("delete failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
        }
}









void MainWindow::on_validermodif_clicked()
{

    int idactivite=ui->l_id_2->text().toInt();
    QString Nom=ui->l_nom_2->text();
    QString Description=ui->l_description_2->text();

    QString Genre=ui->l_genre_2->text();
       QString Cible;
        if (ui->enfant_2->isChecked()==true) {
            Cible = "Enfant";
        } else if (ui->adulte_2->isChecked()==true) {
            Cible = "Adulte";
        }
    activite Act(idactivite,Nom,Description,Genre,Cible);

    bool test=Act.modifier(idactivite);
    if (test)
    {

        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);
        ui->table_act->setModel(Act.afficher());
    }
    else
    {
     QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);
    }
}



void MainWindow::on_chercher_clicked()
{
    ui->table_act->setModel(Act.recherche_NOM(ui->le_chercher->text()));
}

void MainWindow::on_stat_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(9);
      activite A;
       QGridLayout *StatsLayout1 = ui->stackedWidget_in->findChild<QGridLayout*>("gridLayout_act");
       StatsLayout1->addWidget(Act.Stat(), 0, 0);

}



void MainWindow::on_croissant_clicked()
{
    ui->table_act->setModel(Act.tri_croissant());
}

void MainWindow::on_decroissant_clicked()
{
     ui->table_act->setModel(Act.tri_decroissant());
}



   /*  QString strStream;
        QTextStream out(&strStream);
        QPdfWriter pdf("C:/Users/Sarra/Desktop/Volunteer.pdf");

                         QPainter painter(&pdf);

                         int i = 4000;
                       // 'this' is a pointer to the widget you want to paint
                         //painter.setStyleSheet("background-color: red;");
                         painter.drawText(4300,1500,"LIST Of Activites");
                         painter.setPen(QPen(Qt::black, 6));
                         //painter.drawRect(5, 5, 8300, 1900);
                         painter.setFont(QFont("Arial",20));
                         painter.drawRect(0, 0, 0,39600);
                         painter.drawRect(0,0,26800,0);
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial",9));
                         painter.drawText(300,3300,"ID");
                         painter.drawText(1000,3300,"First Name");
                         painter.drawText(2300,3300,"Last Name");
                         painter.drawText(3300,3300,"Adresse");
                         painter.drawText(4300,3300,"DateBirth");
                         painter.drawText(5300,3300,"DateJoining");
                         painter.drawText(6300,3300,"nbPart");
                         painter.drawText(7300,3300,"kind of help");
                         painter.drawText(8300,3300,"occupation");
                         painter.drawText(9100,3300,"Fedility");


                         QSqlQuery query;
                         query.prepare("select * from ACTIVITES");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(300,i,query.value(0).toString());
                             painter.drawText(1000,i,query.value(1).toString());
                             painter.drawText(2300,i,query.value(2).toString());
                             painter.drawText(3300,i,query.value(3).toString());
                             painter.drawText(4300,i,query.value(4).toString());
                             painter.drawText(5300,i,query.value(5).toString());
                             painter.drawText(6300,i,query.value(6).toString());
                             painter.drawText(7300,i,query.value(7).toString());
                             painter.drawText(8300,i,query.value(8).toString());
                             painter.drawText(9300,i,query.value(9).toString());

                             i = i +500;
//                             out <<"<img src=\""<<"C:\\Users\\Ons Ben Maouia\\Downloads\\latifaQT\\media\\logo.png"<<"\"/>\n";
                         }

}
*/
void MainWindow::on_pdf_clicked()
{


        // Exécution de la requête SQL pour récupérer les données
       QSqlQuery query;
        query.exec("SELECT * FROM ACTIVITES");

        // Création d'un fichier PDF temporaire
        QString pdfFileName = "temp_pdf_file.pdf";
        QPdfWriter writer(pdfFileName);
        QPainter painter(&writer);

        painter.drawText(3000,1000,"LIST Of Activites");
        painter.setPen(QPen(Qt::black, 20));
        //painter.drawRect(5, 5, 8300, 1900);
        painter.setFont(QFont("Arial",20));
        painter.drawRect(0, 0, 0,39600);
        painter.drawRect(0,0,26800,0);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial",9));
        painter.drawText(1500,2000,"ID");
        painter.drawText(2500,2000,"Nom activité");
        painter.drawText(3500,2000,"Description");
        painter.drawText(4500,2000,"Genre");
        painter.drawText(5500,2000,"Cible");

        int yPos = 2500;
        while (query.next()) {
            // Récupération des données de la requête
            QString champ1 = query.value(0).toString();
            QString champ2 = query.value(1).toString();
            QString champ3 = query.value(2).toString();
  QString champ4 = query.value(3).toString();
    QString champ5 = query.value(4).toString();

    QFont font("Arial", 9);
      painter.setFont(font);
      QPen pen(Qt::black);
      painter.setPen(pen);


      QColor textColor(255, 0, 0); // Rouge
      pen.setColor(textColor);
      painter.setPen(pen);

            // Dessin des données sur le document PDF
            painter.drawText(QRect(1500, yPos, 2000, 500), champ1);
            painter.drawText(QRect(2500, yPos, 2000, 500), champ2);
            painter.drawText(QRect(3500, yPos, 2000, 500), champ3);
   painter.drawText(QRect(4500, yPos, 2000, 500), champ4);
      painter.drawText(QRect(5500, yPos, 10000, 500), champ5);
            // Incrémentation de la position Y pour passer à la ligne suivante
            yPos += 750;

            // Passage à une nouvelle page du document PDF si nécessaire
            if (yPos > writer.height()) {
                writer.newPage();
                yPos = 1000;
            }
        }
        // Ouvre le fichier PDF avec le programme de visualisation de PDF par défaut de l'utilisateur
        QDesktopServices::openUrl(QUrl::fromLocalFile(pdfFileName));
}

void MainWindow::on_agenda_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(11);

    QComboBox *ComboCLADER = ui->stackedWidget_in->findChild<QComboBox*>("comboBoxcalander");
            ComboCLADER->clear();
             ComboCLADER->addItem("Select");
             ui->comboBoxcalander->setItemData(0, QVariant(Qt::UserRole), Qt::UserRole);

             QSqlQuery query, query1;
                      query.prepare("SELECT IDACTIVITE FROM ACTIVITES");

               // Executing the query and fetching the IDEVENT from the result set
                  if (query.exec()) {
                      while (query.next())
                        {
                           int i=query.value(0).toInt();
                          // Convert the ID_EM to a string format
                          QString intString = QString::number(i);
                            // Add the string representation of the IDEVENT to the
                            ComboCLADER->addItem(intString);
                         }
                  }
                  connect(ComboCLADER, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index){


                         QString selectedItemText = ComboCLADER->currentText();
                         int ID = selectedItemText.toInt();

                         // Prepare the SQL query to fetch the data for the selected ID
                         QSqlQuery query1;

                         query1.prepare("SELECT NOM FROM ACTIVITES WHERE IDACTIVITE = :id");
                         query1.bindValue(":id", ID);
                         qDebug() << "preparation completed ";

                         if (query1.exec() && query1.next()) {

                             // Retrieve the values for each column
                             QString Titre_event = query1.value("NOM").toString();
                             QLineEdit *lineEditTitre_activiter = ui->stackedWidget_in->findChild<QLineEdit*>("nom");
                                        lineEditTitre_activiter->setText(Titre_event);
                                        lineEditTitre_activiter->update();
}                  });
}



void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QString val = date.toString("yyyy-MM-dd");

    QSqlQuery qry;
    qry.exec("SELECT * FROM HISTORIQUEACTIVITES WHERE DATEACTIVITE='" + val + "'");

    if (qry.next()) {
        ui->id_date->setText(qry.value(0).toString());
        ui->nom_activite->setText(qry.value(1).toString());

        QString val2 = qry.value(1).toString();

        QSqlQuery query1;
        query1.exec("SELECT * FROM ACTIVITES WHERE IDACTIVITE ='" + val2 + "'");

        if (query1.next()) {
            ui->nom_activite_2->setText(query1.value(1).toString());
        }
    } else {
        // Aucune activité pour cette date, donc vider les labels
        ui->id_date->setText("");
        ui->nom_activite->setText("");
        ui->nom_activite_2->setText("Aucune activité n'est ajoutée");
    }
}
/*
{
    QString val=date.toString("yyyy-MM-dd");

           QSqlQuery qry;
 qry.exec(("SELECT * FROM HISTORIQUEACTIVITES WHERE DATEACTIVITE='"+val+"'"));


    while (qry.next()) {
        ui->id_date->setText(qry.value(0).toString());
         ui->nom_activite->setText(qry.value(1).toString());
        //ui->affichage_date->setDate(date); //y7ot date baad manenzl al calendrier

         QString val2=qry.value(1).toString();

        QSqlQuery query1;

        query1.exec("SELECT * FROM ACTIVITES WHERE IDACTIVITE ='"+val2+"'");

            while (query1.next()) {
               ui->nom_activite_2->setText(query1.value(1).toString());
            }

}


}

*/


void MainWindow::on_ajoutDate_clicked()
{
    int idactivite=ui->comboBoxcalander->currentText().toInt();
    QDate date=ui->dateEdit->date();

      QString date_v=date.toString("yyyy-MM-dd");

             calender_A Act (idactivite,date_v);

    bool test=Act.calender_ajout();
         if (test)
         {

qDebug() << "Message à afficher sur la console";
             QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("ajout successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);  }
           else

             {
             QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("ajout failed.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
             }
}

/*
void MainWindow::on_supprimer_calendrier_clicked()
{
  calender_A H;

          H.setid_C(ui->supp_calendrier->text().toInt());
    bool test=H.supprmierCalender(H.getid_C());
QMessageBox msgBox;

    if (test)
    {

        QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("delete successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

     }
      else

        {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                               QObject::tr("delete failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);


        }

}
*/
void MainWindow::on_le_chercher_textChanged(const QString &arg1)
{
    ui->table_act->setModel(Act.recherche_NOM(arg1));

}



void MainWindow::done2()

{

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    QSqlQuery query;

    query.prepare("delete from TACHE where content=:c");

    query.bindValue(":c",button->text());

    query.exec();

    delete button;



}

void MainWindow::done()

{

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    ui->v3->addWidget(button);

    QObject::connect( button, &QPushButton::clicked,this, &MainWindow::done2);

    QSqlQuery query;

    query.prepare("update TACHE set type=2 where content=:c");

    query.bindValue(":c",button->text());

    query.exec();

}

void MainWindow::inprogress()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    ui->v2->addWidget(button);

    QObject::connect( button, &QPushButton::clicked,this, &MainWindow::done);

    QSqlQuery query;

    query.prepare("update TACHE set type=1 where content=:c");

    query.bindValue(":c",button->text());

    query.exec();

}



void MainWindow::ajouttodo()

{

    QPushButton *b = new QPushButton(ui->L1->text());

    b->setStyleSheet("QPushButton {background-color:rgb(207, 77, 206);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");

    ui->v1->addWidget(b);

    QObject::connect( b, &QPushButton::clicked,this, &MainWindow::inprogress);

    QSqlQuery query;

    query.prepare("insert into TACHE (content,type) values (:c,0)");

    query.bindValue(":c",ui->L1->text());

    query.exec();

}



void MainWindow::load()

{

    QSqlQuery query;

    query.prepare("select * from TACHE");

    if(query.exec())

    {

        while(query.next())

        {

            if(query.value(1).toInt()==0)

            {

                QPushButton *b = new QPushButton(query.value(0).toString());

                b->setStyleSheet("QPushButton {background-color:rgb(207, 77, 206);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");

                ui->v1->addWidget(b);

                QObject::connect( b, &QPushButton::clicked,this, &MainWindow::inprogress);

            }

            if(query.value(1).toInt()==1)

            {

                QPushButton *b = new QPushButton(query.value(0).toString());

                b->setStyleSheet("QPushButton {background-color:rgb(207, 77, 206);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");
                ui->v2->addWidget(b);

                QObject::connect( b, &QPushButton::clicked,this, &MainWindow::done);

            }

            if(query.value(1).toInt()==2)

            {

                QPushButton *b = new QPushButton(query.value(0).toString());

                b->setStyleSheet("QPushButton {background-color:rgb(207, 77, 206);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");

                ui->v3->addWidget(b);

                QObject::connect( b, &QPushButton::clicked,this, &MainWindow::done2);

            }



        }

    }

}

void MainWindow::on_b1_clicked()
{
    ajouttodo();
}




void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(7);

}


//evenement////////////////
void MainWindow::fingerarduino()
{
    qDebug() << "update label";
    QByteArray data = A.read_from_arduino();
    QString id = QString::fromUtf8(data).trimmed().simplified();
    id = id.remove(QRegExp("[^\\d]")); // remove all non-numeric characters
    int id_num = id.toInt(); // convert the resulting string to an integer
    qDebug() << "ID de l'empreinte digitale:" << id_num;

    QSqlQuery query2;
          query2.prepare("SELECT IDEVENT FROM EVENTS WHERE IDEVENT =:id_num");
          query2.bindValue(":id_num", id_num);
          query2.exec();

          if (query2.next()) {
              QString titreEvent = query2.value("IDEVENT").toString();
              QByteArray data2 = titreEvent.toUtf8();
                        A.write_to_arduino(data2);
                       qDebug() << "Ihoha" << data2;
          }


}
void MainWindow::testy()
{
  qDebug() << "test";
  fingerarduino();
}

void MainWindow::on_Ajouter_event_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(15);
}

//uploade l'affiche
void MainWindow::on_uploade_fichier_event_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir un fichier"), "", tr("Images (*.png *.xpm *.jpg)"));
      if (!fileName.isEmpty()) {
          QImage image(fileName);
          if (image.isNull()) {
              QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
          } else {
              ui->imageLabel_event->setPixmap(QPixmap::fromImage(image_event));
              ui->imageLabel_event->setScaledContents(true);
              image_event=image;


          }
      }

}
//ifaragh l page apdate ml data
void MainWindow::on_Events_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(13);


     QStringList lineEditNames = {"Titre_event_update", "lineEdit_Desc_update", "lineEdit_lieuEvent_update"};

     for (const QString& name : lineEditNames) {
         QLineEdit* lineEdit = ui->stackedWidget_in->findChild<QLineEdit*>(name);
         if (lineEdit){
             lineEdit->clear();
         }
     }

     QCheckBox* radioButton_Pub = ui->stackedWidget_in->findChild<QCheckBox*>("radioButton_Pub_update");
     QCheckBox* radioButton_Sensib = ui->stackedWidget_in->findChild<QCheckBox*>("radioButton_Sensib_update");
     if (radioButton_Pub && radioButton_Sensib) {
         radioButton_Pub->setChecked(false);
         radioButton_Sensib->setChecked(false);

     }


     QCheckBox* radioButton_Virtuel = ui->stackedWidget_in->findChild<QCheckBox*>("radioButton_Virtuel_update");
     QCheckBox* radioButton_Hybride = ui->stackedWidget_in->findChild<QCheckBox*>("radioButton_Hybride_update");
     QCheckBox* radioButton_Present = ui->stackedWidget_in->findChild<QCheckBox*>("radioButton_Present_update");
     if (radioButton_Virtuel && radioButton_Hybride && radioButton_Present) {
         radioButton_Virtuel->setChecked(false);
         radioButton_Hybride->setChecked(false);
         radioButton_Present->setChecked(false);

     }

}
//add events
void MainWindow::on_validation_ajout_event_clicked()
{  int controle=0;

    if(ui->lineEditTitre_event->text() == "")
    {
        ui->Obligatoirechamp1->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->lineEdit_Desc->text() == "")
    {
        ui->labelchamps->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->lineEdit_lieuEvent->text() == "")
    {
        ui->labelchamps_2->setText("Champ Obligatoire*");
        controle=1;
    }




    QString Titre_event=ui->lineEditTitre_event->text();

    QString Desc_event=ui->lineEdit_Desc->text();

    QString lieuEvent=ui->lineEdit_lieuEvent->text();

    QString  genre_event;

        if(ui->radioButton_Pub->isChecked()) {
            genre_event = ui->radioButton_Pub->text();
        }
        else if(ui->radioButton_Sensib->isChecked()) {
            genre_event = ui->radioButton_Sensib->text();
        }



QDateTime date_event=ui->dateTimeEdit_event->dateTime();


    QString  etat_event;
    if(ui->radioButton_Virtuel->isChecked()) {
        etat_event = ui->radioButton_Virtuel->text();
    }
    else if(ui->radioButton_Hybride->isChecked()) {
        etat_event = ui->radioButton_Hybride->text();
    }
    else if(ui->radioButton_present->isChecked()) {
        etat_event = ui->radioButton_present->text();
    }

    //QString etat_event=ui->lineEdit_EtatEvent->text();




      //convertir image en binaire BLOB
            QByteArray imageData;
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            image_event.save(&buffer, "PNG");
            buffer.close();
if(controle==0)
{
 Event E(Titre_event,  Desc_event,  lieuEvent,  genre_event,  etat_event,  date_event,imageData);

 bool test=E.ajouter_event();

 if(test)
   {
        ui->tableView_events->setModel(Evt.afficher_event());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                 QObject::tr("ajouter effectue\n" "Click cancel to exite."),QMessageBox::Cancel);

    //refreche le comptage du nombre de ligne
        QSqlQuery query;
        int row_count = 0;
        query.exec("SELECT COUNT(*) FROM EVENTS");
        if(query.first())
        row_count = query.value(0).toInt();
        QLCDNumber *lcdNumber = this->findChild<QLCDNumber*>("lcdNumber");
        ui->lcdNumber->display(row_count);

        QComboBox *Combodelete = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_suppr");
        Combodelete->clear();
        QSqlQuery query_delate;
        query_delate.prepare("SELECT IDEVENT FROM EVENTS");
    // Executing the query and fetching the IDEVENT from the result set
        if (query_delate.exec()) {
            while (query_delate.next()) {
                int id=query_delate.value(0).toInt();
                // Convert the IDEVENT to a string format
                QString intString = QString::number(id);
                // Add the string representation of the ID_EM to the combobox
                Combodelete->addItem(intString);
            }
        }

        QComboBox *ComboSELECT = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_selest");
        ComboSELECT->clear();
        QSqlQuery query_SELECT;
        query_SELECT.prepare("SELECT NOM FROM EVENTS");
        // Executing the query and fetching the NAME column from the result set
        if (query_SELECT.exec()) {
            while (query_SELECT.next()) {
                QString name = query_SELECT.value(0).toString();
                // Add the name to the combobox
                ComboSELECT->addItem(name);
            }
        }

    }
 else
     {
        QMessageBox::information(nullptr, QObject::tr("not ok"),
                 QObject::tr("ajouter non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
     }
}
}


//delate events
void MainWindow::on_botton_supprimer_clicked()
{
    QComboBox *Combodelete = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_suppr");
    QString selectedItemText = Combodelete->currentText();
    int ID = selectedItemText.toInt();

  bool test=Evt.supprimer_event(ID);
  if(test)
  {
      /*QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("suppression effuctue \n"
                                        "Click cencel to exit."),QMessageBox::Cancel);*/


      //apdate lel combox apres delate
      Combodelete->clear();
      QComboBox *Combodelete = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_suppr");
      Combodelete->clear();
      QSqlQuery query_delate;
      query_delate.prepare("SELECT IDEVENT FROM EVENTS");
  // Executing the query and fetching the IDEVENT from the result set
      if (query_delate.exec()) {
          while (query_delate.next()) {
              int id=query_delate.value(0).toInt();
              // Convert the IDEVENT to a string format
              QString intString = QString::number(id);
              // Add the string representation of the ID_EM to the combobox
              Combodelete->addItem(intString);
          }
      }



//apdate lal comtage events baad l delate
        QSqlQuery query;
         int row_count = 0;
         query.exec("SELECT COUNT(*) FROM EVENTS");
         if(query.first())
         row_count = query.value(0).toInt();
         QLCDNumber *lcdNumber = this->findChild<QLCDNumber*>("lcdNumber");
         ui->lcdNumber->display(row_count);

         ui->tableView_events->setModel(Evt.afficher_event());
          //update cmbox de details event
         QComboBox *ComboSELECT = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_selest");
         ComboSELECT->clear();
         QSqlQuery query_SELECT;
         query_SELECT.prepare("SELECT NOM FROM EVENTS");

         // Executing the query and fetching the NAME column from the result set
         if (query_SELECT.exec()) {
             while (query_SELECT.next()) {
                 QString name = query_SELECT.value(0).toString();
                 // Add the name to the combobox
                 ComboSELECT->addItem(name);
             }
         }

  }
  else
  {
      QMessageBox::critical(nullptr,QObject::tr("not ok"),
                QObject::tr("suppression non effuctue \n"
                              "Click cencel to exit."),QMessageBox::Cancel);
  }
}



//affiche les data to modifier dans les lineedit
void MainWindow::on_botton_update_events_clicked()
{
        ui->stackedWidget_in->setCurrentIndex(16);

        QComboBox *Comboupdate = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_update");
        Comboupdate->clear();
         Comboupdate->addItem("Select");
         ui->comboBox_update->setItemData(0, QVariant(Qt::UserRole), Qt::UserRole);
         QSqlQuery query, query1;
         query.prepare("SELECT IDEVENT FROM EVENTS");

  // Executing the query and fetching the IDEVENT from the result set
     if (query.exec()) {
         while (query.next())
           {
              int i=query.value(0).toInt();
             // Convert the ID_EM to a string format
             QString intString = QString::number(i);
               // Add the string representation of the IDEVENT to the
               Comboupdate->addItem(intString);
            }
     }


   connect(Comboupdate, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index){


       QString selectedItemText = Comboupdate->currentText();
       int ID = selectedItemText.toInt();

       // Prepare the SQL query to fetch the data for the selected ID
       QSqlQuery query1;

       query1.prepare("SELECT NOM,DATEEVENT, DESCRIPTION, LIEU, GENRE, ETAT,AFFICHE FROM EVENTS WHERE IDEVENT = :id");
       query1.bindValue(":id", ID);
       qDebug() << "preparation completed ";

       if (query1.exec() && query1.next()) {

           // Retrieve the values for each column
           QString Titre_event = query1.value("NOM").toString();
           QString Desc_event = query1.value("DESCRIPTION").toString();
           QString lieuEvent = query1.value("LIEU").toString();
           QString genre_event = query1.value("GENRE").toString();
           QString etat_event = query1.value("ETAT").toString();
          // QString intervenant_event = query1.value("INTERVENANT").toString();

           qDebug() << "retrieving completed";

           QLineEdit *lineEditTitre_event = ui->stackedWidget_in->findChild<QLineEdit*>("Titre_event_update");
           lineEditTitre_event->setText(Titre_event);
          // lineEditTitre_event->setReadOnly(true);
           lineEditTitre_event->update();

           QLineEdit *lineEdit_Desc = ui->stackedWidget_in->findChild<QLineEdit*>("lineEdit_Desc_update");
           lineEdit_Desc->setText(Desc_event);
           lineEdit_Desc->update();



           ui->dateTimeEdit_event_update_2->setDateTime(query1.value("DATEEVENT").toDateTime());

           QLineEdit *lineEdit_lieuEvent = ui->stackedWidget_in->findChild<QLineEdit*>("lineEdit_lieuEvent_update");
           lineEdit_lieuEvent->setText(lieuEvent);
           lineEdit_lieuEvent->update();


           if(genre_event=="Publicite"){
               ui->radioButton_Pub_update->setChecked(true);
           }else if(genre_event=="Sensibilisation"){
               ui->radioButton_Sensib_update->setChecked(true);
           }

           if(etat_event=="Virtuel"){
               ui->radioButton_Virtuel_update->setChecked(true);
           }else if(etat_event=="Hybride"){
               ui->radioButton_Hybride_update->setChecked(true);
           }
           else if(etat_event=="Presentiel"){
                ui->radioButton_Present_update->setChecked(true);
           }





           QPixmap update_afffiche;
           QByteArray image_data=query1.value("AFFICHE").toByteArray();
           update_afffiche.loadFromData(image_data);
           ui->imageLabel_3->setPixmap(update_afffiche);
       }
   });

}


void MainWindow::on_validation_update_events_clicked()
{

     QString Titre_event=ui->Titre_event_update->text();

     QString Desc_event=ui->lineEdit_Desc_update->text();

     QString lieuEvent=ui->lineEdit_lieuEvent_update->text();

     QString genre_event = "";
       if (ui->radioButton_Pub_update->isChecked()==true)
        {
         genre_event = "Publicite";
        }
       else if (ui->radioButton_Sensib_update->isChecked()==true)
        {
         genre_event = "Sensibilisation";
        }

       QString etat_event = "";
         if (ui->radioButton_Virtuel_update->isChecked()==true)
          {
           etat_event = "Virtuel";
          }
         else if (ui->radioButton_Hybride_update->isChecked()==true)
          {
           etat_event = "Hybride";
          }
         else if (ui->radioButton_Present_update->isChecked()==true)
          {
           etat_event = "Presentiel";
          }

      //QString etat_event=ui->lineEdit_EtatEvent_update->text();

      QDateTime date_event= ui->dateTimeEdit_event_update_2->dateTime();

      QComboBox *Comboapdate = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_update");
      QString selectedItemText = Comboapdate->currentText();
      int ID = selectedItemText.toInt();

    if (image_event.isNull()==false)
     {
          QByteArray imageData;
          QBuffer buffer(&imageData);
          buffer.open(QIODevice::WriteOnly);
          image_event.save(&buffer, "PNG");
          buffer.close();
  Event E(Titre_event,  Desc_event,  lieuEvent,  genre_event,  etat_event,  date_event,imageData);
  bool test1 = E.modifier_eventimage(ID);

      if(test1){
         ui->tableView_events->setModel(Evt.afficher_event());
          QMessageBox::information(nullptr, QObject::tr("Updated!"),
                                   QObject::tr("The element is updated \n"
                                              "Click ok to exit."), QMessageBox::Ok);
      }
      else{
          QMessageBox::critical(nullptr, QObject::tr("Error"),
                                   QObject::tr("The element is refused \n"
                                              "Click ok to exit."), QMessageBox::Ok);
      }
    }
      else {

          QByteArray imageData;
          QBuffer buffer(&imageData);
          buffer.open(QIODevice::WriteOnly);
          image_event.save(&buffer, "PNG");
          buffer.close();
  Event E(Titre_event,  Desc_event,  lieuEvent,  genre_event,  etat_event,  date_event,imageData);
  bool test1 = E.modifier_event(ID);

        if(test1){
           ui->tableView_events->setModel(Evt.afficher_event());
            QMessageBox::information(nullptr, QObject::tr("Updated!"),
                                     QObject::tr("The element is updated \n"
                                                "Click ok to exit."), QMessageBox::Ok);
        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                                     QObject::tr("The element is refused \n"
          "Click ok to exit."), QMessageBox::Ok);
      }

    }
}

void MainWindow::on_uploade_fichier_event_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir un fichier"), "", tr("Images (*.png *.xpm *.jpg)"));
      if (!fileName.isEmpty())
      {
          QImage image(fileName);
          if (image.isNull())
          {
              QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
          } else
          {

              image_event=image;
              QPixmap update_afffiche=QPixmap::fromImage(image);
              ui->imageLabel_3->setPixmap(update_afffiche);
          }
      }
}

/*
void MainWindow::on_pushButton_3_clicked_event()
{
     ui->stackedWidget_in->setCurrentIndex(2);
}
*/

void MainWindow::on_lineEdit_chercheEvent_textChanged(const QString &arg1)
{
    ui->tableView_events->setModel(Evt.recherche_titreEvent(arg1));
}



void MainWindow::on_events_statistics_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(17);
    Event e;
    QGridLayout *StatsLayout1 = ui->gridLayout_event1;
    StatsLayout1->addWidget(e.stat_gender(), 0, 0);


    QGridLayout *StatsLayout2 = ui->stackedWidget_in->findChild<QGridLayout*>("gridLayout_event2");
    StatsLayout2->addWidget(e.stat_type(), 0, 0);
}

void MainWindow::on_details_events_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(19);

     //AFFICHAGE DE COMBOX DE LES NOM POUR LA PAGE DE DETAILS EVENTS
         QComboBox *ComboSELECT = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_selest");
         ComboSELECT->clear();
         ComboSELECT->addItem("Select a name of event");
         QSqlQuery query_SELECT;
         query_SELECT.prepare("SELECT NOM FROM EVENTS");

         // Executing the query and fetching the NAME column from the result set
         if (query_SELECT.exec()) {
             while (query_SELECT.next()) {
                 QString name = query_SELECT.value(0).toString();
                 // Add the name to the combobox
                 ComboSELECT->addItem(name);
             }
         }

         connect(ComboSELECT, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index){


             QString selectedItemText = ComboSELECT->currentText();

             QString titre = selectedItemText;

             QSqlQuery query2;

             query2.prepare("SELECT NOM, DESCRIPTION,LIEU FROM EVENTS WHERE NOM =:titre");
             query2.bindValue(":titre", titre);
               qDebug() << "preparation completed ";
             if (query2.exec() && query2.next()) {
                         qDebug() << "preparation recete ";
                 // Retrieve the values for each column
                 QString Titre_eventD = query2.value("NOM").toString();
                 QString Desc_eventD = query2.value("DESCRIPTION").toString();
                 QString lieu_eventD = query2.value("LIEU").toString();



               ui->axWidget->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps?q="+lieu_eventD);


                 QLineEdit *lineEditTitre_event = ui->stackedWidget_in->findChild<QLineEdit*>("lineEditTitre_event_2");
                 lineEditTitre_event->setText(Titre_eventD);
                 lineEditTitre_event->setReadOnly(true);
                 lineEditTitre_event->update();

                 QLineEdit *lineEdit_Desc = ui->stackedWidget_in->findChild<QLineEdit*>("lineEdit_Desc_2");
                 lineEdit_Desc->setText(Desc_eventD);
                 lineEdit_Desc->setReadOnly(true);
                 lineEdit_Desc->update();





             }

         });



}

void MainWindow::on_EmissionCO2_clicked()
{
      ui->stackedWidget_in->setCurrentIndex(18);


      QComboBox *comboBox_emmisionCO2 = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_emmisionCO2");
      comboBox_emmisionCO2->clear();
       comboBox_emmisionCO2->addItem("Select");
       ui->comboBox_emmisionCO2->setItemData(0, QVariant(Qt::UserRole), Qt::UserRole);
       QSqlQuery query, query1;
       query.prepare("SELECT IDEVENT FROM EVENTS");

// Executing the query and fetching the IDEVENT from the result set
   if (query.exec()) {
       while (query.next())
         {
            int i=query.value(0).toInt();
           // Convert the ID_EM to a string format
           QString intString = QString::number(i);
             // Add the string representation of the IDEVENT to the
             comboBox_emmisionCO2->addItem(intString);
          }
   }

}




void MainWindow::on_pdf_Event_test_clicked()
{

       QSqlDatabase db;

       QTableView tableView;
       QSqlQueryModel * Modal=new  QSqlQueryModel();
       QSqlQuery qry;
       QString titre = ui->lineEdit_chercheEvent->text();
       qry.prepare("select * from EVENTS WHERE LOWER(NOM) LIKE LOWER('%"+titre+"%')");
       qry.exec();
       Modal->setQuery(qry);
          tableView.setModel(Modal);
          db.close();
          QString strStream;
          QTextStream out(&strStream);
          const int rowCount = tableView.model()->rowCount();
          const int columnCount =  tableView.model()->columnCount();
          const QString strTitle ="ListedesEvents";
          out <<  "<html>\n"
                      "<img src='C:/Users/Mozrani amine/Desktop/Projet/projet/logoqt.png' height='300' width='250'/>"
                      "<head>\n"
                      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                  <<  QString("<title>%1</title>\n").arg(strTitle)
                  <<  "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"
                  << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES EVENEMENT")
                  <<  "<br>"

                  <<  "<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
              out << "<thead><tr bgcolor=#f0f0f0>";
              for (int column = 0; column < columnCount; column++)
                  if (!tableView.isColumnHidden(column))
                out << QString("<th>%1</th>").arg(tableView.model()->headerData(column, Qt::Horizontal).toString());
               out << "</tr></thead>\n";
               for (int row = 0; row < rowCount; row++)
               {
                 out << "<tr>";
                 for (int column = 0; column < columnCount; column++)
                 {
                                 if (!tableView.isColumnHidden(column))

                                 {
                                    QString data = tableView.model()->data(tableView.model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                                 }
                 }
                            out << "</tr>\n";

               }
                       out <<  "</table>\n"
                               "<br><br>"
                           <<"<br>"
                           <<"<table border=1 cellspacing=0 cellpadding=2>\n";
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";

                       QTextDocument *ListeDesevent = new QTextDocument();
                            ListeDesevent->setHtml(strStream);

                            QPrinter printer;
                                QPrintDialog *dialog = new QPrintDialog(&printer, NULL);

                                if (dialog->exec() == QDialog::Accepted)
                                     {
                                         ListeDesevent->print(&printer);
                                     }
                                printer.setOutputFormat(QPrinter::PdfFormat);
                                     printer.setPaperSize(QPrinter::A4);
                                     printer.setOutputFileName("/tmp/Event.pdf");
                                     printer.setPageMargins(QMarginsF(15, 15, 15, 15));
                                     delete ListeDesevent;




}



void MainWindow::on_radioButton_2_clicked()
{
    QString croissance=ui->radioButton_2->text();
    ui->tableView_events->setModel(Evt.trierD());
}

void MainWindow::on_radioButtontrier_eventC_2_clicked()
{
    QString croissance=ui->radioButtontrier_eventC_2->text();
    ui->tableView_events->setModel(Evt.trierC());
}
//arduino  project
void MainWindow::on_Settings_2_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(7);


}





void MainWindow::on_botton_selsct_event_2_clicked()
{
    QComboBox *comboBox_emmisionCO2 = ui->stackedWidget_in->findChild<QComboBox*>("comboBox_emmisionCO2");
    comboBox_emmisionCO2->clear();
    QSqlQuery query_emmisionCO2;
    query_emmisionCO2.prepare("SELECT IDEVENT FROM EVENTS");
// Executing the query and fetching the IDEVENT from the result set
    if (query_emmisionCO2.exec()) {
        while (query_emmisionCO2.next()) {
            int id=query_emmisionCO2.value(0).toInt();
            // Convert the IDEVENT to a string format
            QString intString = QString::number(id);
            // Add the string representation of the ID_EM to the combobox
            comboBox_emmisionCO2->addItem(intString);
        }
    }

             ui->comboBox_emmisionCO2->setItemData(0, QVariant(Qt::UserRole), Qt::UserRole);

             connect(comboBox_emmisionCO2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index){


                 QString selectedItemText = comboBox_emmisionCO2->currentText();
                       int id = selectedItemText.toInt();
                       QSqlQuery qry;
                       qry.prepare ("SELECT ETAT FROM EVENTS WHERE IDEVENT = :id");
                       qry.bindValue(":id", id);
                        qDebug() << "preparation completed ";
                       qry.exec ();

    int Total = 0;
    float CF;
    int nb = ui->Titre_event_update_2->text().toInt();
    if (ui->checkBox->isChecked() == true)
    {
        Total++;
    }
    if (ui->checkBox_2->isChecked() == true)
    {
        Total++;
    }
    if (ui->checkBox_3->isChecked() == true)
    {
        Total++;
    }
    if (ui->checkBox_4->isChecked() == true)
    {
        Total++;
    }
    float Energie = Total*53.3;


    if (qry.exec() && qry.next())
    {
        QString Type = qry.value("ETAT").toString();
    if (Type == "Virtuel")
    {
         CF = 34.92;
    }
    else if (Type == "Presentiel")
    {
         CF = 1815;
    }
     if (Type == "Hybride")
    {
         CF = 239;
    }
    float CO2 = nb*(Energie/1000)*CF;
    float CO2Hybride = nb*(Energie/1000)*239;
    float CO2Physique = nb*(Energie/1000)*1815;
    float CO2Virtuel = nb*(Energie/1000)*34.92;
    QString energyStringH = QString::number(CO2Hybride, 'f', 2);
    QString energyStringP = QString::number(CO2Physique, 'f', 2);
    QString energyStringV = QString::number(CO2Virtuel, 'f', 2);
    QString energyString = QString::number(CO2, 'f', 2);
    ui->label_total->setText(energyString);
    ui->label_virtual->setText(energyStringV);
    ui->label_phusical->setText(energyStringP);
    ui->label_hybrid->setText(energyStringH);
    float PP,PV,PH;
    PP = 100*CO2Physique/CO2;
    PV = 100*CO2Virtuel/CO2;
    PH = 100*CO2Hybride/CO2;
    QString H = QString::number(PH, 'f', 2);
    QString P = QString::number(PP, 'f', 2);
    QString V = QString::number(PV, 'f', 2);
    ui->label_virtual2->setText(V);
    ui->label_physical2->setText(P);
    ui->label_hybrid2->setText(H);
    }
});
}










