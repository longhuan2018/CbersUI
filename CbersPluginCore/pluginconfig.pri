#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T16:43:03
#
#-------------------------------------------------
QT += core xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET_EXT = .pln

OUTPUT_INCLUDE_PATH = $$SDK_PATH/include/PluginCore/

INCLUDEPATH += $$SDK_PATH/include
INCLUDEPATH += $$SDK_PATH/include/x3py
INCLUDEPATH += $$OUTPUT_INCLUDE_PATH
DEPENDPATH += $$SDK_PATH/include
DEPENDPATH += $$SDK_PATH/include/x3py
DEPENDPATH += $$OUTPUT_INCLUDE_PATH

{
    CONFIG(debug, debug|release){
        DESTDIR = $$SDK_PATH/bin/debug/CbersPlugins
    }
    else{
        DESTDIR = $$SDK_PATH/bin/release/CbersPlugins
    }
}

!isEmpty(TRANSLATION_LANGS){
    TRANSLATION_DIR = $$SDK_PATH/i18n/
    TRANSLATIONS =
    for(LANG, $$TRANSLATION_LANGS) {
        TRANSLATIONS += $$TRANSLATION_DIR/$$TARGET_$$LANG.ts
    }
}

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

!isEmpty(OUTPUT_INCLUDE_PATH){
    win32{
        OUTPUT_INCLUDE_PATH ~= s,/,\\,g
        #QMAKE_POST_LINK += if exist $$quote($$OUTPUT_INCLUDE_PATH) ( rmdir /S /Q $$quote($$OUTPUT_INCLUDE_PATH) ) $$escape_expand(\\n\\t)
        QMAKE_POST_LINK += cd $$quote($$PROJECT_PATH) $$escape_expand(\\n\\t)
    }
    unix{
        #QMAKE_POST_LINK += rm -rf $$quote($$OUTPUT_INCLUDE_PATH) $$escape_expand(\\n\\t)
        QMAKE_POST_LINK += cd $$quote($$PROJECT_PATH) $$escape_expand(\\n\\t)
    }

    QMAKE_POST_LINK += $$copyToDir($$HEADERS, $$OUTPUT_INCLUDE_PATH, $$PROJECT_PATH)
}

# Auto Update And Release TRANSLATIONS
!isEmpty(TRANSLATION_DIR){
    win32:TRANSLATION_DIR ~= s,/,\\,g
    win32{
        QMAKE_POST_LINK += if not exist $$quote($$TRANSLATION_DIR) ( $$QMAKE_MKDIR $$quote($$TRANSLATION_DIR) ) $$escape_expand(\\n\\t)
    }
    unix{
        QMAKE_POST_LINK += $$QMAKE_MKDIR -p $$quote($$TRANSLATION_DIR) $$escape_expand(\\n\\t)
    }
    QMAKE_POST_LINK += $(QTDIR)/bin/lupdate $$PROJECT_PATH/$$TARGET.pro $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += $(QTDIR)/bin/lrelease $$PROJECT_PATH/$$TARGET.pro $$escape_expand(\\n\\t)

    RELEASE_TRANSLATIONS = $$TRANSLATIONS
    RELEASE_TRANSLATIONS ~= s,.ts,.qm,g
    QMAKE_POST_LINK += $$copyToDir($$RELEASE_TRANSLATIONS, $$DESTDIR/../i18n/)
}

unix{
    SRCEXT = .so
    DSTEXT = .pln
    QMAKE_POST_LINK += mv -f $$quote($$DESTDIR/lib$$TARGET$$SRCEXT) $$quote($$DESTDIR/$$TARGET$$DSTEXT) $$escape_expand(\\n\\t)
}
