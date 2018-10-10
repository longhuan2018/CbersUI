#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include "mainwindow.h"
#include "pluginmanager.h"
#include "x3py/observer/observerimpl.h"

int main(int argc, char *argv[])
{
    QString configpath = QFileInfo(QString::fromLocal8Bit(argv[0])).absolutePath() + "/config";
    QSettings::setDefaultFormat( QSettings::IniFormat );
    QSettings::setPath( QSettings::IniFormat, QSettings::UserScope, configpath);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/CbersApp.ico"));

    QCoreApplication::setOrganizationName( QObject::tr("CbersApp") );
    QCoreApplication::setOrganizationDomain( QObject::tr("CbersApp") );
    QCoreApplication::setApplicationName( QObject::tr("CbersApp") );
    QCoreApplication::setAttribute( Qt::AA_DontShowIconsInMenus, false );

    QSettings mySettings;
    //////////////////////////////////////////////////////////////
    // Load Translator
    QString i18nPath = QApplication::applicationDirPath() + "/i18n";
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

    QTranslator apptor( 0 );
    QTranslator cbersUItor( 0 );
    QTranslator qttor( 0 );
    if ( myTranslationCode != "C" )
    {
        if ( apptor.load( QString( "CbersApp_" ) + myTranslationCode, i18nPath ) )
        {
            a.installTranslator( &apptor );
        }
        else
        {
            qWarning( "loading of CbersApp translation failed [%s]", QString( "%1/CbersApp_%2" ).arg( i18nPath ).arg( myTranslationCode ).toLocal8Bit().constData() );
        }

        if ( cbersUItor.load( QString( "CbersUI_" ) + myTranslationCode, i18nPath ) )
        {
            a.installTranslator( &cbersUItor );
        }
        else
        {
            qWarning( "loading of CbersUI translation failed [%s]", QString( "%1/CbersUI_%2" ).arg( i18nPath ).arg( myTranslationCode ).toLocal8Bit().constData() );
        }

        if ( qttor.load( QString( "qt_" ) + myTranslationCode, i18nPath ) )
        {
            a.installTranslator( &qttor );
        }
        else
        {
            qWarning( "loading of qt translation failed [%s]", QString( "%1_%2" ).arg( i18nPath ).arg( myTranslationCode ).toLocal8Bit().constData() );
        }
    }
    //////////////////////////////////////////////////////////////

    if( !CPluginManager::Initialize("CbersPlugins") )
        return -1;

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
