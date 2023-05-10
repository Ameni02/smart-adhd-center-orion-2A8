QT       += core gui sql printsupport multimediawidgets

QT += widgets
QT += core

QT += core gui charts
QT       += core gui  serialport

QT+= charts serialport
QT += sql
QT+= location qml quickwidgets
QT += charts
QT += axcontainer
QT += printsupport
QT += core gui widgets printsupport
QT+= location qml quickwidgets
QT += core gui sql network serialport

QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = projet
CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)



SOURCES += \
    arduino2.cpp \
    centeredtextdelegate.cpp \
    chatbot.cpp \
     event.cpp \
    Qrcode.cpp \
    arduino.cpp \
    connection.cpp \
    equipements.cpp \
    imagetablemodel.cpp \
    intervenants.cpp \
    main.cpp \
    mainwindow.cpp \
    activite.cpp \
    historiquec.cpp \
notification.cpp \
    patient.cpp \
    qcustomplot.cpp \
    sidebar.cpp \
    smtp.cpp
HEADERS += \
    arduino2.h \
    centeredtextdelegate.h \
    chatbot.h \
 event.h \
    Qrcode.h \
    arduino.h \
    connection.h \
    equipements.h \
    imagetablemodel.h \
    intervenants.h \
    mainwindow.h \
    activite.h \
    historiquec.h \
    notification.h \
    patient.h \
    qcustomplot.h \
    sidebar.h \
    smtp.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Tsawer.qrc
