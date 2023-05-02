#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDesktopWidget>
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
#include"equipements.h"
#include "historiquec.h"
#include"activite.h"
#include"notification.h"
#include"event.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:




    void on_Ajouter_equipement_clicked();

    void on_validation_ajout_clicked();

    void on_supprimer_equipement_clicked();

    void on_SUPP_clicked();

    void on_modifier_equipement_clicked();

    void on_Equipements_clicked();

    void on_consulter_equipement_pb_clicked();

    void on_consulter_equipement_pb_2_clicked();

    void on_search_btn_clicked();

    void on_tri_btn_clicked();

    void on_tri_btn_2_clicked();

    void on_modifier_equipement_2_clicked();

    void on_consulter_equipement_pb_3_clicked();

    void on_consulter_equipement_pb_4_clicked();

    void on_Ajouter_equipement_2_clicked();

    void on_pdf_btn_clicked();

    void on_statistic_clicked();

    void on_qrcode_clicked();

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

   void on_radioButton_2_clicked();

   void on_radioButtontrier_eventC_2_clicked();

   void on_Settings_2_clicked();

   void on_botton_selsct_event_2_clicked();


   void fingerarduino();
   void testy();

   void on_validation_ajout_event_clicked();

   void on_uploade_fichier_event_clicked();



   void on_uploade_fichier_event_2_clicked();

private:
    Ui::MainWindow *ui;
    activite Act;
    Tache T;
    Event Evt;
    QImage image_event;
   calender_A H;
    Equipements E;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
    //Ajouter un attribut à la classe mainwindow qui correspond à un objet de la classe equipement pour pouvoir faire appel à la méthode supprimer ()
};
#endif // MAINWINDOW_H
