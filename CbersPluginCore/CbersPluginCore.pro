#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T16:43:03
#
#-------------------------------------------------

QT       -= gui

TARGET = CbersPluginCore
TEMPLATE = lib

DEFINES += CBERSPLUGINCORE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    module.cpp \
    UICore.cpp

HEADERS +=\
        cbersplugincore_global.h \
    UIPlugins.h \
    UICore.h \
    UIPluginsEvents.h

PROJECT_PATH = $$PWD
SDK_PATH = $$PROJECT_PATH/../
#TRANSLATION_LANGS = zh_CN
include( pluginconfig.pri )

QMAKE_POST_LINK += $$copyToDir(pluginconfig.pri, $$SDK_PATH/include/, $$PROJECT_PATH)

