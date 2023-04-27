#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"
#include "patient.h"
#include <QMainWindow>
#include "smtp.h"
#include <QBuffer>
#include <QFile>
#include <QPixmap>
#include <QByteArray>
#include "imagetablemodel.h"



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
    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino

    void on_Ajouter_event_clicked();
    void on_Ajouter_patient_clicked();

    void populateModel();


    void on_Events_clicked();
    void on_patients_clicked();


    void on_Patients_clicked();

    void on_validation_ajout_2_clicked();

    void on_affichePatient_clicked();

    void on_supprimerPatient_2_clicked();



    void on_modifierPatient_2_clicked();
    void on_statisque_clicked();

    void on_updat_done_clicked();
    void on_txtFilter_textChanged(const QString &arg1);
    void on_uploade_photo_clicked();
    void on_pdf_2_clicked();
    void makePlot();
    void on_photo_patient_clicked();
    void sendMail();

    void on_supprimerPatient_3_clicked();


    void on_expoterdb_clicked();

    void on_exportxl_clicked();

    void on_deletall_clicked();

    void on_deletall_2_clicked();

    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::MainWindow *ui;
    Patient pat;
    QImage imagePatient,imagePatientTable;
    QByteArray photoPatient;
    Arduino A;
    QByteArray data;
};
#endif // MAINWINDOW_H
