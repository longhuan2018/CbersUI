#include "viewplugin.h"
#include <QObject>
#include <QApplication>
#include <QFileInfo>
#include <QAction>

ViewPlugin::ViewPlugin(QWidget *parent) : QWidget(parent)
{
    Name(QStringLiteral("ViewPlugin"));
    Caption(QStringLiteral("View"));
    Category(QStringLiteral("Plugins"));
    Tooltip(QStringLiteral("ViewPlugin"));
    Description(QStringLiteral("ViewPlugin"));
    BitmapName(QStringLiteral("ViewPlugin"));

    setWindowTitle(Name());

}

ViewPlugin::~ViewPlugin()
{
    UnInitialize();
}

// IUIPlugin
bool ViewPlugin::Initialize()
{

    // Only Support appoint Events
    //supportsEvent("EventKey");
    registerHandlers();
    return true;
}

bool ViewPlugin::UnInitialize()
{

    unregisterHandlers();
    hide();
    return true;
}

bool ViewPlugin::SetBuddy(x3::IObject* val)
{
    if( m_spBuddy==val )
        return true;

    m_spBuddy = val;
    if( !m_spBuddy.valid() )
    {
        return false;
    }


    return true;
}

bool ViewPlugin::readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->readConfig(node, document, errorMessage) )
        return false;

    return true;
}

bool ViewPlugin::writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->writeConfig(node, document, errorMessage) )
        return false;

    return true;
}

// IUIView
QWidget* ViewPlugin::getViewWidget()
{
    return this;
}

// IAnythingEventObserver
bool ViewPlugin::OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam)
{
    //if( _stricmp(eventKey.c_str(), "EventKey")==0 )
    //{
    //}
    return true;
}

