#ifndef TOOLPLUGIN_H
#define TOOLPLUGIN_H
#include <QObject>
#include <QToolButton>

#include "UIPluginsEvents.h"
#include "UIPlugins.h"
USING_NAMESPACE_CBERSPLUGINS

const char* const clsidToolPlugin = "clsidToolPlugin";
class ToolPlugin : public QObject
        , public IUIPlugin
        , public IUICommand
        , public IAnythingEventObserver
{
    Q_OBJECT
    X3BEGIN_CLASS_DECLARE(ToolPlugin, clsidToolPlugin)
    X3DEFINE_INTERFACE_ENTRY(IUIPlugin)
    X3DEFINE_INTERFACE_ENTRY(IUICommand)
    X3END_CLASS_DECLARE()

    public:
        explicit ToolPlugin(QObject *parent = 0);
    ~ToolPlugin();

public:
    // IUIPlugin
    virtual bool Initialize();
    virtual bool UnInitialize();
    virtual bool SetBuddy(x3::IObject* val);
    virtual bool readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage );
    virtual bool writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage );

    // IUICommand
    virtual QWidget* getButtonWidget();
    virtual QWidget* getWndWidget();

    // IAnythingEventObserver
    virtual bool OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam);

signals:

public slots:
    void clicked(bool checked = false);

protected:
    QToolButton* mToolButton;
    bool mDefaultIcon;
};

#endif // TOOLPLUGIN_H