QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addpatientinfodialog.cpp \
    databasehelper.cpp \
    deseasetreeitem.cpp \
    main.cpp \
    authwindow.cpp \
    menuwindow.cpp \
    recordsedit.cpp \
    userentity.cpp

HEADERS += \
    addpatientinfodialog.h \
    authwindow.h \
    constants.h \
    databasehelper.h \
    deseasetreeitem.h \
    menuwindow.h \
    recordsedit.h \
    userentity.h

FORMS += \
    addpatientinfodialog.ui \
    authwindow.ui \
    menuwindow.ui \
    recordsedit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
