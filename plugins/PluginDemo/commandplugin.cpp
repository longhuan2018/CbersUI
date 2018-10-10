#include "commandplugin.h"
#include <QObject>
#include <QApplication>
#include <QFileInfo>
#include <QAction>
#include <QMessageBox>

CommandPlugin::CommandPlugin(QObject *parent) : QObject(parent)
{
    Name(QStringLiteral("CommandPlugin"));
    Caption(QStringLiteral("Buttons"));
    Category(QStringLiteral("Plugins"));
    Tooltip(QStringLiteral("CommandPlugin"));
    Description(QStringLiteral("CommandPlugin"));
    BitmapName(QStringLiteral("CommandPlugin"));


    mToolButton = Q_NULLPTR;
    mDefaultIcon = true;

}

CommandPlugin::~CommandPlugin()
{
    UnInitialize();
}

// IUIPlugin
bool CommandPlugin::Initialize()
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
    }

    mToolButton->setCheckable(false);
    this->connect(mToolButton, SIGNAL(clicked()), this, SLOT(clicked()));

    // Only Support appoint Events
    //supportsEvent("EventKey");
    registerHandlers();
    return true;
}

bool CommandPlugin::UnInitialize()
{
    if( mToolButton!=Q_NULLPTR )
        delete mToolButton;
    mToolButton = Q_NULLPTR;

    unregisterHandlers();
    return true;
}

bool CommandPlugin::SetBuddy(x3::IObject* val)
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

bool CommandPlugin::readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->readConfig(node, document, errorMessage) )
        return false;

    return true;
}

bool CommandPlugin::writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->writeConfig(node, document, errorMessage) )
        return false;

    return true;
}

// IUICommand
QWidget* CommandPlugin::getButtonWidget()
{
    return mToolButton;
}

QWidget* CommandPlugin::getWndWidget()
{
    return Q_NULLPTR;
}

// IAnythingEventObserver
bool CommandPlugin::OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam)
{
    //if( _stricmp(eventKey.c_str(), "EventKey")==0 )
    //{
    //}
    return true;
}

void CommandPlugin::clicked()
{
    QMessageBox::information(Q_NULLPTR, "CommandPlugin", "CommandPlugin clicked");
}
