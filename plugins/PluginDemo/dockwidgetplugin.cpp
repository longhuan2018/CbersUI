#include "dockwidgetplugin.h"
#include "ui_dockwidgetplugin.h"
#include <QObject>
#include <QApplication>
#include <QFileInfo>
#include <QAction>

DockWidgetPlugin::DockWidgetPlugin(QWidget *parent) : QDockWidget(parent)
{
    Name(QStringLiteral("DockWidgetPlugin"));
    Caption(QStringLiteral("View"));
    Category(QStringLiteral("Plugins"));
    Tooltip(QStringLiteral("DockWidgetPlugin"));
    Description(QStringLiteral("DockWidgetPlugin"));
    BitmapName(QStringLiteral("DockWidgetPlugin"));

    setWindowTitle(Name());

    mToolButton = Q_NULLPTR;
    mDefaultIcon = true;

}

DockWidgetPlugin::~DockWidgetPlugin()
{
    UnInitialize();
}

// IUIPlugin
bool DockWidgetPlugin::Initialize()
{
    mToolButton = new QToolButton();
    mToolButton->setText(Name());
    mToolButton->setToolTip(Tooltip());
    mToolButton->setIconSize(QSize(32, 32));
    mToolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mToolButton->setAutoRaise(true);
    mToolButton->setMouseTracking(true);
    QString strBitmapName = BitmapName();
    QIcon icon;
    if( !strBitmapName.isEmpty() )
    {
        strBitmapName = QString("%1/Skins/%2.png").arg(QApplication::applicationDirPath()).arg(strBitmapName);
        QFileInfo fileInfo(strBitmapName);
        if( !fileInfo.exists() )
        {
            strBitmapName = QString("%1/Skins/default.png").arg(QApplication::applicationDirPath());
            fileInfo.setFile(strBitmapName);
        }
        else
            mDefaultIcon = false;

        if( fileInfo.exists() )
            icon.addFile(strBitmapName);
    }

    if( !icon.isNull() )
    {
        mToolButton->setIcon(icon);
        setWindowIcon(icon);
    }

    mToolButton->setCheckable(true);
    QAction* actionDockWidget = toggleViewAction();
    actionDockWidget->setIcon(icon);
    actionDockWidget->setText(Name());
    actionDockWidget->setToolTip(Tooltip());
    mToolButton->setDefaultAction(actionDockWidget);
    this->connect(mToolButton, SIGNAL(toggled(bool)), this, SLOT(toggled(bool)));

    // Only Support appoint Events
    //supportsEvent("EventKey");
    registerHandlers();
    return true;
}

bool DockWidgetPlugin::UnInitialize()
{
    if( mToolButton!=Q_NULLPTR )
        delete mToolButton;
    mToolButton = Q_NULLPTR;

    unregisterHandlers();
    hide();
    return true;
}

bool DockWidgetPlugin::SetBuddy(x3::IObject* val)
{
    if( m_spBuddy==val )
        return true;

    m_spBuddy = val;
    if( !m_spBuddy.valid() )
    {
        mToolButton->setEnabled(false);
        return false;
    }

    mToolButton->setEnabled(true);

    return true;
}

bool DockWidgetPlugin::readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->readConfig(node, document, errorMessage) )
        return false;

    return true;
}

bool DockWidgetPlugin::writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->writeConfig(node, document, errorMessage) )
        return false;

    return true;
}

// IUICommand
QWidget* DockWidgetPlugin::getButtonWidget()
{
    return mToolButton;
}

QWidget* DockWidgetPlugin::getWndWidget()
{
    show();
    return this;
}

// IAnythingEventObserver
bool DockWidgetPlugin::OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam)
{
    //if( _stricmp(eventKey.c_str(), "EventKey")==0 )
    //{
    //}
    return true;
}

void DockWidgetPlugin::toggled(bool checked)
{
    if( checked )
    {
        setVisible(true);
        raise();
    }
}
