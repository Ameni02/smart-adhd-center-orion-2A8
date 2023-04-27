#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateEdit>
#include <QLabel>
#include <QMovie>
#include <QtGui>
#include "event.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QComboBox>
#include <QCheckBox>
#include<QDateTime>
#include <QPrinter>
#include <QPainter>
#include <QStandardPaths>
#include <QPrintDialog>
#include <QPixmap>
#include <QAxBase>
#include  <arduino.h>



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
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(fingerarduino())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).



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


    QSettings settings(QSettings::IniFormat, QSettings::UserScope,QCoreApplication::organizationName(), QCoreApplication::applicationName());
    ui->axWidget->dynamicCall("Navigate(const QString&)", "file:///C:/Users/Mozrani%20amine/Desktop/Projet/projet/index.html");





}

MainWindow::~MainWindow()
{
    delete ui;
}


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
    ui->stackedWidget_in->setCurrentIndex(0);
}


//uploade l'affiche
void MainWindow::on_uploade_fichier_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir un fichier"), "", tr("Images (*.png *.xpm *.jpg)"));
      if (!fileName.isEmpty()) {
          QImage image(fileName);
          if (image.isNull()) {
              QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
          } else {
              ui->imageLabel->setPixmap(QPixmap::fromImage(image_event));
              ui->imageLabel->setScaledContents(true);
              image_event=image;


          }
      }

}
//ifaragh l page apdate ml data
void MainWindow::on_Events_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(3);


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
void MainWindow::on_validation_ajout_clicked()
{  int controle=0;

    if(ui->lineEditTitre_event->text() == "")
    {
        ui->label_2->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->lineEdit_Desc->text() == "")
    {
        ui->label_11->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->lineEdit_lieuEvent->text() == "")
    {
        ui->label_12->setText("Champ Obligatoire*");
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
        ui->stackedWidget_in->setCurrentIndex(1);

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

void MainWindow::on_pushButton_back_clicked()
{


    ui->stackedWidget_2->setCurrentIndex(3);
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

void MainWindow::on_uploade_fichier_3_clicked()
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

void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(2);
}

void MainWindow::on_lineEdit_chercheEvent_textChanged(const QString &arg1)
{
    ui->tableView_events->setModel(Evt.recherche_titreEvent(arg1));
}



void MainWindow::on_events_statistics_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(4);
    Event e;
    QGridLayout *StatsLayout1 = ui->gridLayout;
    StatsLayout1->addWidget(e.stat_gender(), 0, 0);


    QGridLayout *StatsLayout2 = ui->stackedWidget_in->findChild<QGridLayout*>("gridLayout_2");
    StatsLayout2->addWidget(e.stat_type(), 0, 0);
}

void MainWindow::on_details_events_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(5);

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
      ui->stackedWidget_in->setCurrentIndex(6);


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
    ui->label_26->setText(energyString);
    ui->label_25->setText(energyStringV);
    ui->label_39->setText(energyStringP);
    ui->label_43->setText(energyStringH);
    float PP,PV,PH;
    PP = 100*CO2Physique/CO2;
    PV = 100*CO2Virtuel/CO2;
    PH = 100*CO2Hybride/CO2;
    QString H = QString::number(PH, 'f', 2);
    QString P = QString::number(PP, 'f', 2);
    QString V = QString::number(PV, 'f', 2);
    ui->label_78->setText(V);
    ui->label_76->setText(P);
    ui->label_77->setText(H);
    }
});
}

