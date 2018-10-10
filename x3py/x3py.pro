#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T12:31:26
#
#-------------------------------------------------

QT       -= gui

CONFIG += c++11

TARGET = x3manager
TEMPLATE = lib
TARGET_EXT = .pln

DEFINES += X3PY_LIBRARY

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
    source/core/x3manager/module.cpp \
    source/core/x3manager/plugins.cpp \
    source/core/x3manager/workpath.cpp

HEADERS +=\
    interface/core/manager/iplugins.h \
    interface/core/manager/iworkpath.h \
    interface/core/manager/x3manager.h \
    interface/core/module/classentry.h \
    interface/core/module/classmacro.h \
    interface/core/module/moduleitem.h \
    interface/core/module/modulemacro.h \
    interface/core/module/normalobject.h \
    interface/core/module/pluginimpl.h \
    interface/core/module/plugininc.h \
    interface/core/module/singletonobj.h \
    interface/core/nonplugin/scanplugins.h \
    interface/core/nonplugin/swigext.h \
    interface/core/nonplugin/useplugin.h \
    interface/core/nonplugin/useplugins.h \
    interface/core/observer/eventobserver.h \
    interface/core/observer/fireevent.h \
    interface/core/observer/fireobjevent.h \
    interface/core/observer/observerimpl.h \
    interface/core/observer/observerobject.h \
    interface/core/portability/func_s.h \
    interface/core/portability/pathstr.h \
    interface/core/portability/portimpl.h \
    interface/core/portability/uniximpl.h \
    interface/core/portability/winimpl.h \
    interface/core/portability/x3port.h \
    interface/core/portability/x3unix.h \
    interface/core/portability/x3win.h \
    interface/core/utilfunc/convstr.h \
    interface/core/utilfunc/loadmodule.h \
    interface/core/utilfunc/lockcount.h \
    interface/core/utilfunc/lockrw.h \
    interface/core/utilfunc/readints.h \
    interface/core/utilfunc/roundstr.h \
    interface/core/utilfunc/safecall.h \
    interface/core/utilfunc/scanfiles.h \
    interface/core/utilfunc/syserrstr.h \
    interface/core/utilfunc/vecfunc.h \
    interface/core/iobject.h \
    interface/core/objptr.h \
    source/core/x3manager/plugins.h \
    source/core/x3manager/workpath.h \
    interface/core/observer/fireeventex.h \
    interface/core/observer/fireobjeventex.h

{
    CONFIG(debug, debug|release){
        DESTDIR = $$PWD/../bin/debug/CbersPlugins
    }
    else{
        DESTDIR = $$PWD/../bin/release/CbersPlugins
    }
}

INCLUDEPATH += $$PWD/interface/core
DEPENDPATH += $$PWD/interface/core

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

SDK_PATH = $$PWD/../include/x3py/
win32{
    SDK_PATH ~= s,/,\\,g
    QMAKE_POST_LINK += if exist $$quote($$SDK_PATH) ( rmdir /S /Q $$quote($$SDK_PATH) ) $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += cd $$quote($$PWD) $$escape_expand(\\n\\t)
}
unix{
    QMAKE_POST_LINK += rm -rf $$quote($$SDK_PATH) $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += cd $$quote($$PWD) $$escape_expand(\\n\\t)
}

QMAKE_POST_LINK += $$copyToDir("interface/core/*.h", $$SDK_PATH, $$PWD)
QMAKE_POST_LINK += $$copyToDir("interface/core/manager/*.h", $$SDK_PATH/manager/, $$PWD)
QMAKE_POST_LINK += $$copyToDir("interface/core/module/*.h", $$SDK_PATH/module/, $$PWD)
QMAKE_POST_LINK += $$copyToDir("interface/core/nonplugin/*.h", $$SDK_PATH/nonplugin/, $$PWD)
QMAKE_POST_LINK += $$copyToDir("interface/core/observer/*.h", $$SDK_PATH/observer/, $$PWD)
QMAKE_POST_LINK += $$copyToDir("interface/core/portability/*.h", $$SDK_PATH/portability/, $$PWD)
QMAKE_POST_LINK += $$copyToDir("interface/core/utilfunc/*.h", $$SDK_PATH/utilfunc/, $$PWD)

unix{
    SRCEXT = .so
    DSTEXT = .pln
    QMAKE_POST_LINK += mv -f $$quote($$DESTDIR/lib$$TARGET$$SRCEXT) $$quote($$DESTDIR/$$TARGET$$DSTEXT) $$escape_expand(\\n\\t)
}
