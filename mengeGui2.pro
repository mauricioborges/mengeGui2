#-------------------------------------------------
#
# Project created by QtCreator 2018-10-21T12:16:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mengeGui2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#TODO: dinamically clone and build Menge instead
win32:CONFIG(release, debug|release): LIBS += -L/home/mauricio/dev/Menge/projects/g++/build/release/lib -lmengeCore -lmengeVis
else:win32:CONFIG(debug, debug|release): LIBS += -L/home/mauricio/dev/Menge/projects/g++/build/debug/lib -lmengeCore -lmengeVis
else:unix: LIBS += -L/home/mauricio/dev/Menge/projects/g++/build/release/lib/ -lmengeCore -lmengeVis -ldl -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread


INCLUDEPATH += /home/mauricio/dev/Menge/src/include
DEPENDPATH += /home/mauricio/dev/Menge/src/include
INCLUDEPATH += /home/mauricio/dev/Menge/src
DEPENDPATH += /home/mauricio/dev/Menge/src
INCLUDEPATH += /home/mauricio/dev/Menge/src/Menge
DEPENDPATH += /home/mauricio/dev/Menge/src/Menge
INCLUDEPATH += /home/mauricio/dev/Menge/src/Menge/MengeCore
DEPENDPATH += /home/mauricio/dev/Menge/src/Menge/MengeCore
INCLUDEPATH += /home/mauricio/dev/Menge/src/Menge/MengeVis
DEPENDPATH += /home/mauricio/dev/Menge/src/Menge/MengeVis
