#include "qribbonstylesheetmanager.h"
#include <QApplication>
#include <QFile>
USING_NAMESPACE_CBERSUI

QRibbonStyleSheetManager* QRibbonStyleSheetManager::sManager = nullptr;
QRibbonStyleSheetManager::QRibbonStyleSheetManager(QObject *parent) : QObject(parent)
{
    addStyleSheet("office2007_blue", loadStyleSheet(":/office2007/Resource/office2007_blue/office2007_blue.qss"));
    addStyleSheet("office2007_black", loadStyleSheet(":/office2007/Resource/office2007_black/office2007_black.qss"));
}

QRibbonStyleSheetManager* QRibbonStyleSheetManager::instance()
{
    if( sManager==nullptr )
        sManager = new QRibbonStyleSheetManager();
    return sManager;
}

QString QRibbonStyleSheetManager::loadStyleSheet(const QString& url)
{
    QString styleSheet = "";
    QFile qss(url) ;
    if(qss.open(QIODevice::ReadOnly))
    {
        styleSheet = qss.readAll();
        qss.close() ;
    }

    return styleSheet;
}

int QRibbonStyleSheetManager::count()
{
    return mStyleSheets.count();
}

QString QRibbonStyleSheetManager::styleSheet(const QString& name)
{
    if( name.isEmpty() )
        return "";

    return mStyleSheets.value(name.toLower());
}

bool QRibbonStyleSheetManager::addStyleSheet(const QString& name, const QString& styleSheet)
{
    if( name.isEmpty() || styleSheet.isEmpty() )
        return false;

    mStyleSheets.insert(name.toLower(), styleSheet);
    return true;
}

bool QRibbonStyleSheetManager::removeStyleSheet(const QString& name)
{
    return mStyleSheets.remove(name.toLower());
}

void QRibbonStyleSheetManager::clear()
{
    mStyleSheets.clear();
}

bool QRibbonStyleSheetManager::applyStyleSheet(const QString& name)
{
    QString style = styleSheet(name);
    if( style.isEmpty() )
        return false;

    if( mOldStyleSheet.isEmpty() )
        mOldStyleSheet = qApp->styleSheet();

    //style += mOldStyleSheet;
    qApp->setStyleSheet(style);
    return true;
}
