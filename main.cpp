#include "mainwindow.h"
#include "connect.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connect c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {
        w.show();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


   return a.exec();
}



