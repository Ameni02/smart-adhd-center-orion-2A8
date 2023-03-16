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

private:
    Ui::MainWindow *ui;
    activite A;
};
#endif // MAINWINDOW_H
