#ifndef DOCKWIDGETPLUGIN_H
#define DOCKWIDGETPLUGIN_H
#include <QDockWidget>
#include <QToolButton>

#include "UIPluginsEvents.h"
#include "UIPlugins.h"
USING_NAMESPACE_CBERSPLUGINS

const char* const clsidDockWidgetPlugin = "clsidDockWidgetPlugin";
class DockWidgetPlugin : public QDockWidget
        , public IUIPlugin
        , public IUICommand
        , public IAnythingEventObserver
{
    Q_OBJECT
    X3BEGIN_CLASS_DECLARE(DockWidgetPlugin, clsidDockWidgetPlugin)
    X3DEFINE_INTERFACE_ENTRY(IUIPlugin)
    X3DEFINE_INTERFACE_ENTRY(IUICommand)
    X3END_CLASS_DECLARE()

    public:
        explicit DockWidgetPlugin(QWidget *parent = 0);
    ~DockWidgetPlugin();

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
    void toggled(bool checked);

protected:
    QToolButton* mToolButton;
    bool mDefaultIcon;
};

#endif // DOCKWIDGETPLUGIN_H
