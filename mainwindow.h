#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
#include <QMainWindow>
#include <QStackedWidget>
#include <QMainWindow>
#include"activite.h"
#include <QMainWindow>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtCharts>
#include <QChartView>
#include <QCalendarWidget>
#include <QDate>
#include <QTextCharFormat>
#include <QObject>
#include "historiquec.h"

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

   void on_ajouter_tache_clicked();

   void on_calendarWidget_clicked(const QDate &date);

   void on_groupBox_2_clicked();

   void on_valider_ajout_2_clicked();

   void on_ajout_calender_clicked();

   void on_ajoutDate_clicked();

   void on_table_tache_activated(const QModelIndex &index);

   void on_pushButton_5_clicked();

   void on_supprimer_calendrier_clicked();

   void on_le_chercher_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    activite A;
    Tache T;
   calender_A H;
};
#endif // MAINWINDOW_H
