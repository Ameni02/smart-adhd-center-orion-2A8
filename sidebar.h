#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QFrame>
#include <QPropertyAnimation>

class Sidebar : public QFrame
{
    Q_OBJECT

public:
     Sidebar(QFrame *frame);

public slots:
    void toggleSidebar();
    void show();
    void hide();

private:
    QPropertyAnimation *animation;
    bool isSidebarShown;
    QFrame *frame;


};

#endif // SIDEBAR_H
