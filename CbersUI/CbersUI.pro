#-------------------------------------------------
#
# Project created by QtCreator 2016-07-12T17:18:16
#
#-------------------------------------------------
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
TARGET = CbersUI

DEFINES += CBERSUI_LIBRARY

SOURCES += \
    qribbonbar.cpp \
    qribboncategory.cpp \
    qribbonpanel.cpp \
    qribbonstylesheetmanager.cpp \
    qribbontabwidget.cpp \
    qtitlewidget.cpp \
    qseparator.cpp

HEADERS +=\
    qribbonbar.h \
    qribboncategory.h \
    qribbonpanel.h \
    qribbonstylesheetmanager.h \
    qribbontabwidget.h \
    qtitlewidget.h \
    cbersui_global.h \
    qseparator.h

{
    CONFIG(debug, debug|release){
        TARGET = $$join(TARGET,,,d)

        DESTDIR = $$PWD/../lib/debug
        DLLDESTDIR = $$PWD/../bin/debug
    }
    else{
        DESTDIR = $$PWD/../lib/release
        DLLDESTDIR = $$PWD/../bin/release
    }
}

RESOURCES += \
    cbersui.qrc

TRANSLATION_DIR = $$PWD/../i18n/
TRANSLATIONS = $$TRANSLATION_DIR/CbersUI_zh_CN.ts

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

SDK_PATH = $$PWD/../include/CbersUI/
win32{
    SDK_PATH ~= s,/,\\,g
    QMAKE_POST_LINK += if exist $$quote($$SDK_PATH) ( rmdir /S /Q $$quote($$SDK_PATH) ) $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += cd $$quote($$PWD) $$escape_expand(\\n\\t)
}
unix{
    QMAKE_POST_LINK += rm -rf $$quote($$SDK_PATH) $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += cd $$quote($$PWD) $$escape_expand(\\n\\t)
}

QMAKE_POST_LINK += $$copyToDir($$HEADERS, $$SDK_PATH, $$PWD)

# Auto Update And Release TRANSLATIONS
win32:TRANSLATION_DIR ~= s,/,\\,g
win32{
    QMAKE_POST_LINK += if not exist $$quote($$TRANSLATION_DIR) ( $$QMAKE_MKDIR $$quote($$TRANSLATION_DIR) ) $$escape_expand(\\n\\t)
}
unix{
    QMAKE_POST_LINK += $$QMAKE_MKDIR -p $$quote($$TRANSLATION_DIR) $$escape_expand(\\n\\t)
}

QMAKE_POST_LINK += $(QTDIR)/bin/lupdate $$PWD/CbersUI.pro $$escape_expand(\\n\\t)
QMAKE_POST_LINK += $(QTDIR)/bin/lrelease $$PWD/CbersUI.pro $$escape_expand(\\n\\t)

RELEASE_TRANSLATIONS = $$TRANSLATIONS
RELEASE_TRANSLATIONS ~= s,.ts,.qm,g
QMAKE_POST_LINK += $$copyToDir($$RELEASE_TRANSLATIONS, $$DLLDESTDIR/i18n/)
