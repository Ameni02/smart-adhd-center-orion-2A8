#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "event.h"
#include <QMainWindow>

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

    void on_Ajouter_event_clicked();



    void on_uploade_fichier_clicked();

    void on_Events_clicked();

    void on_validation_ajout_clicked();

    void on_botton_supprimer_clicked();

    //void combox_update();

    void on_botton_update_events_clicked();

    void on_pushButton_back_clicked();

   // void on_validation_update_event_clicked();

    void on_validation_update_events_clicked();

    void on_uploade_fichier_3_clicked();
    bool controle_saisir(int n);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Event Evt;
    QImage image_event;
};
#endif // MAINWINDOW_H
