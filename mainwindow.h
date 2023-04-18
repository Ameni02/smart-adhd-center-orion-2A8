#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
void onButtonClicked(const QModelIndex& index);
    void on_Ajouter_event_clicked();
    void on_Ajouter_patient_clicked();

    void populateModel();

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
    void on_statisque_clicked();

    void on_updat_done_clicked();
    void on_txtFilter_textChanged(const QString &arg1);
    void on_uploade_photo_clicked();
    void on_pdf_2_clicked();
    void makePlot();
    void on_photo_patient_clicked();
    void sendMail();
    QString currDate();

    void on_supprimerPatient_3_clicked();

    void on_affichePatient_new_clicked();

private:
    Ui::MainWindow *ui;
    Patient pat;
    QImage imagePatient,imagePatientTable;
    QByteArray photoPatient;
};
#endif // MAINWINDOW_H
