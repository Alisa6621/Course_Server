TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT       += core
QT       += network
QT       += xml
QT       -= gui

SOURCES += main.cpp \
    server.cpp \
    request.cpp \
    log.cpp \
    response.cpp \
    config.cpp

HEADERS += \
    server.h \
    request.h \
    log.h \
    response.h \
    config.h \
    configparam.h
