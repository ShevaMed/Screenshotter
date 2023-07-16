QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/screenlogic/screenshotthread.cpp \
    src/database/dbmanager.cpp \
    src/main.cpp \
    src/ui/gridwidget.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    src/screenlogic/screenshotthread.h \
    src/screenlogic/screenshotinfo.h \
    src/database/dbmanager.h \
    src/ui/gridwidget.h \
    src/ui/mainwindow.h

FORMS += \
    src/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
