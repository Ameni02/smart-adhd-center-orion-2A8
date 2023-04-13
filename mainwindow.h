#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"equipements.h"
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



    void on_pdf_btn_2_clicked();

private:
    Ui::MainWindow *ui;
    Equipements E;
    //Ajouter un attribut à la classe mainwindow qui correspond à un objet de la classe equipement pour pouvoir faire appel à la méthode supprimer ()
};
#endif // MAINWINDOW_H
