#include "mainwindow.h"
#include "centeredtextdelegate.h"
#include "qsqlrecord.h"
#include "resizablebutton.h"
#include "ui_mainwindow.h"
#include"equipements.h"
#include"connection.h"
#include"Qrcode.h"
#include "event.h"
#include "xlsxdocument.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QIntValidator>
#include<QRegExpValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QtGlobal>
#include <cstdlib>
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
#include <qglobal.h>
#include <QTime>
#include <unistd.h>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QVideoWidget>
#include "sidebar.h"
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(0, this, SLOT(showFullScreen()));


    //ARDUINO FINGERPRINT
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino A is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino A is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino A is not available";
         break;
    }
    ui->pushButton->setIcon(QIcon("D:/projet/integration_ameni-sarah back up + seif/LOGO.png"));
    ui->Profil->setIcon(QIcon("D:/projet/profile.png"));
    ui->Patients->setIcon(QIcon("D:/projet/patient.png"));
    ui->Activites->setIcon(QIcon("D:/projet/activite.png"));
    ui->Intervenants->setIcon(QIcon("D:/projet/intervenant.png"));
    ui->Events->setIcon(QIcon("D:/projet/event.png"));
    ui->Equipements->setIcon(QIcon("D:/projet/equipement.png"));
    ui->quit->setIcon(QIcon("D:/projet/exit1.png"));
    ui->Exit->setIcon(QIcon("D:/projet/exit.png"));
    ui->sidebarButton->setIcon(QIcon("D:/projet/menu.png"));
    ui->affichePatient->setIcon(QIcon("D:/projet/icons8-search-account-64 (1).png"));
    ui->expoterdb_2->setIcon(QIcon("D:/projet/icons8-add-user-male-64.png"));
    ui->modifierPatient_2->setIcon(QIcon("D:/projet/icons8-user-settings-64.png"));
    ui->deletall_2->setIcon(QIcon("D:/projet/icons8-denied-64.png"));
    ui->deletall->setIcon(QIcon("D:/projet/icons8-remove-100.png"));
    ui->expoterdb->setIcon(QIcon("D:/projet/icons8-pdf-100 (1).png"));
    ui->exportxl->setIcon(QIcon("D:/projet/icons8-microsoft-excel-100.png"));
    ui->statisque->setIcon(QIcon("D:/projet/icons8-graph-64.png"));




    ui->consulter_equipement_pb->setIcon(QIcon("D:/projet/icons8-back-to-64 (1).png"));//back
    ui->Ajouter_event_27->setIcon(QIcon("D:/projet/icons8-chatbot-64.png"));//vhatbotn seif
    ui->Ajouter_event_21->setIcon(QIcon("D:/projet/icons8-information-64.png"));//aide seif

    ui->pushButton_4->setIcon(QIcon("D:/projet/icons8-edit-64.png.png"));//modif
    ui->Ajouter_event_24->setIcon(QIcon("D:/projet/icons8-pdf-100 (1).png"));//pdf seif
    ui->Ajouter_event_19->setIcon(QIcon("D:/projet/icons8-graph-64.png"));//stat seif
    ui->Ajouter_event_4->setIcon(QIcon("D:/projet/icons8-add-user-male-64.png"));//add
    ui->statistic->setIcon(QIcon("D:/projet/icons8-graph-64.png"));//stat eq
    ui->pdf_btn->setIcon(QIcon("D:/projet/icons8-pdf-100 (1).png"));//pdf eq
    ui->supprimer_equipement->setIcon(QIcon("D:/projet/icons8-remove-100.png"));//supp eq
    ui->modifier_equipement->setIcon(QIcon("D:/projet/icons8-edit-64.png"));//modifiern eq
    ui->Ajouter_equipement_2->setIcon(QIcon("D:/projet/icons8-add-user-male-64.png"));// ajout equipement
    ui->affichePatient->setIcon(QIcon("D:/projet/icons8-search-account-64 (1).png"));//affiche
    ui->pushButton_2->setIcon(QIcon("D:/projet/icons8-add-user-male-64.png"));//ajout
    ui->pushButton_4->setIcon(QIcon("D:/projet/icons8-edit-64.png"));//modif
    ui->agenda->setIcon(QIcon("D:/projet/icons8-planner-64.png"));//agenda
    ui->l_supp->setIcon(QIcon("D:/projet/icons8-remove-100.png"));//suprimer
    ui->pdf->setIcon(QIcon("D:/projet/icons8-pdf-100 (1).png"));//pdf
    ui->todoo->setIcon(QIcon("D:/projet/icons8-checklist-64.png"));//todo
    ui->stat->setIcon(QIcon("D:/projet/icons8-graph-64.png"));//stat


    QList<QSerialPortInfo> portInfoList = QSerialPortInfo::availablePorts();


    // Loop through each serial port and check if it's an Arduino Uno
    foreach (const QSerialPortInfo& portInfo, portInfoList) {
             if (portInfo.serialNumber() == "55338343639351E040B0") {
                 // The connected device is the Arduino Uno with serial number "12345"
                 qDebug() << portInfo.serialNumber() << portInfo.portName();
                  QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(textTOspeech()));

                  qDebug() << "ccccccccccccccccc " << portInfo.portName();

             } else if (portInfo.serialNumber() == "553303435343FF11F121"){/// fiinger
                 // The connected device is a different Arduino Uno
                  QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(fingerprint()));
                 qDebug() << portInfo.serialNumber() << portInfo.portName();
                 qDebug() << "bbbbbbbbbbbbbbbb " << portInfo.portName();
             }else if (portInfo.serialNumber() == "553303435343FF90A1A0"){ /// lcd
                 // The connected device is a different Arduino Uno
                 qDebug() << portInfo.serialNumber() << portInfo.portName();
                 QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));
                 qDebug() << "aaaaaaaaaaaaaa " << portInfo.portName();
             }
         }


      //Evenements///////////////////////
      //refrech l'affichage
      ui->tableView_events->setModel(Evt.afficher_event());

     //controle de saisir
      ui->lineEditTitre_event->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
      ui->lineEdit_Desc->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
      ui->lineEdit_lieuEvent->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
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


      QSettings settings(QSettings::IniFormat, QSettings::UserScope,QCoreApplication::organizationName(), QCoreApplication::applicationName());
     // ui->axWidget->dynamicCall("Navigate(const QString&)", "file:///D:/projet/integration_ameni-sarah back up + seif/index.html");
                     //Activité///////////////////////////////////
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
ui->calendarWidget->setStyleSheet("background-color :rgb(240,217,255);selection-background-color:rgb(207, 77, 206);");
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
   //Moataaaz
   MainWindow::makePlot();


   connect(ui->mail, SIGNAL(clicked()),this, SLOT(sendMail()));


   QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
   proxyModel->setSourceModel(ui->tableView->model());
   proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
   ui->tableView->setModel(proxyModel);
   connect(ui->tableView->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModel, &QSortFilterProxyModel::sort);
   ui->tableView->setSortingEnabled(true);
   ui->tableView->setColumnWidth(8, 150);
   ui->tableView->setGridStyle(Qt::MPenStyle);

   QSortFilterProxyModel *proxyModelA = new QSortFilterProxyModel(this);
   proxyModelA->setSourceModel(ui->table_act->model());
   proxyModelA->setSortCaseSensitivity(Qt::CaseInsensitive);
   ui->table_act->setModel(proxyModelA);
   connect(ui->table_act->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModelA, &QSortFilterProxyModel::sort);
   ui->table_act->setSortingEnabled(true);
   ui->table_act->setColumnWidth(8, 150);
   ui->table_act->setGridStyle(Qt::MPenStyle);

   QSortFilterProxyModel *proxyModelE = new QSortFilterProxyModel(this);
   proxyModelE->setSourceModel(ui->tableView_events->model());
   proxyModelE->setSortCaseSensitivity(Qt::CaseInsensitive);
   ui->tableView_events->setModel(proxyModelE);
   connect(ui->tableView_events->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModelE, &QSortFilterProxyModel::sort);
   ui->tableView_events->setSortingEnabled(true);
   ui->tableView_events->setColumnWidth(8, 150);
   ui->tableView_events->setGridStyle(Qt::MPenStyle);

   QSortFilterProxyModel *proxyModelEq = new QSortFilterProxyModel(this);
   proxyModelEq->setSourceModel(ui->table_equip->model());
   proxyModelEq->setSortCaseSensitivity(Qt::CaseInsensitive);
   ui->table_equip->setModel(proxyModelEq);
   connect(ui->table_equip->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModelEq, &QSortFilterProxyModel::sort);
   ui->table_equip->setSortingEnabled(true);
   ui->table_equip->setColumnWidth(8, 150);
   ui->table_equip->setGridStyle(Qt::MPenStyle);

   ui->num_patient->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
   ui->num_urg->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
   ui->nom_patient->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
   ui->prenom_patient->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z- ]{15}")));
   ui->adress->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$")));




   ui-> tableView->setFocusPolicy(Qt::NoFocus);
   ui-> tableView->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->tableView->verticalHeader()->setVisible(false);
   ui->tableView->horizontalHeader()->setVisible(true);
   ui-> tableView->setShowGrid(false);
   ui->tableView->setObjectName("tableView");
   ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
   ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->tableView->horizontalHeader()->setStretchLastSection(true);

   ui-> table_equip->setFocusPolicy(Qt::NoFocus);
   ui-> table_equip->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->table_equip->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->table_equip->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->table_equip->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->table_equip->verticalHeader()->setVisible(false);
   ui->table_equip->horizontalHeader()->setVisible(true);
   ui-> table_equip->setShowGrid(false);
   ui->table_equip->setObjectName("table_equip");
   ui->table_equip->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
   ui->table_equip->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->table_equip->horizontalHeader()->setStretchLastSection(true);

   QSortFilterProxyModel *proxyModelI = new QSortFilterProxyModel(this);
   proxyModelI->setSourceModel(ui->tableView_2->model());
   proxyModelI->setSortCaseSensitivity(Qt::CaseInsensitive);
   ui->tableView_2->setModel(proxyModelI);
   connect(ui->tableView_2->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModelI, &QSortFilterProxyModel::sort);
   ui->tableView_2->setSortingEnabled(true);
   ui->tableView_2->setColumnWidth(8, 150);
   ui->tableView_2->setGridStyle(Qt::MPenStyle);

   ui->stackedWidget->setCurrentIndex(2);
   setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);



   // Create a new instance of the Sidebar widget
   sidebar = new Sidebar(ui->frame);


connect(ui->sidebarButton, &QPushButton::clicked, sidebar, &Sidebar::toggleSidebar);



QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
shadow->setBlurRadius(5);
shadow->setXOffset(2);
shadow->setYOffset(2);
shadow->setColor(QColor(0, 0, 0, 128));
ui->frame->setGraphicsEffect(shadow);
ui->Ajouter_event_2->setGraphicsEffect(shadow);


ui->frame->show();
////////////////////////////////////////////////////////////////////////////////////////////////
QGraphicsScene *scene = new QGraphicsScene;
QGraphicsView *view = new QGraphicsView(scene, ui->label_GIF);// add ui->groupBox as parent widget
view->setFixedSize(ui->label_GIF->size()); // set the size of the QGraphicsView to match the size of the QGroupBox
view->setStyleSheet("background-color: transparent");
view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
view->setInteractive(false);
view->setMouseTracking(true); // enable mouse tracking for the QGraphicsView
QGraphicsProxyWidget *groupBoxProxy = scene->addWidget(ui->label_GIF); // add ui->groupBox as a widget to the scene
groupBoxProxy->setPos(ui->label_GIF->pos()); // set the position of the proxy widget to match ui->groupBox
groupBoxProxy->setFlag(QGraphicsItem::ItemIsSelectable, false); // disable selection for the proxy widget

QPixmap background("D:/projet/mainwindow.jpg");
QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(background);
bgItem->setOpacity(0.5); // Set the opacity to 0.5
bgItem->setGraphicsEffect(new QGraphicsBlurEffect()); // Add a blur effect
scene->addItem(bgItem);
scene->setSceneRect(view->rect());
qDebug() <<ui->groupBox_9->pos();



QGraphicsView *view1 = new QGraphicsView(scene, ui->label_GIF_2);// add ui->groupBox as parent widget
view1->setFixedSize(ui->label_GIF_2->size()); // set the size of the QGraphicsView to match the size of the QGroupBox
view1->setStyleSheet("background-color: transparent");
view1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
view1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
view1->setInteractive(false);
view1->setMouseTracking(true); // enable mouse tracking for the QGraphicsView
QGraphicsProxyWidget *groupBoxProxy1 = scene->addWidget(ui->label_GIF_2); // add ui->groupBox as a widget to the scene
groupBoxProxy1->setPos(ui->label_GIF_2->pos()); // set the position of the proxy widget to match ui->groupBox
groupBoxProxy1->setFlag(QGraphicsItem::ItemIsSelectable, false); // disable selection for the proxy widget


bgItem->setOpacity(0.5); // Set the opacity to 0.5
bgItem->setGraphicsEffect(new QGraphicsBlurEffect()); // Add a blur effect
scene->addItem(bgItem);
scene->setSceneRect(view1->rect());


    QGraphicsView *view2 = new QGraphicsView(scene, ui->label_GIF_3);// add ui->groupBox as parent widget
view2->setFixedSize(ui->label_GIF_3->size()); // set the size of the QGraphicsView to match the size of the QGroupBox
view2->setStyleSheet("background-color: transparent");
view2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
view2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
view2->setInteractive(false);
view2->setMouseTracking(true); // enable mouse tracking for the QGraphicsView
QGraphicsProxyWidget *groupBoxProxy2 = scene->addWidget(ui->label_GIF_3); // add ui->groupBox as a widget to the scene
groupBoxProxy2->setPos(ui->label_GIF_2->pos()); // set the position of the proxy widget to match ui->groupBox
groupBoxProxy2->setFlag(QGraphicsItem::ItemIsSelectable, false); // disable selection for the proxy widget


bgItem->setOpacity(0.5); // Set the opacity to 0.5
bgItem->setGraphicsEffect(new QGraphicsBlurEffect()); // Add a blur effect
scene->addItem(bgItem);
scene->setSceneRect(view1->rect());


QStringList headers1 = { "IDPATIENT", "NOM", "PRENOM", "DOB", "NUMPERSO","NUMURGENCE", "ETAT", "PDR", "PHOTO" };
QList<QStringList> data1 = { headers1, { "1", "John", "Doe", "1990-01-01", "123", "456", "OK", "N/A", "photo.jpg" } };
populateModel(ui->tableView, headers1, data1);


QStringList headers2 = { "ID", "Name", "Age" };
QList<QStringList> data2 = { headers2, { "1", "Alice", "25" }, { "2", "Bob", "30" }, { "3", "Charlie", "40" } };
populateModel(ui->table_equip, headers2, data2);

QStringList headers3 = { "ID", "Name", "Age" };
QList<QStringList> data3 = { headers2, { "1", "Alice", "25" }, { "2", "Bob", "30" }, { "3", "Charlie", "40" } };
populateModel(ui->tableView_2, headers2, data2);

QStringList headers4 = { "ID", "Name", "Age" };
QList<QStringList> data4 = { headers2, { "1", "Alice", "25" }, { "2", "Bob", "30" }, { "3", "Charlie", "40" } };
populateModel(ui->tableView_events, headers2, data2);

QStringList headers5 = { "ID", "Name", "Age" };
QList<QStringList> data5 = { headers2, { "1", "Alice", "25" }, { "2", "Bob", "30" }, { "3", "Charlie", "40" } };
populateModel(ui->table_act, headers2, data2);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::fingerprint()
{
    qDebug() << "update label";
    QByteArray data = A.read_from_arduino();
    QString id = QString::fromUtf8(data).trimmed().simplified();
    id = id.remove(QRegExp("[^\\d]")); // remove all non-numeric characters
    int id_num = id.toInt(); // convert the resulting string to an integer
    qDebug() << "ID de l'empreinte digitale:" << id_num;

    QSqlQuery query2;
    query2.prepare("SELECT IDPATIENT FROM PATIENTS WHERE IDPATIENT =:id_num");
    query2.bindValue(":id_num", id_num);
    query2.exec();

    if (query2.next()) {
                             QString titreEvent = query2.value("IDPATIENT").toString();
                             QByteArray data2 = titreEvent.toUtf8();
                             A.write_to_arduino(data2);
                             qDebug() << "Ihoha" << data2;
    }

}
//Arduino//////////////////////////////////////////////////////////
void MainWindow::update_label()
{   qDebug() << "data";
    QString data = A.read_from_arduino().trimmed();
    qDebug() << data;
    QSqlQuery query2;
    query2.prepare("SELECT NOM FROM ACTIVITES WHERE IDACTIVITE =:data");
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



void MainWindow::textTOspeech()
{
    QString data = A.read_from_arduino().trimmed();
    qDebug() << "data";
     qDebug() << data;
    QSqlQuery query;
    if (data == 'A')
    {
        query.prepare("SELECT ONE FROM ARDUINO WHERE ID=:id");
        query.bindValue(":id", 1);
        query.exec();
        while (query.next())
        {
            ui->label_49->setText(query.value("ONE").toString());
        }
    }
    else if (data == 1)
    {
        query.prepare("SELECT TWO FROM ARDUINO WHERE ID=:id");
        query.bindValue(":id", 1);
        query.exec();
        qDebug() << query.value("TWO");
    }
    else if (data == 2)
    {
        query.prepare("SELECT THREE FROM ARDUINO WHERE ID=:id");
        query.bindValue(":id", 1);
        query.exec();
        qDebug() << query.value("THREE");
    }
    else if (data == 3)
    {
        query.prepare("SELECT FOUR FROM ARDUINO WHERE ID=:id");
        query.bindValue(":id", 1);
        query.exec();
        qDebug() << query.value("FOUR");
    }
    else if (data == 'B')
    {
        query.prepare("SELECT SIX FROM ARDUINO WHERE ID=:id");
        query.bindValue(":id", 1);
        query.exec();
        qDebug() << query.value("SIX");
    }

}
//Menu

void MainWindow::on_Equipements_clicked()
{
    Notification n ;
    n.notification_ajoutEquipement();
    ui->stackedWidget_in->setCurrentIndex(4);
}
void MainWindow::on_Activites_clicked()
{
   ui->stackedWidget_in->setCurrentIndex(12);

}
void MainWindow::on_Intervenants_clicked()
{
   QSortFilterProxyModel *proxyModelI = new QSortFilterProxyModel(this);
   proxyModelI->setSourceModel(ui->tableView_2->model());
   proxyModelI->setSortCaseSensitivity(Qt::CaseInsensitive);
   ui->tableView_2->setModel(proxyModelI);
   connect(ui->tableView_2->horizontalHeader(), &QHeaderView::sortIndicatorChanged,proxyModelI, &QSortFilterProxyModel::sort);
   ui->tableView_2->setSortingEnabled(true);
   ui->tableView_2->setModel(I.afficher());
    ui->stackedWidget_in->setCurrentIndex(27);
}



void MainWindow::on_Patients_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(20);
}
//Equipements//////////////////////////

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
  Notification n ;
  n.notification_ajoutEquipement();
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
}


void MainWindow::on_pdf_btn_clicked()
{
    QPdfWriter pdf("D:/projet/integration_ameni-sarah back up + seif/pdf/ameni.pdf");
       QPainter painter(&pdf);
      int i = 4000;
           painter.setPen(Qt::red);
           painter.setFont(QFont("Comic Sans MS", 30));
           painter.drawText(1100,1100,"Liste Des Equipemets ");
           painter.setFont(QFont("Comic Sans MS", 50));
           painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("D:/projet/integration_ameni-sarah back up + seif/LOGO.png"));
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


//qr code
void MainWindow::on_table_equip_activated(const QModelIndex &index)
{
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
    ui->stackedWidget_in->setCurrentIndex(26);

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
    QSqlQuery query;
    query.prepare("SELECT NOM from PATIENTS");
    query.exec();
    QSqlQueryModel * modal = new QSqlQueryModel();
    modal->setQuery(query);
    ui->selectPat->setModel(modal);

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

void MainWindow::on_le_chercher_textChanged(const QString &arg1)
{
    ui->table_act->setModel(Act.recherche_NOM(arg1));

}

void MainWindow::done2()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    QSqlQuery query,querypat;

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

    query.prepare(" SELECT PDR from Patients where NOM='"+ui->selectPat->currentText()+"'");
    query.next();
    int pdr = query.value(0).toInt();
    pdr = qrand() % ((23) - 10) + 10;
    query.prepare(" UPDATE PATIENTS SET PDR=:pdr WHERE NOM='"+ui->selectPat->currentText()+"'");
    query.bindValue(":pdr",pdr);
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

  QSqlQuery query;
  query.prepare("SELECT NOM from EQUIPEMENTS");
  query.exec();
  QSqlQueryModel * modal = new QSqlQueryModel();
  modal->setQuery(query);
  ui->selectequipe->setModel(modal);
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
        QSqlQuery query1,query2;
        query1.prepare(" SELECT IDEQUIPEMENT from EQUIPEMENTS where NOM='"+ui->selectequipe->currentText()+"'");
        query1.exec();
        while (query1.next())
        {
            int IDEQ = query1.value("IDEQUIPEMENT").toInt();
            query2.prepare(" INSERT INTO HISTORIQUEEQUIPEMENTS (IDEQUIPEMENT,DATEUTILISATION) VALUES (:id,:date)");
            query2.bindValue(":id",IDEQ);
            query2.bindValue(":date",ui->dateTimeEdit_event->dateTime());
            query2.exec();
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

//moataaaaz
void MainWindow::populateModel(QTableView *tableView, const QStringList &headers, const QList<QStringList> &data) {
             QStandardItemModel *model = qobject_cast<QStandardItemModel *>(tableView->model());
             if (!model)
        return;

             int j = 0;
             for (const QStringList &row : data) {
        model->insertRow(j);
        j++;
        int i = 0;
        for (const QString &x : row) {
            QModelIndex index = model->index(j - 1, i);
            model->setData(index, x);
            model->setData(index, QColor(255, 255, 255), Qt::ForegroundRole);
            model->setData(index, tableView->font(), Qt::FontRole);

            if (j == 1 && i <= 4) {
                                    model->insertColumn(i, QModelIndex());
                                    model->setData(model->index(0, i, QModelIndex()), Qt::AlignCenter, Qt::TextAlignmentRole);
            }

            i++;
        }
             }
}


void MainWindow::on_Ajouter_patient_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(1);
}





void MainWindow::on_patients_clicked()
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
            QString mailpat=ui->adress->text();
           qDebug() <<mailpat ;
Patient p(nom_patient, prenom_patient, DOB, num_patient, num_urg, etat_patient, imageData,mailpat);

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

        ui->stackedWidget_in->setCurrentIndex(20);
        ImageTableModel *imageModel = new ImageTableModel(this);
        imageModel->setTable("PATIENTS");
        imageModel->select();
        ui->tableView->setModel(imageModel);

        CenteredTextDelegate* centeredTextDelegate = new CenteredTextDelegate(ui->tableView);

        // Set the delegate on the table view for the desired column (e.g., column 0)
//        ui->tableView->setItemDelegateForColumn(0, centeredTextDelegate);
//        ui->tableView->setItemDelegateForColumn(1, centeredTextDelegate);
//        ui->tableView->setItemDelegateForColumn(2, centeredTextDelegate);
//        ui->tableView->setItemDelegateForColumn(3, centeredTextDelegate);
//        ui->tableView->setItemDelegateForColumn(4, centeredTextDelegate);
//        ui->tableView->setItemDelegateForColumn(5, centeredTextDelegate);
//        ui->tableView->setItemDelegateForColumn(6, centeredTextDelegate);
//        ui->tableView->setItemDelegateForColumn(7, centeredTextDelegate);
       // ui->tableView->setItemDelegateForColumn(8, centeredTextDelegate);


}




void MainWindow::on_modifierPatient_2_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(24);
}

void MainWindow::on_statisque_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(22);
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
    QString  mailpat=ui->mailpatmodif->text();

Patient p(nom_patient, prenom_patient, DOB, num_patient, num_urg, etat_patient, imageData,mailpat);

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
    query.bindValue(":id",ui->nom_patient_4->text());
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
    query.exec("SELECT COUNT(IDPATIENT) FROM PATIENTS WHERE ETAT='Adult' ");
    query.next();
    int res = query.value(0).toInt();
    query.exec("SELECT COUNT(IDPATIENT) FROM PATIENTS WHERE ETAT='Enfant' ");
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
        QSqlQuery query;
        query.prepare("SELECT * FROM PATIENTS where IDPATIENT =:id");
        query.bindValue(":id",ui->nom_patient_4->text());
        query.exec();
        query.next();
        QString mail=query.value("MAIL").toString();
        qDebug() << mail << "this is my mailllllllllllll" ;

    Smtp* smtp = new Smtp("gmootaz3@gmail.com", "dieitpkjiqrcnwmm", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("HYPERFLOW",mail, "doctor meeting","you have a meeting with your doctor tomorow dont forget");
}


void MainWindow::on_expoterdb_clicked()
{
    QFile data("outputs/output.csv");
    if (data.open(QFile::WriteOnly))
    {
            QTextStream outTxt(&data);
            QSqlQuery query;
            query.prepare("SELECT * FROM PATIENTS");
            if(query.exec()){
                // Get the record and output the headers
                const QSqlRecord recrd = query.record();
                for(int i = 0; i < recrd.count(); ++i) {
                outTxt << recrd.fieldName(i);
                if (i < recrd.count() - 1) {
                    outTxt << " | ";
                }
                }
                outTxt << "\n";

                // Output the data rows
                while (query.next()) {
                for(int i = 0; i < recrd.count(); ++i) {
                    outTxt << query.value(i).toString();
                    if (i < recrd.count() - 1) {
                        outTxt << " | ";
                    }
                }
                outTxt << "\n";
                }
            }

            // Close the file and seek the file position to the beginning
            data.close();
            data.open(QIODevice::ReadOnly);
            data.seek(0);

            QTextDocument doc;
            // Create a QTextStream object to read the file
            QTextStream in(&data);

            // Read the CSV data into a string
            QString csvData = in.readAll();

            // Set the CSV data to the QTextDocument object
            doc.setHtml("<pre>" + csvData + "</pre>");

            data.close();

            QPrinter printer(QPrinter::HighResolution);

            // Set the output file name and format
            printer.setOutputFileName("outputs/output.pdf");
            printer.setOutputFormat(QPrinter::PdfFormat);

            // Print the QTextDocument to the QPrinter
            doc.print(&printer);
    }
}


void MainWindow::on_exportxl_clicked()
{
    // Create a QSqlQuery object and execute the query
    QSqlQuery query;
    query.prepare("SELECT * FROM PATIENTS");
    if(query.exec())
    {
            // Create a QXlsx::Document object and add a worksheet
            QXlsx::Document xlsx;
            xlsx.addSheet("Patients");

            // Get the record and output the headers
            const QSqlRecord recrd = query.record();
            for(int i = 0; i < recrd.count(); ++i) {
                xlsx.write(1, i + 1, recrd.fieldName(i));
            }

            // Output the data rows
            int row = 2;
            while (query.next()) {
                for(int i = 0; i < recrd.count(); ++i) {
                xlsx.write(row, i + 1, query.value(i).toString());
                }
                row++;
            }

            // Save the Excel file
            xlsx.saveAs("outputs/output.xlsx");
    }
}


void MainWindow::on_deletall_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
            bool test=pat.supprimer_patients();
            if(test)
            {
                QMessageBox::information(nullptr, QObject::tr("ok"),
                                         QObject::tr("suppression effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
                ImageTableModel *imageModel = new ImageTableModel(this);
                imageModel->setTable("PATIENTS");
                imageModel->select();
                ui->tableView->setModel(imageModel);

                CenteredTextDelegate* centeredTextDelegate = new CenteredTextDelegate(ui->tableView);

                // Set the delegate on the table view for the desired column (e.g., column 0)
//                ui->tableView->setItemDelegateForColumn(0, centeredTextDelegate);
//                ui->tableView->setItemDelegateForColumn(1, centeredTextDelegate);
//                ui->tableView->setItemDelegateForColumn(2, centeredTextDelegate);
//                ui->tableView->setItemDelegateForColumn(3, centeredTextDelegate);
//                ui->tableView->setItemDelegateForColumn(4, centeredTextDelegate);
//                ui->tableView->setItemDelegateForColumn(5, centeredTextDelegate);
//                ui->tableView->setItemDelegateForColumn(6, centeredTextDelegate);
//                ui->tableView->setItemDelegateForColumn(7, centeredTextDelegate);
                // ui->tableView->setItemDelegateForColumn(8, centeredTextDelegate);
            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("not ok"),
                                         QObject::tr("suppression non effectue\n" "Click cancel to exite."),QMessageBox::Cancel);
            }
    } else {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("aucun patient n'a été supprimé \n" "Click close to exite."),QMessageBox::Cancel);
    }

}


void MainWindow::on_deletall_2_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    // get the IDs of the selected rows
    QList<int> selectedIds;
    foreach (QModelIndex index, selectedRows) {
            int id = index.sibling(index.row(), 0).data().toInt();
            selectedIds.append(id);
    }

    // delete the selected rows from the database
    foreach (int id, selectedIds) {
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

}

void MainWindow::on_pushButton_5_clicked()
{
QSqlQuery query ;
query.prepare("SELECT TWO FROM ARDUINO WHERE ID=:id");
query.bindValue(":id", 1);
query.exec();
A.write_to_arduino("1");
while (query.next())
{
            ui->label_12->setText("Speaker:"+query.value("TWO").toString());

}
}
void MainWindow::on_pushButton_6_clicked()
{
QSqlQuery query ;
query.prepare("SELECT THREE FROM ARDUINO WHERE ID=:id");
query.bindValue(":id", 1);
query.exec();
A.write_to_arduino("2");
while (query.next())
{
            ui->label_12->setText("Speaker:"+query.value("THREE").toString());

}

}

void MainWindow::on_pushButton_8_clicked()
{
A.write_to_arduino("0");
ui->label_12->setText("Speaker:Resumed");


}

void MainWindow::on_pushButton_9_clicked()
{
QSqlQuery query ;
query.prepare("SELECT FOUR FROM ARDUINO WHERE ID=:id");
query.bindValue(":id", 1);
query.exec();
A.write_to_arduino("3");
while (query.next())
{
            ui->label_12->setText(query.value("FOUR").toString());

}

}




void MainWindow::on_pushButton_10_clicked()
{
QSqlQuery query ;
query.prepare("SELECT ONE FROM ARDUINO WHERE ID=:id");
query.bindValue(":id", 1);
query.exec();
A.write_to_arduino("4");
while (query.next())
{
            ui->label_12->setText("Speaker:"+query.value("ONE").toString());

}
}


void MainWindow::on_pushButton_11_clicked()
{
QSqlQuery query ;
query.prepare("SELECT SIX FROM ARDUINO WHERE ID=:id");
query.bindValue(":id", 1);
query.exec();
A.write_to_arduino("5");
while (query.next())
{
            ui->label_12->setText("Speaker:"+query.value("SIX").toString());

}
}







void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
int row = index.row();
QSqlQuery query1;
QModelIndex idIndex = index.sibling(row,0);
QVariant idVariant = ui->tableView_2->model()->data(idIndex);
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
ui->stackedWidget_in->setCurrentIndex(28);
}


void MainWindow::on_Ajouter_event_17_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(27);
}


void MainWindow::on_Ajouter_event_18_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM INTERVENANTS where IDIntervenant = :id");
    query.bindValue(":id",ui->Titre_40->text());
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
            int id = query.value("IDIntervenant").toInt();
            QString nom = query.value("NOM").toString();
            QString prenom = query.value("PRENOM").toString();
            QString type = query.value("TYPE").toString();
            QString etat = query.value("ETAT").toString();
            float salaire = query.value("SALAIRE").toInt();
            QDateTime DOB = query.value("DOB").toDateTime();
            painter.setFont(font);
            painter.setPen(pen);
            painter.drawText(100, 100 + row * 20, QString("%1 %2 %3 %4 %5 %6 %7").arg(id).arg(nom).arg(prenom).arg(type).arg(etat).arg(QString::number(salaire, 'f', 2)).arg(DOB.toString()));
            row++;
    }
    painter.end();
    QMessageBox::information(this, "Exported", "Data exported to PDF file.");
}


void MainWindow::on_Ajouter_event_14_clicked()
{
    int id=ui->Titre_40->text().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM INTERVENANTS WHERE IDINTERVENANT = :id");
    query.bindValue(":id",id);
    query.exec();
    ui->tableView_2->setModel(I.afficher());
    ui->stackedWidget_in->setCurrentIndex(27);
}


void MainWindow::on_Ajouter_event_13_clicked()
{
    QSqlQuery query1;
    QString idIntervenant;
    idIntervenant = ui->Titre_40->text();
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
                ui->imageLabel_5->setPixmap(pixmap);
            } else {
                qDebug() << "PHOTO field not found in query result set";
            }
    } else {
            qDebug() << "No records found for the query";
    }
    ui->lineEdit_8->setText(query1.value("NOM").toString());
    ui->lineEdit_9->setText(query1.value("PRENOM").toString());
    ui->Titre_44->setText(idIntervenant);
    ui->Titre_43->setText(query1.value("NUM").toString());
    ui->Titre_45->setText(query1.value("SALAIRE").toString());
    ui->dateTimeEdit_event_6->setDateTime(query1.value("DOB").toDateTime());
    for (int i = 0; i < ui->comboBox_10->count(); i++) {
            QString currentItemText = ui->comboBox_10->itemText(i);
            if (currentItemText == query1.value("TYPE")) {
                ui->comboBox_10->setCurrentIndex(i);
                break;
            }
    }
    for (int i = 0; i < ui->comboBox_6->count(); i++) {
            QString currentItemText = ui->comboBox_9->itemText(i);
            if (currentItemText == query1.value("ETAT")) {
                ui->comboBox_9->setCurrentIndex(i);
                break;
            }
    }
    ui->stackedWidget_in->setCurrentIndex(29);
}


void MainWindow::on_Ajouter_event_15_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(28);
}


void MainWindow::on_Ajouter_event_16_clicked()
{
    bool vide1 = false;
    bool errornom = false,errorPrenom=false,errornum=false,errorSalaire=false;
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("^[A-Za-z]+$"), this);
    QRegularExpressionValidator *validatornum = new QRegularExpressionValidator(QRegularExpression("^\\d{8}$"),this);
    ui->lineEdit_8->setValidator(validator);
    ui->lineEdit_9->setValidator(validator);
    ui->Titre_43->setValidator(validatornum);
    QString nom=ui->lineEdit_8->text();
    if (nom == "")
    {
            vide1 = true;
    }
    if (!ui->lineEdit_8->hasAcceptableInput())
    {
            errornom=true;
    }
    QString prenom=ui->lineEdit_9->text();
    if (prenom == "")
    {
            vide1 = true;
    }
    if (!ui->lineEdit_9->hasAcceptableInput())
    {
            errorPrenom = true;
    }
    QString numtest=ui->Titre_43->text();
    if (numtest=="")
    {
            vide1 = true;
    }
    int num=ui->Titre_43->text().toInt();
    if (!ui->Titre_43->hasAcceptableInput())
    {
            errornum = true;
    }
    QString Salaire=ui->Titre_45->text();
    // if (Salaire == "")
    //{
    //  vide1 = true;
    //}
    if (!ui->Titre_45->hasAcceptableInput())
    {
            errorSalaire = true;
    }
    float Sal = Salaire.toFloat();
    QString type;
    if(ui->comboBox_10->currentIndex() != -1) {
            type = ui->comboBox_10->currentText();
    }
    else
    {
            vide1 = true;
    }
    QString etat;
    if(ui->comboBox_9->currentIndex() != -1) {
            etat = ui->comboBox_9->currentText();
    }
    else
    {
            vide1 = true;
    }
    QDateTime DOB=ui->dateTimeEdit_event_6->dateTime();
    if (imageIntervenantTable.isNull()==false)
    {
            if ((vide1 == false)&&(errorSalaire == false)&&(errornum == false)&&(errornom == false)&&(errorPrenom == false))
            {
                QByteArray imageData;
                QBuffer buffer(&imageData);
                buffer.open(QIODevice::WriteOnly);
                imageIntervenantTable.save(&buffer, "JPG");
                buffer.close();
                INTERVENANTS I1(ui->Titre_44->text().toInt(),nom, prenom,num,Sal,type,etat,DOB,imageData);
                bool test = I1.ModifierIntervenant();
                if(test)
                {
                ui->tableView_2->setModel(I.afficher());
                QMessageBox::information(nullptr, QObject::tr("ok"),
                                         QObject::tr("Modified Successfull\n"),QMessageBox::Cancel);
                QSqlQuery query1;
                QString idIntervenant;
                idIntervenant = ui->Titre_40->text();
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
                                         QObject::tr("Error : Last Name not Valid\n" "Click cancel to exit."),QMessageBox::Cancel);

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
                INTERVENANTS I1(ui->Titre_44->text().toInt(),nom, prenom,num,Sal,type,etat,DOB);
                bool test = I1.ModifierIntervenant1();
                if(test)
                {
                ui->tableView_2->setModel(I.afficher());
                QMessageBox::information(nullptr, QObject::tr("ok"),
                                         QObject::tr("Modified Successfull\n"),QMessageBox::Cancel);
                QSqlQuery query1;
                QString idIntervenant;
                idIntervenant = ui->Titre_40->text();
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


void MainWindow::on_Ajouter_event_19_clicked()
{
    QLayoutItem* item;
    while ((item = ui->gridLayout_6->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
    }
    while ((item = ui->gridLayout_5->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
    }
    QSqlQuery queryType;
    queryType.prepare("SELECT type, COUNT(*) CNT FROM INTERVENANTS GROUP BY TYPE");
    queryType.exec();
    if (!queryType.exec()) {
            qDebug() << "Query failed:" << queryType.lastError().text();
    } else {
            QPieSeries *seriesType = new QPieSeries();
            while (queryType.next()) {
                QString type = queryType.value(0).toString();
                int countType = queryType.value("CNT").toInt();
                seriesType->append(type, countType);
            }
            if (seriesType->count() > 0) {
                seriesType->setLabelsVisible();
                QBrush brush1(QColor("#336699"));
                seriesType->slices().at(0)->setBrush(brush1);
                if (seriesType->count() > 1) {
                QBrush brush2(QColor("#993366"));
                seriesType->slices().at(1)->setBrush(brush2);
                }
                if (seriesType->count() > 2) {
                QBrush brush3(QColor("#FF9900"));
                seriesType->slices().at(2)->setBrush(brush3);
                }
            }
            QChart *chartType = new QChart();
            chartType->addSeries(seriesType);
            chartType->setTitle("Type of Intervenants");
            QChartView *chartViewType = new QChartView(chartType);
            chartViewType->setRenderHint(QPainter::Antialiasing);
            ui->gridLayout_5->addWidget(chartViewType);

            QSqlQuery queryEtat;
            queryEtat.prepare("SELECT ETAT, COUNT(*) CNT FROM INTERVENANTS GROUP BY ETAT");
            queryEtat.exec();
            if (!queryEtat.exec()) {
                qDebug() << "Query failed:" << queryEtat.lastError().text();
            } else {
                QPieSeries *seriesEtat = new QPieSeries();
                while (queryEtat.next()) {
                QString etat = queryEtat.value(0).toString();
                int countEtat = queryEtat.value("CNT").toInt();
                seriesEtat->append(etat, countEtat);
                }
                QBrush brush4(QColor("#336699"));
                seriesEtat->slices().at(0)->setBrush(brush4);
                QBrush brush5(QColor("#993366"));
                seriesEtat->slices().at(1)->setBrush(brush5);
                QChart *chartEtat = new QChart();
                chartEtat->addSeries(seriesEtat);
                chartEtat->setTitle("Etat of Intervenants");
                QChartView *chartViewEtat = new QChartView(chartEtat);
                chartViewEtat->setRenderHint(QPainter::Antialiasing);
                chartViewType->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                chartViewEtat->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                ui->gridLayout_6->addWidget(chartViewEtat);
                ui->stackedWidget_in->setCurrentIndex(30);
            }
    }

}


void MainWindow::on_Ajouter_event_23_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(27);
}


void MainWindow::on_Ajouter_event_21_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(31);
}


void MainWindow::on_Ajouter_event_29_clicked()
{
    srand(time(NULL));
    QString userInput = ui->userInput_2->text();
    QString Response;
    if ((userInput.contains("aaslema"))||(userInput.contains("Aaslema"))||(userInput.contains("Hello"))||(userInput.contains("Hey"))||(userInput.contains("hey"))||(userInput.contains("hello"))||(userInput.contains("Bonjour")))
    {
            int randomNum = rand() % 3 + 1;
            if (randomNum == 1)
            {
                Response = "Hello, How can I help you today ? ";
            }
            else if (randomNum == 2)
            {
                Response = "Aaslema ! Is there something i can help you with ?";
            }
            else
            {
                Response = "Hey, I hope that everything is going well. What can i help you with today ?";
            }
    }
    else if ((userInput.contains("panic"))||(userInput.contains("attack"))||(userInput.contains("Panic Attack"))||(userInput.contains("panic attack"))||(userInput.contains("Panic"))||(userInput.contains("Attack")))
    {
            int randomNum = rand() % 4 + 1;
            if (randomNum == 1)
            {
                Response = "It may help to focus on a calming image or object, such as a favorite photo or a piece of jewelry, to distract The patient from the panic attack.";
            }
            else if (randomNum == 2)
            {
                Response = "If you're in a public place when a panic attack hits, try to find a quiet and private spot where they can take deep breaths and calm down.";
            }
            else if (randomNum == 3)
            {
                Response = "Avoiding triggers, such as certain foods or stressful situations, can help prevent panic attacks.";
            }
            else
            {
                Response = "Practicing regular exercise and relaxation techniques, such as yoga or meditation, can help reduce the frequency and intensity of panic attacks.";
            }

    }
    else if ((userInput.contains("activity"))||(userInput.contains("activities"))||(userInput.contains("Activity"))||(userInput.contains("Activities"))||(userInput.contains("idea"))||(userInput.contains("ideas"))||(userInput.contains("Idea"))||(userInput.contains("Ideas")))
    {
            int randomNum = rand() % 4 + 1;
            if (randomNum == 1)
            {
                Response = "Mindfulness exercises: Practicing mindfulness can help patients with ADHD improve their focus and reduce feelings of anxiety or stress. This can include activities such as deep breathing, body scans, or guided meditations.";
            }
            else if (randomNum == 2)
            {
                Response = "Organizational tasks: Many people with ADHD struggle with organization and time management, so practicing tasks such as making to-do lists, organizing workspaces, or using a planner can be helpful.";
            }
            else if (randomNum == 3)
            {
                Response = "Cognitive behavioral therapy: Cognitive behavioral therapy (CBT) is a form of therapy that can help people with ADHD improve their self-esteem, develop coping skills, and manage their emotions.";
            }
            else
            {
                Response = "Cognitive behavioral therapy: Cognitive behavioral therapy (CBT) is a form of therapy that can help people with ADHD improve their self-esteem, develop coping skills, and manage their emotions.";
            }
    }
    else if ((userInput.contains("medication"))||(userInput.contains("medicaments"))||(userInput.contains("Medicaments"))||(userInput.contains("treatments"))||(userInput.contains("traitements")))
    {
            int randomNum = rand() % 4 + 1;
            if (randomNum == 1)
            {
                Response = "Lisdexamfetamine (Vyvanse): A stimulant medication that is taken orally once a day and may have a longer duration of action than some other stimulant medications.";
            }
            else if (randomNum == 2)
            {
                Response = "Dexmethylphenidate (Focalin): A stimulant medication that is available in both short-acting and extended-release formulations.";
            }
            else if (randomNum == 3)
            {
                Response = "Bupropion (Wellbutrin): An antidepressant medication that is sometimes used off-label to treat ADHD symptoms.";
            }
            else
            {
                Response = "Modafinil (Provigil): A medication that is approved to treat sleep disorders, but may also be used off-label to improve focus and attention in patients with ADHD.";
            }
    }
    else
    {
            int randomNum = rand() % 3 + 1;
            if (randomNum == 1)
            {
                Response = "I am sorry I didn't understand you";
            }
            else if (randomNum == 2)
            {
                Response = "Can you please repeat your question ?";
            }
            else
            {
                Response = "I am not able to help you with that...";
            }
    }
    ui->chatDisplay_2->append("User: " + userInput);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        ui->chatDisplay_2->append("Chatbot: " + Response);
        timer->stop();
    });
    timer->start(1000);
    ui->userInput_2->clear();
}


void MainWindow::on_Profil_clicked()
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
    ui->stackedWidget_in->setCurrentIndex(32);
}


void MainWindow::on_Ajouter_event_9_clicked()
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
                ui->imageLabel_6->setPixmap(pixmap);
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
    ui->stackedWidget_in->setCurrentIndex(33);
}


void MainWindow::on_Ajouter_event_12_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(33);
}


void MainWindow::on_Ajouter_event_11_clicked()
{
    bool vide1 = false;
    bool errornom = false,errorPrenom=false,errornum=false,errorSalaire=false;
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("^[A-Za-z]+$"), this);
    QRegularExpressionValidator *validatornum = new QRegularExpressionValidator(QRegularExpression("^\\d{8}$"),this);
    ui->lineEdit_3->setValidator(validator);
    ui->lineEdit_4->setValidator(validator);
    ui->Titre_38->setValidator(validatornum);
    QString nom=ui->lineEdit_4->text();
    if (nom == "")
    {
            vide1 = true;
    }
    if (!ui->lineEdit_4->hasAcceptableInput())
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
                                         QObject::tr("Error : Last Name not Valid\n" "Click cancel to exit."),QMessageBox::Cancel);

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


void MainWindow::on_Ajouter_event_30_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(34);

}


void MainWindow::on_Exit_clicked()
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


void MainWindow::on_Settings_clicked()
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
    ui->stackedWidget_in->setCurrentIndex(32);
}


void MainWindow::on_Ajouter_event_2_clicked()
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
                   ui->stackedWidget_in->setCurrentIndex(26);
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


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_Ajouter_event_3_clicked()
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


void MainWindow::on_Ajouter_event_4_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(35);

}


void MainWindow::on_Ajouter_event_6_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(27);
}


void MainWindow::on_Ajouter_event_5_clicked()
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
                ui->stackedWidget_in->setCurrentIndex(27);
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


void MainWindow::on_uploade_fichier_2_clicked()
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


void MainWindow::on_Ajouter_event_24_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM INTERVENANTS");
    query.exec();
    QString fileName2 = QFileDialog::getSaveFileName(this, "Save PDF File", "", "*.pdf");
    if (fileName2.isEmpty()) {
                return;
    }
    QPdfWriter writer(fileName2);
    writer.setResolution(2400);
    QTextDocument textDocument;
    QPainter painter(&writer);
    QFont font("Arial", 12);
    QPen pen(Qt::black, 1);
    int row = 0;
    QString html;
    while (query.next()) {
                int id = query.value("IDIntervenant").toInt();
                QString nom = query.value("NOM").toString();
                QString prenom = query.value("PRENOM").toString();
                QString type = query.value("TYPE").toString();
                QString etat = query.value("ETAT").toString();
                float salaire = query.value("SALAIRE").toInt();
                QDateTime DOB = query.value("DOB").toDateTime();
                painter.setFont(font);
                painter.setPen(pen);
                painter.drawText(100, 100 + row * 1000, QString("%1 %2 %3 %4 %5 %6 %7").arg(id).arg(nom).arg(prenom).arg(type).arg(etat).arg(QString::number(salaire, 'f', 2)).arg(DOB.toString()));
                row++;
    }
    painter.end();
    QMessageBox::information(this, "Exported", "Data exported to PDF file.");
}


void MainWindow::on_Ajouter_event_28_clicked()
{
    ui->stackedWidget_in->setCurrentIndex(27);
}


void MainWindow::on_pushButton_7_clicked()
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
                ui->imageLabel_6->setPixmap(pixmap);
                }
    }
}


void MainWindow::on_expoterdb_2_clicked()
{
        ui->stackedWidget_in->setCurrentIndex(21);
}


void MainWindow::on_Ajouter_event_27_clicked()
{
        ui->stackedWidget_in->setCurrentIndex(25);
}


void MainWindow::on_Ajouter_event_31_clicked()
{
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Audio and Video Files (*.mp3 *.mp4)"));

        if (!fileName.isEmpty()) {
                QFileInfo fileInfo(fileName);
                QString ext = fileInfo.suffix().toLower();

                if (ext == "mp4") {
                // Create a video widget
                QVideoWidget *videoWidget = new QVideoWidget(this);
                videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                // Create a media player and set the video output to the widget
                QMediaPlayer *player = new QMediaPlayer(this);
                player->setMedia(QUrl::fromLocalFile(fileName));
                player->setVideoOutput(videoWidget);

                // Create a layout manager and add the video widget to it
                QVBoxLayout *layout = new QVBoxLayout();
                layout->addWidget(videoWidget);
                layout->setAlignment(Qt::AlignCenter);

                // Set the layout manager on the central widget of the main window
                ui->widget->setLayout(layout);

                // Play the video
                player->play();
                } else if (ext == "mp3") {
                // Create an audio player
                QMediaPlayer *player = new QMediaPlayer(this);
                player->setMedia(QUrl::fromLocalFile(fileName));

                // Play the audio
                player->play();
                } else {
                // Display an error message for unsupported file types
                QMessageBox::warning(this, tr("Unsupported File Type"), tr("The selected file is not supported."));
                }
        }
}






void MainWindow::on_updat_done_2_clicked()
{

            QSqlQuery query;
        query.prepare("SELECT PDR FROM PATIENTS where IDPATIENT = :id");
        query.bindValue(":id",ui->nom_patient_4->text());
        query.exec();
        while (query.next())
        {
        ui->lcdNumber_2->display(query.value("PDR").toString());
        }
}


void MainWindow::on_quit_clicked()
{

        QSqlQuery query;

        query.prepare("SELECT * FROM SESSIONS");
        if (query.exec() && query.next()) {
        qDebug() << query.value(1);
        closesession(query.value(1).toInt());
        QObject::connect(ui->quit, &QPushButton::clicked, &QCoreApplication::quit);
        ui->quit->show();
        }
        else
        {
        qDebug() << "Error";
        }
}


