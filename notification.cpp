#include "notification.h"

#include<QString>
#include<QSqlQueryModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"equipements.h"
#include"connection.h"
#include <QFileDialog>
#include <QMessageBox>
#include<QIntValidator>
#include<QRegExpValidator>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include"Qrcode.h"
#include <QPixmap>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtCore/QBuffer>
#include <QtCore/QDebug>
#include <QtCore/QByteArray>
#include <QtGui/QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QUrl>
#include <QUrlQuery>
#include<QSystemTrayIcon>
#include<notification.h>
Notification::Notification()
{

}

void Notification::notification_ajoutEquipement()
{

    float S;
    QSqlQuery qry;
      qry.prepare("SELECT * from HISTORIQUEEQUIPEMENTS");
      if (!qry.exec()) {
          qDebug() << "Error executing query:" << qry.lastError().text();
          return;
      }
      while (qry.next())
      {
          QDateTime date = QDateTime::currentDateTime();
          int nbjours = qry.value("DATEUTILISATION").toDateTime().daysTo(date);
          QSqlQuery qry1,qry2;
          qry1.prepare("SELECT count(*) CNT FROM HISTORIQUEEQUIPEMENTS where IDEQUIPEMENT = :id");
          qry1.bindValue(":id", qry.value("IDEQUIPEMENT"));
          if (!qry1.exec()) {
              qDebug() << "Error executing query:" << qry1.lastError().text();
              continue;
          }
          if (qry1.next()) {
              S = nbjours * 0.5 + qry1.value("CNT").toFloat() * 0.5;
              //S=7;
              if (S > 3.5)
              {
                  qry2.prepare("SELECT NOM FROM EQUIPEMENTS where IDEQUIPEMENT = :id");
                  qry2.bindValue(":id", qry.value("IDEQUIPEMENT"));
                  qry2.exec();
                  while (qry2.next())
                  {
                      QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                      QIcon icon("D:/projet/integration_ameni-sarah back up + seif/LOGO.png");
                      notifyIcon->setIcon(icon);
                      notifyIcon->show();
                      notifyIcon->showMessage(qry2.value("NOM").toString()+" n'a pas été utilisé pendant plus de 7 jours "," veuillez vérifier son état ",QSystemTrayIcon::Information,15000);
                  }

              }
          }
      }
      }








