#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QtGui>
#include "event.h"
#include "patient.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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
   ui->label_nbGIF->setFixedSize(161,131);
   ui->tableView->setModel(pat.afficher_patient());
}

MainWindow::~MainWindow()
{
    delete ui;
}







void MainWindow::on_Ajouter_event_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(0);
}

void MainWindow::on_Ajouter_patient_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_uploade_fichier_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir un fichier"), "", tr("Images (*.png *.xpm *.jpg)"));
      if (!fileName.isEmpty()) {
          QImage image(fileName);
          if (image.isNull()) {
              QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
          } else {
              ui->imageLabel->setPixmap(QPixmap::fromImage(image));
              ui->imageLabel->setScaledContents(true);
          }
      }
}

void MainWindow::on_Events_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(2);
}

void MainWindow::on_patients_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_validation_ajout_clicked()
{
   //int id_event=ui->lineEdit_IntervenantEvent->text().toInt();
   int note_event=ui->lineEdit_noteEvent->text().toInt();
   QString Titre_event=ui->Titre_event->text();
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

Event E(note_event, Titre_event,  Desc_event,  lieuEvent,  genre_event,  etat_event,  date_event);

bool test=E.ajouter_event();

if(test)
{
    ui->tableView->setModel(pat.afficher_patient());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("ajouter effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
else
{
    QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("ajouter non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
}

void MainWindow::on_validation_ajout_patient_clicked()
{
    QString nom_patient=ui->nom_patient->text();
    QString prenom_patient=ui->prenom_patient->text();
    QString photo_patient=ui->photo_patient->text();
    QString  etat_patient;
    if(ui->radioButton_Pub->isChecked()) {
        etat_patient = ui->radioButton_Pub->text();
    }
    else if(ui->radioButton_Sensib->isChecked()) {
        etat_patient = ui->radioButton_Sensib->text();
    }
    int num_patient=ui->num_patient->text().toInt();
    int num_urg=ui->num_urg->text().toInt();
    QDateTime DOB=ui->dateTimeEdit_DOB->dateTime();

Patient p(nom_patient, prenom_patient, DOB, photo_patient, num_patient, num_urg, etat_patient);

bool test=p.ajouter_patient();

if(test)
{
    QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("ajouter effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
else
{
    QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("ajouter non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
}

void MainWindow::on_Patients_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_validation_ajout_2_clicked()
{
    QString nom_patient=ui->nom_patient->text();
    QString prenom_patient=ui->prenom_patient->text();
    QString photo_patient=ui->photo_patient->text();
    QString  etat_patient;
    if(ui->radioButton_Pub->isChecked()) {
        etat_patient = ui->radioButton_Pub->text();
    }
    else if(ui->radioButton_Sensib->isChecked()) {
        etat_patient = ui->radioButton_Sensib->text();
    }
    int num_patient=ui->num_patient->text().toInt();
    int num_urg=ui->num_urg->text().toInt();
    QDateTime DOB=ui->dateTimeEdit_DOB->dateTime();

Patient p(nom_patient, prenom_patient, DOB, photo_patient, num_patient, num_urg, etat_patient);

bool test=p.ajouter_patient();

if(test)
{
    QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("ajouter effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
else
{
    QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("ajouter non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
}
void MainWindow::on_affichePatient_clicked()
{
        ui->stackedWidget_in->setCurrentIndex(2);
}
void MainWindow::on_supprimerPatient_clicked()
{
        int id=ui->IDPatient->text().toInt();
        bool test=pat.supprimer_patient(id);
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("suppression effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
            ui->tableView->setModel(pat.afficher_patient());
        }
        else
        {
            QMessageBox::information(nullptr, QObject::tr("not ok"),
                                     QObject::tr("suppression non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
        }
}

void MainWindow::on_supprimerPatient_2_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(5);
}



void MainWindow::on_modifierPatient_2_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::on_updat_done_clicked()
{
    int id_patient=ui->nom_patient_4->text().toInt();
    QString nom_patient=ui->nom_patient_3->text();
    QString prenom_patient=ui->prenom_patient_3->text();
    QString photo_patient=ui->photo_patient_3->text();
    QString  etat_patient;
    if(ui->radioButton_Pub->isChecked()) {
        etat_patient = ui->radioButton_Pub_6->text();
    }
    else if(ui->radioButton_Sensib_5->isChecked()) {
        etat_patient = ui->radioButton_Sensib->text();
    }
    int num_patient=ui->num_patient_3->text().toInt();
    int num_urg=ui->num_urg_3->text().toInt();
    QDateTime DOB=ui->dateTimeEdit_DOB_3->dateTime();

Patient p(nom_patient, prenom_patient, DOB, photo_patient, num_patient, num_urg, etat_patient);

bool test=p.modifier(id_patient);

if(test)
{
    ui->tableView->setModel(pat.afficher_patient());
    QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("modifier effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
else
{
    QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("modifier non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
}
