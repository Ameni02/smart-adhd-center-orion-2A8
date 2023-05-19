#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
//#include <QDesktopWidget>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStackedWidget>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtCharts>
#include <QChartView>
#include <QCalendarWidget>
#include <QDate>
#include <QTextCharFormat>
#include <QObject>
#include "arduino.h"
#include "arduino2.h"
#include "chatbot.h"
#include "patient.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>
#include <QMainWindow>
#include "smtp.h"
#include <QBuffer>
#include <QFile>
#include <QPixmap>
#include <QByteArray>
#include "imagetablemodel.h"
#include "arduino.h"
#include"equipements.h"
#include "historiquec.h"
#include"activite.h"
#include"notification.h"
#include"event.h"
#include <QPropertyAnimation>
#include "chatbot.h"
#include "intervenants.h"
#include "sidebar.h"
#include "videowidget.h"
//#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showCentralWidget();

private slots:






    void on_validation_ajout_clicked();

    void on_supprimer_equipement_clicked();

    void on_SUPP_clicked();

    void on_modifier_equipement_clicked();

    void on_Equipements_clicked();

    void on_consulter_equipement_pb_clicked();



    void on_search_btn_clicked();

    void on_tri_btn_clicked();

    void on_tri_btn_2_clicked();

    void on_modifier_equipement_2_clicked();

    void on_consulter_equipement_pb_3_clicked();

    void on_consulter_equipement_pb_4_clicked();

    void on_Ajouter_equipement_2_clicked();

    void on_pdf_btn_clicked();

    void on_statistic_clicked();

    void on_table_equip_activated(const QModelIndex &index);

    void update_label();

    void on_pdf_btn_2_clicked();

    void on_uploade_fichier_clicked();

   void on_pushButton_clicked();

   void on_valider_ajout_clicked();

   void on_pushButton_2_clicked();

   void on_update_clicked();

   void on_pushButton_3_clicked();

   void on_validermodif_clicked();

   void on_pushButton_4_clicked();

   void on_gestion_activite_clicked();

   void on_chercher_clicked();

   void on_stat_clicked();

   void on_croissant_clicked();

   void on_decroissant_clicked();

   void on_pdf_clicked();

   void on_agenda_clicked();

   void on_todoo_clicked();

   void on_calendarWidget_clicked(const QDate &date);

   void on_ajoutDate_clicked();



   void on_le_chercher_textChanged(const QString &arg1);

   void ajouttodo();

   void done();

   void done2();

   void load();

   void inprogress();
   void on_b1_clicked();

   void on_Activites_clicked();

   void on_Intervenants_clicked();

   void on_Events_clicked();

   void on_Patients_clicked();

   void on_l_supp_clicked();

   void on_Ajouter_event_clicked();



   void on_botton_supprimer_clicked();

   void on_botton_update_events_clicked();



   void on_validation_update_events_clicked();



   void on_lineEdit_chercheEvent_textChanged(const QString &arg1);

   void on_events_statistics_clicked();

   void on_details_events_clicked();

   void on_EmissionCO2_clicked();

   void on_pdf_Event_test_clicked();

   void on_Settings_2_clicked();

   void on_botton_selsct_event_2_clicked();


   void fingerarduino();
   void testy();

   void on_validation_ajout_event_clicked();

   void on_uploade_fichier_event_clicked();



   void on_uploade_fichier_event_2_clicked();

//Moatazzzzzzz

  // void on_Ajouter_event_clicked();
   void on_Ajouter_patient_clicked();



  // void on_Events_clicked();
   void on_patients_clicked();


  // void on_Patients_clicked();

   void on_validation_ajout_2_clicked();

   //void on_affichePatient_clicked();




   void on_modifierPatient_2_clicked();
   void on_statisque_clicked();

   void on_updat_done_clicked();
   void on_txtFilter_textChanged(const QString &arg1);
   void on_uploade_photo_clicked();

   void makePlot();
   void on_photo_patient_clicked();
   void sendMail();




   void on_expoterdb_clicked();

   void on_exportxl_clicked();

   void on_deletall_clicked();

   void on_deletall_2_clicked();

   void on_pushButton_5_clicked();
   void on_pushButton_6_clicked();
   //  void on_pushButton_7_clicked();
   void on_pushButton_8_clicked();
   void on_pushButton_9_clicked();

   void on_pushButton_10_clicked();

   void on_pushButton_11_clicked();

   void on_Ajouter_event_17_clicked();

   void on_Ajouter_event_18_clicked();

   void on_Ajouter_event_14_clicked();

   void on_Ajouter_event_13_clicked();

   void on_Ajouter_event_15_clicked();

   void on_Ajouter_event_16_clicked();

   void on_Ajouter_event_19_clicked();

   void on_Ajouter_event_23_clicked();

   void on_Ajouter_event_21_clicked();

   void on_Ajouter_event_29_clicked();

   void on_Profil_clicked();

   void on_Ajouter_event_9_clicked();

   void on_Ajouter_event_12_clicked();

   void on_Ajouter_event_11_clicked();

   void on_Ajouter_event_30_clicked();

   void on_Exit_clicked();

   void on_Settings_clicked();

   void on_Ajouter_event_2_clicked();

   void on_pushButton_12_clicked();

   void on_pushButton_13_clicked();

   void on_Ajouter_event_3_clicked();




   void on_Ajouter_event_4_clicked();

   void on_Ajouter_event_6_clicked();

   void on_Ajouter_event_5_clicked();

   void on_uploade_fichier_2_clicked();

   void on_Ajouter_event_24_clicked();

   void on_Ajouter_event_28_clicked();

   void on_pushButton_7_clicked();

   void fingerprint();
   void on_expoterdb_2_clicked();

   void textTOspeech();
   void on_Ajouter_event_27_clicked();

   void on_tableView_2_activated(const QModelIndex &index);

   void on_Ajouter_event_31_clicked();


   void on_pdf_2_clicked();

   void on_updat_done_2_clicked();

   void on_quit_clicked();

   // void on_toggleSidebar_clicked();

   void populateModel(QTableView *tableView, const QStringList &headers, const QList<QStringList> &data);

  // void runFaceRecognition();
   void on_consulter_equipement_pb_7_clicked();

   void on_consulter_equipement_pb_14_clicked();

   void on_consulter_equipement_pb_22_clicked();

   void on_consulter_equipement_pb_15_clicked();

   void on_consulter_equipement_pb_16_clicked();

   void updateClock();
   private:
   QStackedWidget *stackedWidget;
   VideoWidget *videoWidget;
    QTimer *timer;
   QLabel *m_logo;
   QPropertyAnimation *m_animation;
   QMediaPlayer *m_player;
    Ui::MainWindow *ui;
    Sidebar *sidebar;
    QPropertyAnimation *animation;
    activite Act;
    Patient pat;
    QImage imagePatient,imagePatientTable;
    QByteArray photoPatient;
    Tache T;
    Event Evt;
    QImage image_event;
   calender_A H;
    Equipements E;
    QByteArray data; // variable contenant les données reçues
    INTERVENANTS I;
    QImage imageIntervenant,imageIntervenantTable;
     // variable contenant les données reçues
    Arduino A;
    arduino2 A2;// objet temporaire
    ChatBot C; // objet temporaire
    //Ajouter un attribut à la classe mainwindow qui correspond à un objet de la classe equipement pour pouvoir faire appel à la méthode supprimer ()
};
#endif // MAINWINDOW_H
