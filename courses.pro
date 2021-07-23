TEMPLATE = app TARGET = course

QT += core gui charts
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    window.cpp

HEADERS += \
    window.h


