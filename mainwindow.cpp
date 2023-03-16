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
#define file_rx "[A-z0-9]+(\\.(jpg|png|gif|jpeg|jfif))"

bool MainWindow::controle_saisir(int n)

{
     QLineEdit *lineEdit_nom = ui->stackedWidget_in->findChild<QLineEdit*>("lineEditTitre_event");
     QLineEdit *lineEdit_Desc = ui->stackedWidget_in->findChild<QLineEdit*>("lineEdit_Desc");
     QLineEdit *lineEdit_lieuEvent = ui->stackedWidget_in->findChild<QLineEdit*>("lineEdit_lieuEvent");
     QLineEdit *lineEdit_EtatEvent = ui->stackedWidget_in->findChild<QLineEdit*>("lineEdit_EtatEvent");
     //QCheckBox *checkBox_P = ui->stackedWidget_in->findChild<QCheckBox*>("radioButton_Pub");
     //QCheckBox *checkBox_S = ui->stackedWidget_in->findChild<QCheckBox*>("radioButton_Sensib");

     QLabel *error_name = ui->stackedWidget_in->findChild<QLabel*>("label_2");
     QLabel *error_desc = ui->stackedWidget_in->findChild<QLabel*>("label_11");
     QLabel *error_lieu = ui->stackedWidget_in->findChild<QLabel*>("label_12");
     QLabel *error_etat = ui->stackedWidget_in->findChild<QLabel*>("label_14");
      //QLabel *error_genre = ui->stackedWidget_in->findChild<QLabel*>("label_15");

     if (n==1)
     {
         if ((lineEdit_nom->text()=="") || (lineEdit_Desc->text()=="")||(lineEdit_lieuEvent->text()=="")|| (lineEdit_EtatEvent->text()==""))
         {

              if(lineEdit_nom->text()==""){error_name->show(); error_name->setText("Champs Obligatoire !"); }
              if(lineEdit_Desc->text()==""){error_desc->show(); error_name->setText("Champs Obligatoire !"); }
              if(lineEdit_lieuEvent->text()==""){error_lieu->show(); error_name->setText("Champs Obligatoire !"); }
              if(lineEdit_EtatEvent->text()==""){error_etat->show(); error_name->setText("Champs Obligatoire !"); }
               //if(!(checkBox_P->isChecked())&&(!(checkBox_S->isChecked()))){error_genre->show(); error_genre->setText("Choisier un genre!");}
              return  0;
         }else
         {

             qDebug()<<"suii3";
             return  1;
         }


     }

     qDebug()<<"suii4";
         return 1;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //refrech l'affichage
    ui->tableView_events->setModel(Evt.afficher_event());

   //controle de saisir
    // ui->l_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
    ui->lineEditTitre_event->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
    ui->lineEdit_Desc->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
    ui->lineEdit_lieuEvent->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
    ui->lineEdit_EtatEvent->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));


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



//ajouter les option de combobox
   /* ui->comboBox_events->addItem("Sélectionnez un intervenant");
    ui->comboBox_events->setItemData(0, QVariant(Qt::UserRole), Qt::UserRole);  //une option non selectionne
    ui->comboBox_events->addItem("Psychiatre");
    ui->comboBox_events->addItem("Médecin généraliste");
    ui->comboBox_events->addItem("Neurologue");*/



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
}

MainWindow::~MainWindow()
{
    delete ui;
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


     QStringList lineEditNames = {"Titre_event_update", "lineEdit_Desc_update", "lineEdit_lieuEvent_update",
                                  "lineEdit_EtatEvent_update"};

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

}
//add events
void MainWindow::on_validation_ajout_clicked()
{
if (controle_saisir(1))
{

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

    QString etat_event=ui->lineEdit_EtatEvent->text();

    QDateTime date_event=ui->dateTimeEdit_event->dateTime();


      //convertir image en binaire BLOB
            QByteArray imageData;
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            image_event.save(&buffer, "PNG");
            buffer.close();

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

           QLineEdit *lineEdit_EtatEvent = ui->stackedWidget_in->findChild<QLineEdit*>("lineEdit_EtatEvent_update");
           lineEdit_EtatEvent->setText(etat_event);
           lineEdit_EtatEvent->update();


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


      QString etat_event=ui->lineEdit_EtatEvent_update->text();

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
     ui->stackedWidget_2->setCurrentIndex(2);
}
