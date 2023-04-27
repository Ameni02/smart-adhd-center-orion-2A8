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
   //ui->l_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
     ui->l_nom->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
        ui->l_description->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

           ui->l_genre->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));


           ui->l_id_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));
            ui->l_nom_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
               ui->l_description_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

                  ui->l_genre_2->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));

                  ui->table_act->setModel(A.afficher); //chercher

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
                              ui->stackedWidget_in->setCurrentIndex(0);
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
    ui->table_act->setModel(A.recherche_NOM(arg1));

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

void MainWindow::on_table_act_activated(const QModelIndex &index)
{
    int row = index.row();
    QSqlQuery query1;
    QModelIndex idIndex = index.sibling(row,0);
    QVariant idVariant = ui->tableView->model()->data(idIndex);
    QString idIntervenant;
    idIntervenant = idVariant.toString();
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
            ui->imageLabel_4->setPixmap(pixmap);
        } else {
            qDebug() << "PHOTO field not found in query result set";
        }
    } else {
        qDebug() << "No records found for the query";
    }
    ui->lineEdit_6->setText(query1.value("NOM").toString());
    ui->lineEdit_7->setText(query1.value("PRENOM").toString());
    ui->Titre_40->setText(idIntervenant);
    ui->Titre_41->setText(query1.value("NUM").toString());
    ui->Titre_42->setText(query1.value("SALAIRE").toString());
    ui->dateTimeEdit_event_5->setDateTime(query1.value("DOB").toDateTime());
    QStringList items,items2;
    ui->comboBox_7->clear();
    items.append(query1.value("TYPE").toString());
    ui->comboBox_7->addItems(items);
    ui->comboBox_7->setEditable(false);
    ui->comboBox_7->setEnabled(false);
    ui->comboBox_8->clear();
    items2.append(query1.value("ETAT").toString());
    ui->comboBox_8->addItems(items2);
    ui->comboBox_8->setEditable(false);
    ui->comboBox_8->setEnabled(false);
    ui->stackedWidget_in->setCurrentIndex(8);
}
