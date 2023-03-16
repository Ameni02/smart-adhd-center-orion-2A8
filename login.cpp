#include "login.h"
#include "ui_login.h"
#include <QMovie>
#include <QtGui>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    //GIF



}

login::~login()
{
    delete ui;
}



