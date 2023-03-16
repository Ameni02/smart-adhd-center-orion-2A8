#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QtGui>
//#include "event.h"
#include "intervenants.h"
#include <QCloseEvent>
#include <QSqlRecord>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(I.afficher());
    ui->stackedWidget->setCurrentIndex(1);
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Ajouter_event_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(0);
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

void MainWindow::on_validation_ajout_clicked()
{
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
    QMessageBox::information(nullptr, QObject::tr("ok"),
                             QObject::tr("ajouter effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
else
{
    QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("ajouter non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
}
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Ajouter_event_2_clicked() //Login
{
   QString id = ui->Titre_20->text();
   QString password = ui->Titre_21->text();
   if (id == "")
   {
       QMessageBox::information(nullptr, QObject::tr("not ok"),
                                QObject::tr("ID Cannot be empty\n" "Click cancel to exit."),QMessageBox::Cancel);
   }
   else
   if (password == "")
   {
       QMessageBox::information(nullptr, QObject::tr("not ok"),
                                QObject::tr("Password Cannot be empty\n" "Click cancel to exit."),QMessageBox::Cancel);
   }
   else
   {
       QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM INTERVENANTS WHERE IDINTERVENANT = :id AND MDP = :password");
       query.bindValue(":id", id);
       query.bindValue(":password", password);
       if (query.exec() && query.next()) {
           int count = query.value(0).toInt();
           if (count == 1) {
             createsession(id.toInt());
             qDebug() << "Login successful";
             ui->stackedWidget->setCurrentIndex(0);
             ui->stackedWidget_in->setCurrentIndex(1);
           } else {
               qDebug() << "Login failed";
               QMessageBox::critical(this, "Error", "Invalid id or password");
           }
       } else {
           // Error executing query, display error message
           qDebug() << "Error executing query";
           QMessageBox::critical(this, "Error", "Error executing query");
       }

   }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Ajouter_event_3_clicked() //SignUp
{
    bool errornom = false,errorPrenom=false,errornum=false,errormdp=false;
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("^[A-Za-z]+$"), this);
    QRegularExpressionValidator *validatornum = new QRegularExpressionValidator(QRegularExpression("^\\d{8}$"),this);
    QRegularExpressionValidator *validatormdp = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"), this);
    ui->Titre_22->setValidator(validator);
    ui->Titre_23->setValidator(validator);
    ui->Titre_24->setValidator(validatornum);
    ui->Titre_25->setValidator(validatormdp);
    bool vide=false;
    QString nom=ui->Titre_22->text();
    if (nom == "")
    {
        vide = true;
    }
    if (!ui->Titre_22->hasAcceptableInput())
    {
        errornom=true;
    }
    QString prenom=ui->Titre_23->text();
    if (prenom == "")
    {
        vide = true;
    }
    if (!ui->Titre_23->hasAcceptableInput())
    {
        errorPrenom=true;
    }
    int num=ui->Titre_24->text().toInt();
    if (ui->Titre_24->text()=="")
    {
        vide = true;
    }
    if (!ui->Titre_24->hasAcceptableInput())
    {
        errornum=true;
    }
    QString mdp=ui->Titre_25->text();
    if (mdp == "")
    {
        vide = true;
    }
    if ((!ui->Titre_25->hasAcceptableInput())||(mdp.length()<5))
    {
        errormdp=true;
    }
    QString mdp1=ui->Titre_26->text();
    if (mdp1 == "")
    {
        vide = true;
    }
    if ((mdp==mdp1)&&(vide==false)&&(errornum==false)&&(errornom==false)&&(errorPrenom==false)&&(errormdp==false))
    {
 INTERVENANTS I(nom,prenom,num,mdp);

 bool test=I.Signup();

 if(test)
 {
     ui->tableView->setModel(I.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("SignUp Successfull\n" "Click cancel to exit."),QMessageBox::Cancel);
     ui->stackedWidget->setCurrentIndex(1);
 }
 else
 {
     QMessageBox::information(nullptr, QObject::tr("not ok"),
                              QObject::tr("Unable to Signup\n" "Click cancel to exit."),QMessageBox::Cancel);
 }

}
    else
    {
        if (mdp != mdp1)
        {
         QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                QObject::tr("Passwords Don't match"),QMessageBox::Cancel);
        }
        if (vide == true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Elements can't be empty"),QMessageBox::Cancel);
        }
        if (errorPrenom==true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The First Name is Invalid"),QMessageBox::Cancel);
        }
        if (errornom==true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Last Name is Invalid"),QMessageBox::Cancel);
        }
        if (errornum==true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Phone Number is Invalid"),QMessageBox::Cancel);
        }
        if (errormdp==true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Password is Invalid"),QMessageBox::Cancel);
        }


    }
}

void MainWindow::on_Exit_clicked() // Close session when Clicking on Quit button
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SESSIONS");
    if (query.exec() && query.next()) {
        qDebug() << query.value(1);
        closesession(query.value(1).toInt());
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
         qDebug() << "Error";
    }

}

void MainWindow::on_Intervenants_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::mySlot() // Close session when clicking on the X button
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SESSIONS");
    if (query.exec() && query.next()) {
        qDebug() << query.value(1);
        closesession(query.value(1).toInt());
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
         qDebug() << "Error";
    }
}

void MainWindow::on_Ajouter_event_4_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(5);
}

void MainWindow::on_Ajouter_event_6_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::on_Ajouter_event_5_clicked() // Add User Information to add in ADD new user (Admin Side)
{
    bool vide = false;
    bool errornom = false,errorPrenom=false,errornum=false,errorSalaire=false,errormdp=false;
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("^[A-Za-z]+$"), this);
    QRegularExpressionValidator *validatornum = new QRegularExpressionValidator(QRegularExpression("^\\d{8}$"),this);
    QRegularExpressionValidator *validatormdp = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9_]*$"), this);
    //QDoubleValidator *validatorSalary = new QDoubleValidator(0.00,100000.00,2,this);
    //validatorSalary->setNotation(QDoubleValidator::StandardNotation);
    ui->Titre_27->setValidator(validator);
    ui->Titre_28->setValidator(validator);
    ui->Titre_30->setValidator(validatornum);
    ui->Titre_31->setValidator(validatormdp);
    //ui->Titre_29->setValidator(validatorSalary);
    QString nom=ui->Titre_27->text();
    if (nom == "")
    {
       vide = true;
    }
    if (!ui->Titre_27->hasAcceptableInput())
    {
        errornom = true;
    }
    QString prenom=ui->Titre_28->text();
    if (prenom == "")
    {
        vide = true;
    }
    if (!ui->Titre_28->hasAcceptableInput())
    {
        errorPrenom = true;
    }
    QString numtest=ui->Titre_30->text();
    if (numtest=="")
    {
        vide = true;
    }
    if (!ui->Titre_30->hasAcceptableInput())
    {
        errornum = true;
    }
    int num=ui->Titre_30->text().toInt();
    QString mdp=ui->Titre_31->text();
    if (mdp == "")
    {
        vide = true;
    }
    if ((mdp.length()<5)||(!ui->Titre_31->hasAcceptableInput()))
    {
        errormdp=true;
    }
    QString Salaire=ui->Titre_29->text();
    if (Salaire == "")
    {
        vide = true;
    }
    //if (!ui->Titre_29->hasAcceptableInput())
    //{
      //  errorSalaire = true;
    //}
    float Sal = Salaire.toFloat();
    QString type;
    if(ui->comboBox->currentIndex() != -1) {
        type = ui->comboBox->currentText();
    }
    else
    {
        vide = true;
    }
    QString etat;
    if(ui->comboBox_2->currentIndex() != -1) {
        etat = ui->comboBox->currentText();
    }
    else
    {
        vide = true;
    }
    QDateTime DOB=ui->dateTimeEdit_event_2->dateTime();
    if (imageIntervenant.isNull())
    {
    vide = true;
    }
    if ((vide == false)&&(errorPrenom==false)&&(errornom==false)&&(errormdp==false)&&(errorSalaire==false)&&(errornum==false))
{
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        imageIntervenant.save(&buffer, "JPG");
        buffer.close();
        INTERVENANTS I1(nom, prenom,num,mdp,Sal,type,etat,DOB,imageData);
 bool test = I1.AjouterIntervenant();
 if(test)
 {
     ui->tableView->setModel(I.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("Added Successfull\n"),QMessageBox::Cancel);
     ui->stackedWidget_in->setCurrentIndex(4);
 }
 else
 {
     QMessageBox::information(nullptr, QObject::tr("not ok"),
                              QObject::tr("Unable to Add\n" "Click cancel to exit."),QMessageBox::Cancel);
 }
}
else
{
        if (vide==true)
        {
QMessageBox::information(nullptr, QObject::tr("not ok"),
                         QObject::tr("Error : Empty Values\n" "Click cancel to exit."),QMessageBox::Cancel);
        }
        if (errorPrenom == true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The First Name is Invalid"),QMessageBox::Cancel);
        }
        if (errornom == true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Last Name is Invalid"),QMessageBox::Cancel);
        }
        if (errornum == true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Phone Number is Invalid"),QMessageBox::Cancel);
        }
        if (errorSalaire == true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Salary is Invalid"),QMessageBox::Cancel);
        }
        if (errormdp == true)
        {
            QMessageBox::information(nullptr, QObject::tr("Probleme"),
                                   QObject::tr("The Password is Invalid"),QMessageBox::Cancel);
        }
}
}

void MainWindow::on_Ajouter_event_8_clicked()
{
    int id=ui->Titre_event_2->text().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM INTERVENANTS WHERE IDINTERVENANT = :id");
    query.bindValue(":id",id);
    query.exec();
    ui->tableView->setModel(I.afficher());
    ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::on_Ajouter_event_7_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(3);
}

void MainWindow::on_Ajouter_event_10_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM SESSIONS");
    if (query.exec() && query.next()) {
        qDebug() << query.value(1);
        closesession(query.value(1).toInt());
        ui->stackedWidget->setCurrentIndex(1);
        event->accept();
    }
    else
    {
         qDebug() << "Error";
    }
}

void MainWindow::on_uploade_fichier_2_clicked() // Choose a picture to add in ADD new user (Admin Side)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a Picture"), "", tr("Images (*.png *.xpm *.jpg)"));
      if (!fileName.isEmpty()) {
          QImage image(fileName);
          if (image.isNull()) {
              QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
          } else {
              imageIntervenant = image;
          }
      }
}

void MainWindow::on_Profil_clicked() // Show Current User Information ReadOnly
{
    QSqlQuery query;
    QSqlQuery query1;
    QString idIntervenant;
    query.prepare("SELECT IDINTERVENANT FROM SESSIONS");
    query.exec();
    if (query.next()) {
        idIntervenant = query.value(0).toString();
    }
    query1.prepare("SELECT * from INTERVENANTS where IDINTERVENANT = :id");
    query1.bindValue(":id", idIntervenant);
    query1.exec();
    if (query1.next()) {
        QSqlRecord record = query1.record();
        int photoIndex = record.indexOf("PHOTO");
        if (photoIndex >= 0) {
            QPixmap pixmap;
            QByteArray imageData = query1.value(photoIndex).toByteArray();
            pixmap.loadFromData(imageData);
            ui->imageLabel_2->setPixmap(pixmap);
        } else {
            qDebug() << "PHOTO field not found in query result set";
        }
    } else {
        qDebug() << "No records found for the query";
    }
    ui->lineEdit_2->setText(query1.value("NOM").toString());
    ui->lineEdit->setText(query1.value("PRENOM").toString());
    ui->Titre_37->setText(idIntervenant);
    ui->Titre_36->setText(query1.value("NUM").toString());
    ui->Titre_34->setText(query1.value("SALAIRE").toString());
    ui->dateTimeEdit_event_3->setDateTime(query1.value("DOB").toDateTime());
    QStringList items,items2;
    ui->comboBox->clear();
    items.append(query1.value("TYPE").toString());
    ui->comboBox->addItems(items);
    ui->comboBox->setEditable(false);
    ui->comboBox->setEnabled(false);
    ui->comboBox_2->clear();
    items2.append(query1.value("ETAT").toString());
    ui->comboBox_2->addItems(items2);
    ui->comboBox_2->setEditable(false);
    ui->comboBox_2->setEnabled(false);
    ui->stackedWidget_in->setCurrentIndex(6);
}

void MainWindow::on_Ajouter_event_12_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(6);
}

void MainWindow::on_Ajouter_event_9_clicked() //Show Current User Inforamtion for him to update
{
    QSqlQuery query;
    QSqlQuery query1;
    QString idIntervenant;
    query.prepare("SELECT IDINTERVENANT FROM SESSIONS");
    query.exec();
    if (query.next()) {
        idIntervenant = query.value(0).toString();
    }
    query1.prepare("SELECT * from INTERVENANTS where IDINTERVENANT = :id");
    query1.bindValue(":id", idIntervenant);
    query1.exec();
    if (query1.next()) {
        QSqlRecord record = query1.record();
        int photoIndex = record.indexOf("PHOTO");
        if (photoIndex >= 0) {
            QPixmap pixmap;
            QByteArray imageData = query1.value(photoIndex).toByteArray();
            pixmap.loadFromData(imageData);
            ui->imageLabel_3->setPixmap(pixmap);
        } else {
            qDebug() << "PHOTO field not found in query result set";
        }
    } else {
        qDebug() << "No records found for the query";
    }
    ui->lineEdit_4->setText(query1.value("NOM").toString());
    ui->lineEdit_3->setText(query1.value("PRENOM").toString());
    ui->Titre_39->setText(idIntervenant);
    ui->Titre_38->setText(query1.value("NUM").toString());
    ui->Titre_35->setText(query1.value("SALAIRE").toString());
    ui->dateTimeEdit_event_4->setDateTime(query1.value("DOB").toDateTime());
    for (int i = 0; i < ui->comboBox_3->count(); i++) {
        QString currentItemText = ui->comboBox_3->itemText(i);
                if (currentItemText == query1.value("TYPE")) {
            ui->comboBox_3->setCurrentIndex(i);
            break;
        }
    }
    for (int i = 0; i < ui->comboBox_6->count(); i++) {
        QString currentItemText = ui->comboBox_6->itemText(i);
                if (currentItemText == query1.value("ETAT")) {
            ui->comboBox_6->setCurrentIndex(i);
            break;
        }
    }
    ui->stackedWidget_in->setCurrentIndex(7);
}

void MainWindow::on_Ajouter_event_11_clicked() //Update Current User Information
{
    bool vide1 = false;
    bool errornom = false,errorPrenom=false,errornum=false,errorSalaire=false;
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("^[A-Za-z]+$"), this);
    QRegularExpressionValidator *validatornum = new QRegularExpressionValidator(QRegularExpression("^\\d{8}$"),this);
    //QDoubleValidator *validatorSalary = new QDoubleValidator(this);
    //validatorSalary->setRange(20000.0, 200000.0, 2);
    ui->lineEdit_3->setValidator(validator);
    ui->lineEdit_4->setValidator(validator);
    ui->Titre_38->setValidator(validatornum);
    //ui->Titre_35->setValidator(validatorSalary);
    QString nom=ui->lineEdit_4->text();
    if (nom == "")
    {
       vide1 = true;
    }
    if (ui->lineEdit_4->hasAcceptableInput())
    {
        errornom=true;
    }
    QString prenom=ui->lineEdit_3->text();
    if (prenom == "")
    {
        vide1 = true;
    }
    if (!ui->lineEdit_3->hasAcceptableInput())
    {
        errorPrenom = true;
    }
    QString numtest=ui->Titre_38->text();
    if (numtest=="")
    {
        vide1 = true;
    }
    int num=ui->Titre_38->text().toInt();
    if (!ui->Titre_38->hasAcceptableInput())
    {
        errornum = true;
    }
    QString Salaire=ui->Titre_35->text();
   // if (Salaire == "")
    //{
      //  vide1 = true;
    //}
    if (!ui->Titre_35->hasAcceptableInput())
    {
        errorSalaire = true;
    }
    float Sal = Salaire.toFloat();
    QString type;
    if(ui->comboBox_3->currentIndex() != -1) {
        type = ui->comboBox_3->currentText();
    }
    else
    {
        vide1 = true;
    }
    QString etat;
    if(ui->comboBox_6->currentIndex() != -1) {
        etat = ui->comboBox_6->currentText();
    }
    else
    {
        vide1 = true;
    }
    QDateTime DOB=ui->dateTimeEdit_event_4->dateTime();
    if (imageIntervenant.isNull()==false)
    {
    if ((vide1 == false)&&(errorSalaire == false)&&(errornum == false)&&(errornom == false)&&(errorPrenom == false))
{
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        imageIntervenant.save(&buffer, "JPG");
        buffer.close();
        INTERVENANTS I1(ui->Titre_39->text().toInt(),nom, prenom,num,Sal,type,etat,DOB,imageData);
 bool test = I1.ModifierIntervenant();
 if(test)
 {
     ui->tableView->setModel(I.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("Modified Successfull\n"),QMessageBox::Cancel);
     QSqlQuery query;
     QSqlQuery query1;
     QString idIntervenant;
     query.prepare("SELECT IDINTERVENANT FROM SESSIONS");
     query.exec();
     if (query.next()) {
         idIntervenant = query.value(0).toString();
     }
     query1.prepare("SELECT * from INTERVENANTS where IDINTERVENANT = :id");
     query1.bindValue(":id", idIntervenant);
     query1.exec();
     if (query1.next()) {
         QSqlRecord record = query1.record();
         int photoIndex = record.indexOf("PHOTO");
         if (photoIndex >= 0) {
             QPixmap pixmap;
             QByteArray imageData = query1.value(photoIndex).toByteArray();
             pixmap.loadFromData(imageData);
             ui->imageLabel_2->setPixmap(pixmap);
         } else {
             qDebug() << "PHOTO field not found in query result set";
         }
     } else {
         qDebug() << "No records found for the query";
     }
     ui->lineEdit_2->setText(query1.value("NOM").toString());
     ui->lineEdit->setText(query1.value("PRENOM").toString());
     ui->Titre_37->setText(idIntervenant);
     ui->Titre_36->setText(query1.value("NUM").toString());
     ui->Titre_34->setText(query1.value("SALAIRE").toString());
     ui->dateTimeEdit_event_3->setDateTime(query1.value("DOB").toDateTime());
     QStringList items,items2;
     ui->comboBox->clear();
     items.append(query1.value("TYPE").toString());
     ui->comboBox->addItems(items);
     ui->comboBox->setEditable(false);
     ui->comboBox->setEnabled(false);
     ui->comboBox_2->clear();
     items2.append(query1.value("ETAT").toString());
     ui->comboBox_2->addItems(items2);
     ui->comboBox_2->setEditable(false);
     ui->comboBox_2->setEnabled(false);
     ui->stackedWidget_in->setCurrentIndex(6);
     ui->stackedWidget_in->setCurrentIndex(6);
 }
 else
 {
     QMessageBox::information(nullptr, QObject::tr("not ok"),
                              QObject::tr("Unable to Add\n" "Click cancel to exit."),QMessageBox::Cancel);
 }
}
else
    {
        if (vide1 == true)
{
QMessageBox::information(nullptr, QObject::tr("not ok"),
                         QObject::tr("Error : Empty Values\n" "Click cancel to exit."),QMessageBox::Cancel);
}
if (errornom == true)
{
    QMessageBox::information(nullptr, QObject::tr("not ok"),
                         QObject::tr("Error : Last Name Can not Contain Number\n" "Click cancel to exit."),QMessageBox::Cancel);

}
if (errorPrenom == true)
    {
        QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("Error : First Name Can not Contain Number\n" "Click cancel to exit."),QMessageBox::Cancel);

    }
if (errornum == true)
    {
        QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("Error : Phone Number is Invalid\n" "Click cancel to exit."),QMessageBox::Cancel);

    }
if (errorSalaire == true)
    {
        QMessageBox::information(nullptr, QObject::tr("not ok"),
                             QObject::tr("Error : Salary is Invalid \n" "Click cancel to exit."),QMessageBox::Cancel);

    }
    }
    }
    else
    {
        if ((vide1 == false)&&(errorSalaire == false)&&(errornum == false)&&(errornom == false)&&(errorPrenom == false))
        {
        INTERVENANTS I1(ui->Titre_39->text().toInt(),nom, prenom,num,Sal,type,etat,DOB);
 bool test = I1.ModifierIntervenant1();
 if(test)
 {
     ui->tableView->setModel(I.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("Modified Successfull\n"),QMessageBox::Cancel);
     QSqlQuery query;
     QSqlQuery query1;
     QString idIntervenant;
     query.prepare("SELECT IDINTERVENANT FROM SESSIONS");
     query.exec();
     if (query.next()) {
         idIntervenant = query.value(0).toString();
     }
     query1.prepare("SELECT * from INTERVENANTS where IDINTERVENANT = :id");
     query1.bindValue(":id", idIntervenant);
     query1.exec();
     if (query1.next()) {
         QSqlRecord record = query1.record();
         int photoIndex = record.indexOf("PHOTO");
         if (photoIndex >= 0) {
             QPixmap pixmap;
             QByteArray imageData = query1.value(photoIndex).toByteArray();
             pixmap.loadFromData(imageData);
             ui->imageLabel_2->setPixmap(pixmap);
         } else {
             qDebug() << "PHOTO field not found in query result set";
         }
     } else {
         qDebug() << "No records found for the query";
     }
     ui->lineEdit_2->setText(query1.value("NOM").toString());
     ui->lineEdit->setText(query1.value("PRENOM").toString());
     ui->Titre_37->setText(idIntervenant);
     ui->Titre_36->setText(query1.value("NUM").toString());
     ui->Titre_34->setText(query1.value("SALAIRE").toString());
     ui->dateTimeEdit_event_3->setDateTime(query1.value("DOB").toDateTime());
     QStringList items,items2;
     ui->comboBox->clear();
     items.append(query1.value("TYPE").toString());
     ui->comboBox->addItems(items);
     ui->comboBox->setEditable(false);
     ui->comboBox->setEnabled(false);
     ui->comboBox_2->clear();
     items2.append(query1.value("ETAT").toString());
     ui->comboBox_2->addItems(items2);
     ui->comboBox_2->setEditable(false);
     ui->comboBox_2->setEnabled(false);
     ui->stackedWidget_in->setCurrentIndex(6);
 }
 else
 {
     QMessageBox::information(nullptr, QObject::tr("not ok"),
                              QObject::tr("Unable to Add\n" "Click cancel to exit."),QMessageBox::Cancel);
 }
  }
        else
        {
            if (vide1 == true)
            {
        QMessageBox::information(nullptr, QObject::tr("not ok"),
                                 QObject::tr("Error : Empty Values\n" "Click cancel to exit."),QMessageBox::Cancel);

        }
         if (errornom == true)
        {
            QMessageBox::information(nullptr, QObject::tr("not ok"),
                                 QObject::tr("Error : Last Name Can not Contain Number\n" "Click cancel to exit."),QMessageBox::Cancel);

        }
             if (errorPrenom == true)
            {
                QMessageBox::information(nullptr, QObject::tr("not ok"),
                                     QObject::tr("Error : First Name Can not Contain Number\n" "Click cancel to exit."),QMessageBox::Cancel);

            }
             if (errornum == true)
            {
                QMessageBox::information(nullptr, QObject::tr("not ok"),
                                     QObject::tr("Error : Phone Number is Invalid\n" "Click cancel to exit."),QMessageBox::Cancel);

            }
             if (errorSalaire == true)
            {
                QMessageBox::information(nullptr, QObject::tr("not ok"),
                                     QObject::tr("Error : Salary is Invalid \n" "Click cancel to exit."),QMessageBox::Cancel);

            }
}
    }

}

void MainWindow::on_pushButton_4_clicked() //Choose another Picture in Update Current User Information
{
    qDebug() << "Button clicked";
        QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a Picture"), "", tr("Images (*.png *.xpm *.jpg)"));
          if (!fileName.isEmpty()) {
              QImage image(fileName);
              if (image.isNull()) {
                  QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier"));
              } else {
                  imageIntervenant = image;
                  QPixmap pixmap = QPixmap::fromImage(image);
                  ui->imageLabel_3->setPixmap(pixmap);
              }
          }
}




