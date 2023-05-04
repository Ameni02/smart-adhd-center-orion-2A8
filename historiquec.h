#ifndef HISTORIQUEC_H
#define HISTORIQUEC_H
#include <QString>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QObject>
#include <QDateTime>

class calender_A
{
    QString Date;
    int id_activite, id_historique;
public:
    calender_A();
   calender_A(int idactive, QString date);
       int getid_C();

        void setid_C(int);

    bool calender_ajout();
    void ajouterActivite(QCalendarWidget *calendrier);
    bool supprmierCalender(int);
private:

};

#endif // HISTORIQUEC_H
