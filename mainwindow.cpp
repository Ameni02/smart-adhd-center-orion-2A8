#include "mainwindow.h"
#include "imagetablemodel.h"
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
#include "QByteArray"
#include "QBuffer"
#include <QTableView>
#include <QTableWidget>
#include <iostream>
#include "centeredtextdelegate.h"
#include "buttonDelegate.h"


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
  // ui->tableView->setModel(pat.afficher_patient());


       QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
       proxyModel->setSourceModel(ui->tableView->model());
       proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
       ui->tableView->setModel(proxyModel);
       connect(ui->tableView->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModel, &QSortFilterProxyModel::sort);
       ui->tableView->setSortingEnabled(true);
       ui->tableView->setColumnWidth(8, 150);
       ui->tableView->setGridStyle(Qt::MPenStyle);
      // ui->tableView->resizeColumnsToContents();
       //ui->tableView->resizeRowsToContents();



    ui->num_patient->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->num_urg->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->nom_patient->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
    ui->prenom_patient->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));




   ui-> tableView->setFocusPolicy(Qt::NoFocus);
   ui-> tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
 ui->   tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
ui->    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setVisible(true);
   ui-> tableView->setShowGrid(false);
    ui->tableView->setObjectName("tableView");
   // ui->tableView->setRowCount(0);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);




    // Create and set the custom delegate to the last column of the table view
    ButtonDelegate* buttonDelegate = new ButtonDelegate(ui->tableView);
    ui->tableView->setItemDelegateForColumn(ui->tableView->model()->columnCount() - 1, buttonDelegate);
    // Connect the buttonClicked() signal to a slot
      int id=ui->IDPatient_2->text().toInt();
    connect(buttonDelegate, &ButtonDelegate::buttonClicked, this, &MainWindow::onButtonClicked); // Replace MyClass::onButtonClicked with the appropriate slot function



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onButtonClicked(const QModelIndex& index) {
    // Get the row and column index of the clicked button
    int row = index.row();
    int column = index.column();

    // Call pat.supprimer_patient(id) with the appropriate row and column information
    // Replace this with your actual function call
    pat.supprimer_patient(row);
}


void MainWindow::populateModel() {
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->tableView->model());
    if (!model)
        return;

    QStringList headers = { "IDPATIENT", "NOM", "PRENOM", "DOB", "NUMPERSO","NUMURGENCE", "ETAT", "PDR", "PHOTO" };
    QList<QStringList> data = { headers};

    int j = 0;
    for (const QStringList &row : data) {
        model->insertRow(j);
        j++;
        int i = 0;
        for (const QString &x : row) {
            QModelIndex index = model->index(j - 1, i);
            model->setData(index, x);
            model->setData(index, QColor(255, 255, 255), Qt::ForegroundRole);
            model->setData(index, font(), Qt::FontRole);

            if (j == 1 && i <= 4) {
                model->insertColumn(i, QModelIndex());
                model->setData(model->index(0, i, QModelIndex()), Qt::AlignCenter, Qt::TextAlignmentRole);
            }

            i++;
        }
    }
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



void MainWindow::on_Patients_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_validation_ajout_2_clicked()
{
    QString nom_patient=ui->nom_patient->text();
    QString prenom_patient=ui->prenom_patient->text();
    QString  etat_patient;
    if(ui->radioButtonAdult->isChecked()) {
    etat_patient = ui->radioButtonAdult->text();
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
QSqlQuery query;
QVariant nup = QVariant(num_patient);
QVariant nur = QVariant(num_urg);
query.prepare("INSERT INTO PATIENTS (NOM,PRENOM,DOB,NUMPERSO,NUMURGENCE,ETAT,PHOTO) values (:nom_patient,:prenom_patient , :DOB,:num_patient , :num_urg, :etat_patient  , :photo_patient)");

query.bindValue(":nom_patient", nom_patient);
query.bindValue(":prenom_patient", prenom_patient);
query.bindValue(":DOB", DOB);
query.bindValue(":photo_patient", imageData);
query.bindValue(":num_patient", nup);
query.bindValue(":num_urg", nur);
query.bindValue(":etat_patient", etat_patient);

query.exec();
}
void MainWindow::on_affichePatient_clicked()
{

        ui->stackedWidget_in->setCurrentIndex(2);
        ImageTableModel *imageModel = new ImageTableModel(this);
        imageModel->setTable("PATIENTS");
        imageModel->select();
        ui->tableView->setModel(imageModel);

        CenteredTextDelegate* centeredTextDelegate = new CenteredTextDelegate(ui->tableView);

        // Set the delegate on the table view for the desired column (e.g., column 0)
        ui->tableView->setItemDelegateForColumn(0, centeredTextDelegate);
        ui->tableView->setItemDelegateForColumn(1, centeredTextDelegate);
        ui->tableView->setItemDelegateForColumn(2, centeredTextDelegate);
        ui->tableView->setItemDelegateForColumn(3, centeredTextDelegate);
        ui->tableView->setItemDelegateForColumn(4, centeredTextDelegate);
        ui->tableView->setItemDelegateForColumn(5, centeredTextDelegate);
        ui->tableView->setItemDelegateForColumn(6, centeredTextDelegate);
        ui->tableView->setItemDelegateForColumn(7, centeredTextDelegate);
       // ui->tableView->setItemDelegateForColumn(8, centeredTextDelegate);


}





void MainWindow::on_supprimerPatient_2_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(6);
}



void MainWindow::on_modifierPatient_2_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(5);
}

void MainWindow::on_statisque_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(7);
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


void MainWindow::on_uploade_photo_clicked()
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


    smtp->sendMail("gmootaz3@gmail.com", "gmootaz3@gmail.com" , "hyperflow","you have a meeting with your doctor tomorow dont forget");
}




void MainWindow::on_supprimerPatient_3_clicked()
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






