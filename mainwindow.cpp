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

void MainWindow::on_Events_clicked()
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

activite Act(idactivite ,Nom ,Description ,Genre ,Cible);
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
    A1.setid(ui->l_supp->text().toInt());
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
