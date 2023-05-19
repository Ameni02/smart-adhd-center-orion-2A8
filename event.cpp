#include "event.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include <QObject>
#include <QLCDNumber>
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QtGui>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QByteArray>
#include <QPrinter>
#include <QTableView>
#include <QPrintDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

Event::Event()
{

}


Event::Event(QString Titre_event, QString Desc_event, QString lieuEvent, QString genre_event, QString etat_event, QDateTime date_event,QByteArray image_e)
{

  this->Desc_event=Desc_event;
  this->lieuEvent=lieuEvent;
  this->Titre_event=Titre_event;
  this->genre_event=genre_event;
  this->etat_event=etat_event;
  this->date_event=date_event;

   this->image_e=image_e;


}

 bool Event::ajouter_event()
 {



     QSqlQuery query;

      //QVariant id = QVariant(id_event);
query.prepare("INSERT INTO EVENTS (NOM,DESCRIPTION,DATEEVENT,LIEU,GENRE,ETAT,AFFICHE)""VALUES(:Titre_event, :Desc_event, :date_event, :lieuEvent, :genre_event, :etat_event, :image_e)");



     // query.bindValue(":id_event",id);

     query.bindValue(":Titre_event",Titre_event);
     query.bindValue(":Desc_event",Desc_event);
     query.bindValue(":date_event",date_event);
     query.bindValue(":lieuEvent",lieuEvent);
     query.bindValue(":genre_event",genre_event);
     query.bindValue(":etat_event",etat_event);
     query.bindValue(":image_e",image_e);
     //query.bindValue(":intervenant_event",intervenant_event);




     return query.exec();
 }
  QSqlQueryModel * Event::afficher_event()
  {
      QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("SELECT * FROM Events");
      model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEVENT"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEEVENT"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("LIEU"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("GENRE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("ETAT"));

      return model;
  }
    bool Event::supprimer_event(int id)
    {
        QSqlQuery query;
        //QString res=QString::number(id);
        query.prepare("DELETE FROM EVENTS where IDEVENT= :id ");
        query.bindValue(":id",id);
         return query.exec();
    }

   bool Event::modifier_event(int id)
   {
       QSqlQuery query;
       query.prepare("UPDATE EVENTS set NOM=:Titre_event,DESCRIPTION=:Desc_event,DATEEVENT=:date_event,LIEU=:lieuEvent,GENRE=:genre_event,ETAT=:etat_event where IDEVENT=:id");
       query.bindValue(":id",id);
       query.bindValue(":Titre_event",Titre_event);
       query.bindValue(":Desc_event",Desc_event);
       query.bindValue(":date_event",date_event);
       query.bindValue(":lieuEvent",lieuEvent);
       query.bindValue(":genre_event",genre_event);
       query.bindValue(":etat_event",etat_event);
       //query.bindValue(":image_e",image_e);
       //query.bindValue(":intervenant_event",intervenant_event);
       qDebug() << "Updated";
       return query.exec();

   }

   bool Event::modifier_eventimage(int id)
   {
       QSqlQuery query;
       query.prepare("update EVENTS set NOM=:Titre_event,DESCRIPTION=:Desc_event,DATEEVENT=:date_event,LIEU=:lieuEvent,GENRE=:genre_event,ETAT=:etat_event,AFFICHE=:image_e where IDEVENT=:id");
       query.bindValue(":id",id);
       query.bindValue(":Titre_event",Titre_event);
       query.bindValue(":Desc_event",Desc_event);
       query.bindValue(":date_event",date_event);
       query.bindValue(":lieuEvent",lieuEvent);
       query.bindValue(":genre_event",genre_event);
       query.bindValue(":etat_event",etat_event);
       query.bindValue(":image_e",image_e);
       //query.bindValue(":intervenant_event",intervenant_event);
       qDebug() << "Updated";
       return query.exec();

   }

   QSqlQueryModel * Event::recherche_titreEvent(QString titre)
   {
       QSqlQueryModel * model = new QSqlQueryModel();

       model->setQuery("select * from EVENTS WHERE LOWER(NOM) LIKE LOWER('%"+titre+"%')");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEVENT"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEEVENT"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("LIEU"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("GENRE"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("ETAT"));
       return model;
   }
QChartView *Event::stat_gender()
{
    int pub=0;
    int Sensib=0;


    QSqlQuery query;
    query.prepare("select * from EVENTS where GENRE='Publicite'");
    query.exec();
    while(query.next())
        pub++;

    query.prepare("select * from EVENTS where GENRE='Sensibilisation'");
    query.exec();
    while(query.next())
        Sensib++;

     qDebug() << pub << Sensib  ;

     QPieSeries *series = new QPieSeries();
         series->append("Publicite",pub);
         series->append("Sensibilisation",Sensib);

         int total = pub + Sensib;
             // ajouter des étiquettes avec des pourcentages
          QString labelPublicite = QString("Pub (%1%)").arg((double)pub/total * 100, 0, 'f', 1);
          QString labelSensibilisation = QString("Sensib (%1%)").arg((double)Sensib/total * 100, 0, 'f', 1);
           series->slices().at(1)->setLabel(labelSensibilisation);
           series->slices().at(0)->setLabel(labelPublicite);


         QPieSlice *slice = series->slices().at(0);
         slice->setExploded(true);
         slice->setColor("#ffdaac");
         QPieSlice *slice2 = series->slices().at(1);
         slice2->setColor("#990000");

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Gender statistics");

         series->setLabelsVisible();

         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->chart()->setAnimationOptions(QChart::AllAnimations);
         chartView->chart()->legend()->hide();
         return chartView;
}
QChartView * Event::stat_type()
{
    int Virt=0;
    int Hyb=0;
    int Presen=0;

    QSqlQuery query;
    query.prepare("select * from EVENTS where ETAT='Virtuel'");
    query.exec();
    while(query.next())
        Virt++;


    query.prepare("select * from EVENTS where ETAT='Hybride'");
    query.exec();
    while(query.next())
        Hyb++;

    query.prepare("select * from EVENTS where ETAT='Presentiel'");
    query.exec();
    while(query.next())
        Presen++;

     qDebug() << Virt << Hyb << Presen ;


     QPieSeries *series0 = new QPieSeries();
         series0->append("Virtuel",Virt);
         series0->append("Hybride",Hyb);
         series0->append("Presentiel",Presen);
      int total = Virt + Hyb + Presen;

QString labelVirtuel = QString("Virtuel (%1%)").arg((double)Virt/total * 100, 0, 'f', 1);
QString labelHybride = QString("Hybride (%1%)").arg((double)Hyb/total * 100, 0, 'f', 1);
QString labelPresentiel = QString("Present (%1%)").arg((double)Presen/total * 100, 0, 'f', 1);
series0->slices().at(0)->setLabel(labelVirtuel);
series0->slices().at(1)->setLabel(labelHybride);
series0->slices().at(2)->setLabel(labelPresentiel);
     QPieSlice *slice3 = series0->slices().at(0);
     slice3->setExploded(true);
     slice3->setColor("#81c1b0");
     QPieSlice *slice4 = series0->slices().at(1);
     slice4->setColor("#b081c1");
     QPieSlice *slice5 = series0->slices().at(2);
     slice5->setColor("#f55d11");

     QChart *chart1 = new QChart();
     chart1->addSeries(series0);
     chart1->setTitle("type statistics");

     series0->setLabelsVisible();

     QChartView *chartView1 = new QChartView(chart1);
     chartView1->setRenderHint(QPainter::Antialiasing);
     chartView1->chart()->setAnimationOptions(QChart::AllAnimations);
     chartView1->chart()->legend()->hide();
     return chartView1;
}
QSqlQueryModel * Event::trierC( )
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENTS ORDER BY DATEEVENT ASC ");

    return model;
}

QSqlQueryModel * Event::trierD( )
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENTS ORDER BY DATEEVENT DESC ");

    return model;
}
  QSqlQueryModel *  Event::trier_event()
{
   QSqlQueryModel * model = new QSqlQueryModel();



       model->setQuery("SELECT * FROM EVENTS ORDER BY DATEEVENT DESC");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEVENT"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEEVENT"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("LIEU"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("GENRE"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("ETAT"));


   return model;
}
void Event::exportToPDF(QTableView *tableView)
{
   QPrinter printer(QPrinter::HighResolution);
   printer.setPrinterName("Printer Name"); // Set the printer name

   QPrintDialog dialog(&printer, nullptr);
   if (dialog.exec() != QDialog::Accepted)
   {
        return; // Cancel if the user cancels the dialog
   }

   QPainter painter(&printer);
   painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

   // Calculate the scaling factor to fit the table on the page
   double xscale = printer.pageRect(QPrinter::DevicePixel).width() / double(tableView->width());

   painter.scale(xscale, xscale);

   // Calculate the y-position to center the table on the page
   double ypos = (printer.pageRect(QPrinter::DevicePixel).height() / xscale - tableView->height()) / 1500;


   // Translate the painter to center the table on the page
   painter.translate(0, ypos);

   // Draw the TableView on the QPainter
   tableView->render(&painter);

   painter.end();
}


