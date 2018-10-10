#include "toolplugin.h"
#include <QObject>
#include <QApplication>
#include <QFileInfo>
#include <QAction>
#include <QMessageBox>

ToolPlugin::ToolPlugin(QObject *parent) : QObject(parent)
{
    Name(QStringLiteral("ToolPlugin"));
    Caption(QStringLiteral("Buttons"));
    Category(QStringLiteral("Plugins"));
    Tooltip(QStringLiteral("ToolPlugin"));
    Description(QStringLiteral("ToolPlugin"));
    BitmapName(QStringLiteral("ToolPlugin"));


    mToolButton = Q_NULLPTR;
    mDefaultIcon = true;

}

ToolPlugin::~ToolPlugin()
{
    UnInitialize();
}

// IUIPlugin
bool ToolPlugin::Initialize()
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

    mToolButton->setCheckable(true);
    mToolButton->setEnabled(false);
    this->connect(mToolButton, SIGNAL(clicked(bool)), this, SLOT(clicked(bool)));

    // Only Support appoint Events
    //supportsEvent("EventKey");
    registerHandlers();
    return true;
}

bool ToolPlugin::UnInitialize()
{
    if( mToolButton!=Q_NULLPTR )
        delete mToolButton;
    mToolButton = Q_NULLPTR;

    unregisterHandlers();
    return true;
}

bool ToolPlugin::SetBuddy(x3::IObject* val)
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

bool ToolPlugin::readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->readConfig(node, document, errorMessage) )
        return false;

    return true;
}

bool ToolPlugin::writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
{
    if( !((IUIPlugin*)this)->writeConfig(node, document, errorMessage) )
        return false;

    return true;
}

// IUICommand
QWidget* ToolPlugin::getButtonWidget()
{
    return mToolButton;
}

QWidget* ToolPlugin::getWndWidget()
{
    return Q_NULLPTR;
}

// IAnythingEventObserver
bool ToolPlugin::OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam)
{
    if( _stricmp(eventKey.c_str(), "toolActived")==0 )
    {
        if( sender==(IUIPlugin*)this )
            return true;
    }
    return true;
}

void ToolPlugin::clicked(bool checked)
{
    QMessageBox::information(Q_NULLPTR, "ToolPlugin", checked ? "ToolPlugin clicked" : "ToolPlugin unclicked");
}
