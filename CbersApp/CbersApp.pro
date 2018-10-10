#-------------------------------------------------
#
# Project created by QtCreator 2016-09-08T16:10:14
#
#-------------------------------------------------

QT       += core gui opengl xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = CbersApp
TEMPLATE = app

{
    CONFIG(debug, debug|release){
        TARGET = $$join(TARGET,,,d)

        DESTDIR = $$PWD/../bin/debug
    }
    else{
        DESTDIR = $$PWD/../bin/release
    }
}


SOURCES += main.cpp\
        mainwindow.cpp \
    pluginmanager.cpp \
    ribbonpluginmanager.cpp

HEADERS  += mainwindow.h \
    pluginmanager.h \
    ribbonpluginmanager.h

FORMS    += mainwindow.ui


CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lCbersUI
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lCbersUId

unix{
    LIBS += -ldl
}

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../include/CbersUI
INCLUDEPATH += $$PWD/../include/x3py
INCLUDEPATH += $$PWD/../include/PluginCore
DEPENDPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include/CbersUI
DEPENDPATH += $$PWD/../include/x3py
DEPENDPATH += $$PWD/../include/PluginCore

win32{
    LIBS += -lDbghelp
}

SDK_PATH = $$PWD/../

win32{
    RC_FILE= CbersApp_win32.rc
}

RESOURCES += \
    CbersApp.qrc

TRANSLATION_DIR = $$PWD/../i18n/
TRANSLATIONS = $$TRANSLATION_DIR/CbersApp_zh_CN.ts

# Copies the given files to the destination directory
defineReplace(copyToDir) {
    files = $$1
    DIR = $$2
    SRCDIR = $$3
    LINK =

    win32:DIR ~= s,/,\\,g
    win32{
        LINK += if not exist $$quote($$DIR) ( $$QMAKE_MKDIR $$quote($$DIR) ) $$escape_expand(\\n\\t)
    }
    unix{
        LINK += $$QMAKE_MKDIR $$quote($$DIR) $$escape_expand(\\n\\t)
    }
    for(FILE, files) {
        !isEmpty(SRCDIR){
            FILE = $$SRCDIR/$$FILE
        }
        win32:FILE ~= s,/,\\,g
        LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DIR) $$escape_expand(\\n\\t)
    }
    return($$LINK)
}

win32{
    QMAKE_POST_LINK += cd $$quote($$PWD) $$escape_expand(\\n\\t)
}
unix{
    QMAKE_POST_LINK += cd $$quote($$PWD) $$escape_expand(\\n\\t)
}

# Auto Update And Release TRANSLATIONS
win32:TRANSLATION_DIR ~= s,/,\\,g
win32{
    QMAKE_POST_LINK += if not exist $$quote($$TRANSLATION_DIR) ( $$QMAKE_MKDIR $$quote($$TRANSLATION_DIR) ) $$escape_expand(\\n\\t)
}
unix{
    QMAKE_POST_LINK += $$QMAKE_MKDIR -p $$quote($$TRANSLATION_DIR) $$escape_expand(\\n\\t)
}

QMAKE_POST_LINK += $(QTDIR)/bin/lupdate $$PWD/CbersApp.pro $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $(QTDIR)/bin/lrelease $$PWD/CbersApp.pro $$escape_expand(\\n\\t)
RELEASE_TRANSLATIONS = $$TRANSLATIONS
RELEASE_TRANSLATIONS ~= s,.ts,.qm,g
QMAKE_POST_LINK += $$copyToDir($$RELEASE_TRANSLATIONS, $$DESTDIR/i18n/)
