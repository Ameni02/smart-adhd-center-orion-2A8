#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "event.h"
#include "arduino.h"
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


    void on_pushButton_3_clicked();

    void on_lineEdit_chercheEvent_textChanged(const QString &arg1);



    void on_Ajouter_event_4_clicked();

    void on_Ajouter_event_6_clicked();

    void on_events_statistics_clicked();

    void on_details_events_clicked();

    void on_EmissionCO2_clicked();

    void on_botton_trier_event_clicked();



    void on_pdf_Event_test_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButtontrier_eventC_2_clicked();

    void on_Settings_2_clicked();

    void on_pushButton_PORT_ON_clicked();

    void on_pushButton_OFF_PORT_clicked();

    void on_comboBox_selest_currentTextChanged(const QString &arg1);

    void on_botton_selsct_event_2_clicked();

    void on_botton_selsct_event_clicked();



private:
    Ui::MainWindow *ui;
    Event Evt;
    QImage image_event;
    QByteArray data;
    arduino A;
};
#endif // MAINWINDOW_H
