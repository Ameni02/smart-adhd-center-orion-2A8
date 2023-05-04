#include "historiquec.h"
#include "activite.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtSql/QSqlQuery>
#include <QApplication>
#include <QCalendarWidget>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QtCore/QtDebug>

calender_A::calender_A()
{
    id_historique=0;
    Date="";
}
calender_A::calender_A(int idactive, QString date)
{
this->id_activite=idactive;
    this->Date=date;
}
int calender_A::getid_C(){
    return id_activite;
}
void calender_A::setid_C(int id_activite)
{
    this->id_activite=id_activite;
}
bool calender_A::calender_ajout(){


    QSqlQuery query;

    query.prepare("insert into HISTORIQUEACTIVITES (IDACTIVITE,DATEACTIVITE)"
                  "VALUES ( :activite,:date)");
    query.bindValue(":date",Date);
    query.bindValue(":activite",id_activite);

return query.exec();
}
bool calender_A:: supprmierCalender(int id)
{
    QSqlQuery query;

    query.prepare(" Delete from HISTORIQUEACTIVITES where IDACTIVITE=:id");
    query.bindValue(0,id);

return query.exec();

    return query.exec();
}
