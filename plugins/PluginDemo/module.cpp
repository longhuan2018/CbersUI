#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QTranslator>
#include <QLocale>
#include <QTextCodec>
#include "module/plugininc.h"
#include "module/pluginimpl.h"
#include "module/modulemacro.h"
#include "observer/observerimpl.h"
#include "viewplugin.h"
#include "dockwidgetplugin.h"
#include "commandplugin.h"
#include "toolplugin.h"

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY(ViewPlugin)
    XDEFINE_CLASSMAP_ENTRY(DockWidgetPlugin)
    XDEFINE_CLASSMAP_ENTRY(CommandPlugin)
    XDEFINE_CLASSMAP_ENTRY(ToolPlugin)
XEND_DEFINE_MODULE_DLL()

QTranslator gTranslator;
OUTAPI bool x3InitializePlugin()
{
    //////////////////////////////////////////////////////////////
    // Load Translator
    QSettings mySettings;
    QString i18nPath = QApplication::applicationDirPath() + QDir::separator() + "i18n";
    QString myUserLocale = mySettings.value( "locale/userLocale", "" ).toString();
    bool myLocaleOverrideFlag = mySettings.value( "locale/overrideFlag", false ).toBool();
    QString myTranslationCode;
    if ( !myTranslationCode.isNull() && !myTranslationCode.isEmpty() )
    {
        mySettings.setValue( "locale/userLocale", myTranslationCode );
    }
    else
    {
        if ( !myLocaleOverrideFlag || myUserLocale.isEmpty() )
        {
            myTranslationCode = QLocale::system().name();
            mySettings.setValue( "locale/userLocale", myTranslationCode );
        }
        else
        {
            myTranslationCode = myUserLocale;
        }
    }

    if ( myTranslationCode != "C" )
    {
        if ( gTranslator.load( QString( "PluginDemo_" ) + myTranslationCode, i18nPath ) )
        {
            QApplication::installTranslator( &gTranslator );
        }
        else
        {
            qWarning( "loading of PluginDemo translation failed [%s]", QString( "%1/PluginDemo_%2" ).arg( i18nPath ).arg( myTranslationCode ).toLocal8Bit().constData() );
        }
    }
    //////////////////////////////////////////////////////////////
    return true;
}

OUTAPI void x3UninitializePlugin()
{
    if( !gTranslator.isEmpty() )
    {
        QApplication::removeTranslator( &gTranslator );
    }
}
