QT       += core charts sql
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    aliment.cpp \
    alimentdao.cpp \
    courses.cpp \
    coursesdao.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    qpushbuttonaliment.cpp

HEADERS += \
    aliment.h \
    alimentdao.h \
    courses.h \
    coursesdao.h \
    databasemanager.h \
    mainwindow.h \
    qpushbuttonaliment.h

FORMS += \
    mainwindow.ui
