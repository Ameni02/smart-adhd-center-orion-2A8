#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QtGui>
#include "event.h"
#include "patient.h"
#include <QCloseEvent>
#include <QSqlRecord>
#include <QRegularExpression>
#include <QStatusBar>
#include <QPdfWriter>
#include <QPainter>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtSql/QSqlError>
#include "QSslSocket"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();

    connect(ui->mail, SIGNAL(clicked()),this, SLOT(sendMail()));
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
   QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(ui->tableView->model());
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->tableView->setModel(proxyModel);
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModel, &QSortFilterProxyModel::sort);
    ui->tableView->setSortingEnabled(true);
   /* ui->nom_patient->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
    ui->nom_patient->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
    ui->prenom_patient->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));*/



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
/*
void MainWindow::on_validation_ajout_patient_clicked()
{
    QString nom_patient=ui->nom_patient->text();
    QString prenom_patient=ui->prenom_patient->text();
    QImage photo_patien;
    QString  etat_patient;
    if(ui->radioButton->isChecked()) {
    etat_patient = "eqweqe";
    }
    else if(ui->radioButtonEnfant->isChecked()) {
        etat_patient =ui->radioButtonEnfant->text();
    }
    int num_patient=ui->num_patient->text().toInt();
    int num_urg=ui->num_urg->text().toInt();
    QDateTime DOB=ui->dateTimeEdit_DOB->dateTime();
    QByteArray imageData;
           QBuffer buffer(&imageData);
           buffer.open(QIODevice::WriteOnly);
           imagePatient.save(&buffer, "JPG");
           buffer.close();

Patient p(nom_patient, prenom_patient, DOB, num_patient, num_urg, etat_patient, imageData );

bool test=p.ajouter_patient();

if(test)
{
    QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("ajouter effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
    ui->tableView->setModel(pat.afficher_patient());

}
else
{
    QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("ajouter non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
}*/

void MainWindow::on_Patients_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_validation_ajout_2_clicked()
{
    QString nom_patient=ui->nom_patient->text();
    QString prenom_patient=ui->prenom_patient->text();
    QByteArray photo_patient;
    QString  etat_patient;
    if(ui->radioButton->isChecked()) {
    etat_patient = "eqweqe";
    }
    else if(ui->radioButtonEnfant->isChecked()) {
    etat_patient =ui->radioButtonEnfant->text();
    }
    int num_patient=ui->num_patient->text().toInt();
    int num_urg=ui->num_urg->text().toInt();
    QDateTime DOB=ui->dateTimeEdit_DOB->dateTime();
    QByteArray imageData;
           QBuffer buffer(&imageData);
           buffer.open(QIODevice::WriteOnly);
           imagePatient.save(&buffer, "JPG");
           buffer.close();

Patient p(nom_patient, prenom_patient, DOB, num_patient, num_urg, etat_patient, imageData);

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
        ui->tableView->setModel(pat.afficher_patient());

}
void MainWindow::on_supprimerPatient_clicked()
{
        int id=ui->IDPatient_2->text().toInt();
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

void MainWindow::on_statisque_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(6);
}

void MainWindow::on_updat_done_clicked()
{
    int id_patient=ui->nom_patient_4->text().toInt();
    QString nom_patient=ui->nom_patient_3->text();
    QString prenom_patient=ui->prenom_patient_3->text();
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
    QByteArray imageData;
           QBuffer buffer(&imageData);
           buffer.open(QIODevice::WriteOnly);
           imagePatient.save(&buffer, "JPG");
           buffer.close();

Patient p(nom_patient, prenom_patient, DOB, num_patient, num_urg, etat_patient, imageData);

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

void MainWindow::on_txtFilter_textChanged(const QString &arg1)
{
    ui->tableView->setModel(pat.afficherRecherche(arg1));
}


void MainWindow::on_uploade_photo_clicked() // Choose a picture to add in ADD new user (Admin Side)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a Picture"), "", tr("Images (*.png *.xpm *.jpg)"));
      if (!fileName.isEmpty()) {
          QImage image(fileName);
          if (image.isNull()) {
              QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
          } else {
              imagePatient = image;
          }
      }
}

void MainWindow::on_pdf_2_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PATIENTS where IDPATIENT = :id");
    query.bindValue(":id",ui->IDPatient_2->text());
    query.exec();
        QString fileName = QFileDialog::getSaveFileName(this, "Save PDF File", "", "*.pdf");
        if (fileName.isEmpty()) {
            return;
        }
        QPdfWriter writer(fileName);
        QPainter painter(&writer);
        QFont font("Arial", 12);
        QPen pen(Qt::black, 1);
        int row = 0;
        while (query.next()) {
            int id = query.value("IDPATIENT").toInt();
            QString nom = query.value("NOM").toString();
            QString prenom = query.value("PRENOM").toString();
            QDateTime DOB = query.value("DOB").toDateTime();
            int num_patient=query.value("NUMPERSO").toInt();
            int num_urg=query.value("NUMURGENCE").toInt();
            QString etat = query.value("ETAT").toString();


            painter.setFont(font);
            painter.setPen(pen);
            painter.drawText(100, 100 + row * 20, QString("%1 %2 %3 %4 %5 %6 %7").arg(id).arg(nom).arg(prenom).arg(etat).arg(QString::number(num_patient, 'f', 2)).arg(QString::number(num_urg, 'f', 2)).arg(DOB.toString()));
            row++;
        }
        painter.end();
        QMessageBox::information(this, "Exported", "Data exported to PDF file.");
}

void MainWindow::makePlot()
{
    QSqlQuery query;
    query.exec("SELECT COUNT(IDPATIENT) FROM PATIENTS WHERE ETAT='adult' ");
    query.next();
    int res = query.value(0).toInt();
    query.exec("SELECT COUNT(IDPATIENT) FROM PATIENTS WHERE ETAT='enfant' ");
    query.next();
    int res1 = query.value(0).toInt();
    QCPBars *myBars = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    // now we can modify properties of myBars:
    myBars->setName("Bars Series 1");
    QVector<double> keyData;
    QVector<double> valueData;
    keyData << 0  << 1 ;
    valueData << res << res1 ;
    myBars->setData(keyData, valueData);
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

void MainWindow::on_photo_patient_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a Picture"), "", tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            if (image.isNull()) {
                QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
            } else {
                imagePatient = image;
            }
        }
}

void MainWindow::sendMail()
{

    Smtp* smtp = new Smtp("gmootaz3@gmail.com", "dieitpkjiqrcnwmm", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("gmootaz3@gmail.com", "gmootaz3@gmail.com" , "subject","message");
}



