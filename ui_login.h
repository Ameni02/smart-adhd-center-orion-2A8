/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QPushButton *Ajouter_event;
    QLabel *label;
    QLineEdit *Titre_19;
    QLineEdit *Titre_20;
    QLabel *label_78;
    QLabel *label_79;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_GIF;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(1181, 729);
        login->setStyleSheet(QString::fromUtf8("background: rgb(191, 162, 219);"));
        groupBox = new QGroupBox(login);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(90, 80, 991, 561));
        groupBox->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255);\n"
"border-radius: 30px;"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 0, 51, 561));
        groupBox_2->setStyleSheet(QString::fromUtf8("background:rgb(207, 77, 206);\n"
"border-radius: 30px;"));
        Ajouter_event = new QPushButton(groupBox);
        Ajouter_event->setObjectName(QString::fromUtf8("Ajouter_event"));
        Ajouter_event->setGeometry(QRect(670, 340, 151, 41));
        Ajouter_event->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"width: 214.24px;\n"
"height: 42.47px;\n"
"left: 90px;\n"
"top: 97px;\n"
"color:black;\n"
"background:rgb(207, 77, 206);\n"
"/*background: #F0D9FF;*/\n"
"border-radius: 10px;\n"
"}\n"
"QPushButton::hover\n"
"{\n"
"font-size:15px;\n"
"color:rgb(255, 255, 255);\n"
"}"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(690, 80, 121, 61));
        Titre_19 = new QLineEdit(groupBox);
        Titre_19->setObjectName(QString::fromUtf8("Titre_19"));
        Titre_19->setGeometry(QRect(590, 190, 291, 41));
        Titre_19->setStyleSheet(QString::fromUtf8("QLineEdit{ \n"
"                                        background-color:rgb(192, 192, 255);;\n"
"                                        border: 2px solid gray;\n"
"                                        border-radius: 10px;\n"
"                                        padding: 0 8px;\n"
"                                        selection-background-color: darkgray;\n"
"                                        font-size: 16px;}\n"
"                                        QLineEdit:focus { \n"
"                                        background-color:rgb(192, 192, 255);}"));
        Titre_20 = new QLineEdit(groupBox);
        Titre_20->setObjectName(QString::fromUtf8("Titre_20"));
        Titre_20->setGeometry(QRect(590, 280, 291, 41));
        Titre_20->setStyleSheet(QString::fromUtf8("QLineEdit{ \n"
"                                        background-color:rgb(192, 192, 255);;\n"
"                                        border: 2px solid gray;\n"
"                                        border-radius: 10px;\n"
"                                        padding: 0 8px;\n"
"                                        selection-background-color: darkgray;\n"
"                                        font-size: 16px;}\n"
"                                        QLineEdit:focus { \n"
"                                        background-color:rgb(192, 192, 255);}"));
        label_78 = new QLabel(groupBox);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        label_78->setGeometry(QRect(590, 150, 81, 31));
        label_78->setStyleSheet(QString::fromUtf8("color:rgb(127, 124, 130);\n"
"font: 8pt \"Tahoma\";\n"
" font-family: Arial, sans-serif;"));
        label_79 = new QLabel(groupBox);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setGeometry(QRect(590, 240, 121, 31));
        label_79->setStyleSheet(QString::fromUtf8("color:rgb(127, 124, 130);\n"
"font: 8pt \"Tahoma\";\n"
" font-family: Arial, sans-serif;"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(630, 410, 161, 31));
        label_2->setStyleSheet(QString::fromUtf8("color:rgb(127, 124, 130);"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(770, 410, 81, 28));
        pushButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"\n"
"color:rgb(0, 170, 0);\n"
"background-color: rgba( 255, 255, 255, 0% );\n"
"/*background: #F0D9FF;*/\n"
"border-radius: 10px;\n"
"}\n"
"QPushButton::hover\n"
"{\n"
"color:rgb(170, 0, 127);\n"
"\n"
"}"));
        label_GIF = new QLabel(groupBox);
        label_GIF->setObjectName(QString::fromUtf8("label_GIF"));
        label_GIF->setGeometry(QRect(170, 210, 271, 251));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        Ajouter_event->setText(QCoreApplication::translate("login", "validation ", nullptr));
        label->setText(QCoreApplication::translate("login", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600;\">LOG IN</span></p></body></html>", nullptr));
        label_78->setText(QCoreApplication::translate("login", "<html><head/><body><p><span style=\" font-size:12pt;\">Email:</span></p></body></html>", nullptr));
        label_79->setText(QCoreApplication::translate("login", "<html><head/><body><p><span style=\" font-size:12pt;\">password:</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("login", "<html><head/><body><p><span style=\" font-weight:600;\">don't have an account?</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("login", "Sign up", nullptr));
        label_GIF->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
