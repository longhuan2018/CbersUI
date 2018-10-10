%{Cpp:LicenseTemplate}\
#ifndef %{GUARD}
#define %{GUARD}
@if '%{Base}'
#include <%{Base}>
@endif
@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
#include <QToolButton>
@endif

@if '%{IncludeIUIEvent}'
#include "UIPluginsEvents.h"
@endif
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
#include "UIPlugins.h"
USING_NAMESPACE_CBERSPLUGINS
@else
@if '%{IncludeIUIEvent}'
USING_NAMESPACE_CBERSPLUGINS
@endif
@endif
%{JS: Cpp.openNamespaces('%{Class}')}
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
const char* const clsid%{CN} = "clsid%{CN}";
@endif
@if '%{Base}'
class %{CN} : public %{Base}
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	, public IUIPlugin
@if '%{IncludeIUIView}'
	, public IUIView
@else
@if '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	, public IUICommand
@endif
@endif	
@endif
@if '%{IncludeIUIEvent}'
	, public IAnythingEventObserver
@endif
@else
class %{CN}
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	: public IUIPlugin
@if '%{IncludeIUIView}'
	, public IUIView
@else	
@if '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	, public IUICommand
@endif
@endif
@if '%{IncludeIUIEvent}'
	, public IAnythingEventObserver
@endif
@else
@if '%{IncludeIUIEvent}'
	: public IAnythingEventObserver
@endif	
@endif
@endif
{
@if %{isQObject}
     Q_OBJECT
@endif
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
     X3BEGIN_CLASS_DECLARE(%{CN}, clsid%{CN})
          X3DEFINE_INTERFACE_ENTRY(IUIPlugin)
@if '%{IncludeIUIView}'
          X3DEFINE_INTERFACE_ENTRY(IUIView)
@else
@if '%{IncludeIUICommand}' || '%{IncludeIUITool}'
          X3DEFINE_INTERFACE_ENTRY(IUICommand)
@endif
@endif
     X3END_CLASS_DECLARE()
@endif	
	
public:
@if '%{Base}' === 'QObject'
    explicit %{CN}(QObject *parent = 0);
@elsif '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QDockWidget' || '%{Base}' === 'QTableWidget'
    explicit %{CN}(QWidget *parent = 0);
@else
    %{CN}();	
@endif
	~%{CN}();

public:
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	// IUIPlugin
    virtual bool Initialize();
    virtual bool UnInitialize();
    virtual bool SetBuddy(x3::IObject* val);
	virtual bool readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage );
	virtual bool writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage );
@if '%{IncludeIUIView}'
	
	// IUIView
    virtual QWidget* getViewWidget();
@else
@if '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	
	// IUICommand
    virtual QWidget* getButtonWidget();
    virtual QWidget* getWndWidget();
@endif
@endif
@endif
@if '%{IncludeIUIEvent}'
	
	// IAnythingEventObserver
	virtual bool OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam);
@endif	

@if %{isQObject}
signals:

public slots:
@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
@if '%{IncludeIUITool}'
        void clicked(bool checked = false);
@else
@if '%{Base}' === 'QDockWidget'
	void toggled(bool checked);
@else
	void clicked();
@endif
@endif
@endif
@endif

@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
protected:
	QToolButton* mToolButton;
	bool mDefaultIcon;
@endif
};
%{JS: Cpp.closeNamespaces('%{Class}')}
#endif // %{GUARD}\
