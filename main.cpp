
#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    qputenv("QT_DIRECT3D_NO_DEBUG_LAYER", "1");
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
