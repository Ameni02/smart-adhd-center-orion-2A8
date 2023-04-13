#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"activite.h"
#include"connect.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QIntValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QTextCharFormat>
#include <QApplication>
#include <QCalendarWidget>
#include <QDate>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include "historiquec.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);//controle de saisie
   ui->l_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
     ui->l_nom->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
        ui->l_description->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

           ui->l_genre->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));


           ui->l_id_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
            ui->l_nom_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
               ui->l_description_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

                  ui->l_genre_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

                  ui->table_act->setModel(A.afficher()); //chercher
 ui->table_tache->setModel(T.afficher_tache());
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
}

MainWindow::~MainWindow()
{
    delete ui;  // liberation des donnees
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



void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(0);

}

void MainWindow::on_valider_ajout_clicked()
{
    int idactivite=ui->l_id->text().toInt();
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
activite A(idactivite ,Nom ,Description ,Genre ,Cible);
qDebug() << "Message à afficher sur la console";
bool test=A.ajouter();
     if (test)
     {
    ui->table_act->setModel(A.afficher()); // setmodel hyaaa eli lhyaaa bel affichage fi label table_act

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


void MainWindow::on_ajouter_tache_clicked()
{

    int idtache=ui->l_idtache->text().toInt();
    QString Nom_inter=ui->l_nom_interv->text();

     QString Nom_tache=ui->l_tache->text();


              QString Etat;
             if(ui->l_oui->isChecked()) {
                     Etat = ui->l_oui->text();
                 }
                 else if(ui->l_non->isChecked()) {
                     Etat = ui->l_non->text();
                 }

Tache T(idtache, Nom_inter, Nom_tache, Etat);



  qDebug() << "Message à afficher sur la console";

     bool test=T.ajouter_tache();
     if (test)
     {

   ui->table_tache->setModel(T.afficher_tache()); // setmodel hyaaa eli lhyaaa bel affichage fi label table_act


         QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("ajout successful.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

      }
       else

         {
         QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                QObject::tr("ajout failed.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);


         }
}


void MainWindow::on_pushButton_2_clicked()
{
    activite A1;
    A1.setid(ui->le_supp->text().toInt());
    bool test=A1.supprmier(A1.getid());
QMessageBox msgBox;

    if (test)
    {
  ui->table_act->setModel(A.afficher());//updateeeeeeeeeeeeeee label affichage
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


void MainWindow::on_update_clicked()
{
      ui->stackedWidget_in->setCurrentIndex(1);
}





void MainWindow::on_pushButton_3_clicked()
{
  ui->stackedWidget_in->setCurrentIndex(2);
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
    activite A(idactivite,Nom,Description,Genre,Cible);

    bool test=A.modifier(idactivite);
    if (test)
    {

        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);
        ui->table_act->setModel(A.afficher());
    }
    else
    {
     QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget_in->setCurrentIndex(1);
}

void MainWindow::on_gestion_activite_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(5);
}

void MainWindow::on_chercher_clicked()
{
    ui->table_act->setModel(A.recherche_NOM(ui->le_chercher->text()));
}

void MainWindow::on_stat_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(2);
      activite A;
       QGridLayout *StatsLayout1 = ui->stackedWidget_in->findChild<QGridLayout*>("gridLayout");
       StatsLayout1->addWidget(A.Stat(), 0, 0);

}



void MainWindow::on_croissant_clicked()
{
    ui->table_act->setModel(A.tri_croissant());
}

void MainWindow::on_decroissant_clicked()
{
     ui->table_act->setModel(A.tri_decroissant());
}

void MainWindow::on_pdf_clicked()
{


        // Exécution de la requête SQL pour récupérer les données
        QSqlQuery query;
        query.exec("SELECT * FROM ACTIVITES");

        // Création d'un fichier PDF temporaire
        QString pdfFileName = "temp_pdf_file.pdf";
        QPdfWriter writer(pdfFileName);
        QPainter painter(&writer);


        int yPos = 1000;
        while (query.next()) {
            // Récupération des données de la requête
            QString champ1 = query.value(0).toString();
            QString champ2 = query.value(1).toString();
            QString champ3 = query.value(2).toString();
  QString champ4 = query.value(3).toString();
    QString champ5 = query.value(4).toString();

    QFont font("Arial", 12);
      painter.setFont(font);
      QPen pen(Qt::black);
      painter.setPen(pen);


      QColor textColor(255, 0, 0); // Rouge
      pen.setColor(textColor);
      painter.setPen(pen);

            // Dessin des données sur le document PDF
            painter.drawText(QRect(1000, yPos, 10000, 500), champ1);
            painter.drawText(QRect(2000, yPos, 10000, 500), champ2);
            painter.drawText(QRect(3000, yPos, 10000, 500), champ3);
   painter.drawText(QRect(4000, yPos, 10000, 500), champ4);
      painter.drawText(QRect(5000, yPos, 10000, 500), champ5);
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
     ui->stackedWidget_in->setCurrentIndex(3);

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

void MainWindow::on_todoo_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(4);
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
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




void MainWindow::on_ajoutDate_clicked()
{
    int idactivite=ui->comboBoxcalander->currentText().toInt();
    QDate date=ui->dateEdit->date();

      QString date_v=date.toString("yyyy-MM-dd");

             calender_A A (idactivite,date_v);

    bool test=A.calender_ajout();
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
/*
activite A1;
    A1.setid(ui->le_supp->text().toInt());
    bool test=A1.supprmier(A1.getid());
QMessageBox msgBox;

    if (test)
    {
  ui->table_act->setModel(A.afficher());//updateeeeeeeeeeeeeee label affichage
        QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("delete successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel); }
      else
        {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                               QObject::tr("delete failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
        }*/

void MainWindow::on_le_chercher_textChanged(const QString &arg1)
{
    ui->table_act->setModel(A.recherche_NOM(arg1));

}
