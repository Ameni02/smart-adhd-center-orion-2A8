#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "event.h"
#include <QMainWindow>
#include "intervenants.h"
#include <QPixmap>

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
    void mySlot();

private slots:

    void on_Ajouter_event_clicked();



    void on_uploade_fichier_clicked();

    void on_Events_clicked();

    void on_validation_ajout_clicked();

    void on_pushButton_clicked();

    void on_Ajouter_event_2_clicked();

    void on_pushButton_2_clicked();

    void on_Ajouter_event_3_clicked();

    void on_Exit_clicked();

    void on_Intervenants_clicked();

    void on_Ajouter_event_4_clicked();

    void on_Ajouter_event_6_clicked();

    void on_Ajouter_event_5_clicked();

    void on_Ajouter_event_8_clicked();

    void on_Ajouter_event_7_clicked();

    void on_Ajouter_event_10_clicked();

    void closeEvent (QCloseEvent *event);
    void on_uploade_fichier_2_clicked();

    void on_Profil_clicked();

    void on_Ajouter_event_12_clicked();

    void on_Ajouter_event_9_clicked();

    void on_Ajouter_event_11_clicked();

    void on_imageLabel_3_linkActivated(const QString &link);


    void on_imageLabel_2_linkActivated(const QString &link);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_Profil_2_clicked();

    void on_Ajouter_event_13_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

    void on_Ajouter_event_15_clicked();

    void on_Ajouter_event_14_clicked();

    void on_Ajouter_event_16_clicked();

    void on_Ajouter_event_17_clicked();

    void on_Ajouter_event_18_clicked();

    void on_Ajouter_event_19_clicked();

    void on_Ajouter_event_20_clicked();

private:
    Ui::MainWindow *ui;
    Event Evt;
    INTERVENANTS I;
    QImage imageIntervenant,imageIntervenantTable;
};
#endif // MAINWINDOW_H
