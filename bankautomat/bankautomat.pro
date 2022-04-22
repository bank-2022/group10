QT       += core gui
QT       += network
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankactions.cpp \
    bankmain.cpp \
    drawanothersum.cpp \
    drawmoney.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    myurl.cpp \
    pin.cpp

HEADERS += \
    bankactions.h \
    bankmain.h \
    drawanothersum.h \
    drawmoney.h \
    login.h \
    mainwindow.h \
    myurl.h \
    pin.h

FORMS += \
    bankactions.ui \
    bankmain.ui \
    drawanothersum.ui \
    drawmoney.ui \
    login.ui \
    mainwindow.ui \
    pin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
