#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "event.h"
#include "patient.h"
#include <QMainWindow>
using namespace std;

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
    void on_Ajouter_patient_clicked();



    void on_uploade_fichier_clicked();

    void on_Events_clicked();
    void on_patients_clicked();

    void on_validation_ajout_clicked();
    void on_validation_ajout_patient_clicked();

    void on_Patients_clicked();

    void on_validation_ajout_2_clicked();


    void on_supprimerPatient_clicked();
    void on_affichePatient_clicked();

    void on_supprimerPatient_2_clicked();



    void on_modifierPatient_2_clicked();

    void on_updat_done_clicked();


private:
    Ui::MainWindow *ui;
    Event Evt;
    Patient pat;
};
#endif // MAINWINDOW_H
