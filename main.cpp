
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
    {w.show();

        QSystemTrayIcon trayIcon;
        trayIcon.setIcon(QIcon("D:/projet/integration_ameni-sarah back up + seif/exit2.png")); // set the icon for the tray
        trayIcon.show(); // show the tray icon

        // create a menu for the tray icon
        QMenu menu;
        QAction *exitAction = menu.addAction("Exit");
        QObject::connect(exitAction, &QAction::triggered, &a, &QApplication::quit); // exit the application when "Exit" is clicked

        trayIcon.setContextMenu(&menu); // set the menu for the tray icon
}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
