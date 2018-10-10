#ifndef VIEWPLUGIN_H
#define VIEWPLUGIN_H
#include <QWidget>

#include "UIPluginsEvents.h"
#include "UIPlugins.h"
USING_NAMESPACE_CBERSPLUGINS

const char* const clsidViewPlugin = "clsidViewPlugin";
class ViewPlugin : public QWidget
        , public IUIPlugin
        , public IUIView
        , public IAnythingEventObserver
{
    Q_OBJECT
    X3BEGIN_CLASS_DECLARE(ViewPlugin, clsidViewPlugin)
    X3DEFINE_INTERFACE_ENTRY(IUIPlugin)
    X3DEFINE_INTERFACE_ENTRY(IUIView)
    X3END_CLASS_DECLARE()

    public:
        explicit ViewPlugin(QWidget *parent = 0);
    ~ViewPlugin();

public:
    // IUIPlugin
    virtual bool Initialize();
    virtual bool UnInitialize();
    virtual bool SetBuddy(x3::IObject* val);
    virtual bool readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage );
    virtual bool writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage );

    // IUIView
    virtual QWidget* getViewWidget();

    // IAnythingEventObserver
    virtual bool OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam);

signals:

public slots:

};

#endif // VIEWPLUGIN_H