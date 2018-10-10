%{Cpp:LicenseTemplate}\
#include "%{HdrFileName}"
#include <QObject>
@if '%{IncludeIUICommand}' || '%{IncludeIUITool}'
#include <QApplication>
#include <QFileInfo>
#include <QAction>
@endif

@if '%{Base}' === 'QObject'
%{CN}::%{CN}(QObject *parent) : QObject(parent)
@elsif '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QDockWidget' || '%{Base}' === 'QTableWidget'
%{CN}::%{CN}(QWidget *parent) : %{Base}(parent)
@else
%{CN}::%{CN}()
@endif
{
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	Name(QStringLiteral("%{PluginName}"));
	Caption(QStringLiteral("%{PluginCaption}"));
	Category(QStringLiteral("%{PluginCategory}"));
	Tooltip(QStringLiteral("%{PluginTooltip}"));
	Description(QStringLiteral("%{PluginDescription}"));
	BitmapName(QStringLiteral("%{PluginBitmapName}"));

@if '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QDockWidget' || '%{Base}' === 'QTableWidget'
	setWindowTitle(Name());
@endif
	
@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
	mToolButton = Q_NULLPTR;
	mDefaultIcon = true;
	
@if '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QTableWidget'
	hide();
@endif
@endif	
@endif
}

%{CN}::~%{CN}()
{
@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	UnInitialize();
@endif	
}

@if '%{IncludeIUIView}' || '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	// IUIPlugin
    bool %{CN}::Initialize()
	{		
@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
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
@if '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QDockWidget' || '%{Base}' === 'QTableWidget'
			setWindowIcon(icon);
@endif
		}
		
@if '%{IncludeIUITool}'
		mToolButton->setCheckable(true);
        mToolButton->setEnabled(false);
		this->connect(mToolButton, SIGNAL(clicked(bool)), this, SLOT(clicked(bool)));
@else
@if '%{Base}' === 'QDockWidget'
		mToolButton->setCheckable(true);
		QAction* actionDockWidget = toggleViewAction();
		actionDockWidget->setIcon(icon);
		actionDockWidget->setText(Name());
		actionDockWidget->setToolTip(Tooltip());
		mToolButton->setDefaultAction(actionDockWidget);
		this->connect(mToolButton, SIGNAL(toggled(bool)), this, SLOT(toggled(bool)));	
@else
		mToolButton->setCheckable(false);
		this->connect(mToolButton, SIGNAL(clicked()), this, SLOT(clicked()));
@endif	
@endif
@endif
	
@if '%{IncludeIUIEvent}'
		// Only Support appoint Events
		//supportsEvent("EventKey");
		registerHandlers();
@endif	
		return true;
	}
		
    bool %{CN}::UnInitialize()
	{
@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')		
		if( mToolButton!=Q_NULLPTR )
			delete mToolButton;
		mToolButton = Q_NULLPTR;
@endif

@if '%{IncludeIUIEvent}'
		unregisterHandlers();
@endif		
@if '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QDockWidget' || '%{Base}' === 'QTableWidget'
		hide();
@endif			
		return true;
	}
	
    bool %{CN}::SetBuddy(x3::IObject* val)
	{
		if( m_spBuddy==val )
			return true;
		
		m_spBuddy = val;
		if( !m_spBuddy.valid() )
		{
@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
			mToolButton->setEnabled(false);
@endif
			return false;
		}
		
@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
		mToolButton->setEnabled(true);
@endif		
		
		return true;
	}
	
	bool %{CN}::readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
	{
		if( !((IUIPlugin*)this)->readConfig(node, document, errorMessage) )
			return false;
		
		return true;
	}
	
	bool %{CN}::writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
	{
		if( !((IUIPlugin*)this)->writeConfig(node, document, errorMessage) )
			return false;
		
		return true;
	}
@if '%{IncludeIUIView}'
	
	// IUIView
	QWidget* %{CN}::getViewWidget()
	{
@if '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QDockWidget' || '%{Base}' === 'QTableWidget'
		return this;
@else
		return Q_NULLPTR;
@endif
	}
@else
@if '%{IncludeIUICommand}' || '%{IncludeIUITool}'
	
	// IUICommand
    QWidget* %{CN}::getButtonWidget()
	{
		return mToolButton;
	}
	
    QWidget* %{CN}::getWndWidget()
	{
@if '%{Base}' === 'QWidget' || '%{Base}' === 'QMainWindow' || '%{Base}' === 'QDockWidget' || '%{Base}' === 'QTableWidget'
		show();
		return this;
@else
		return Q_NULLPTR;
@endif		
	}
@endif
@endif
@endif
@if '%{IncludeIUIEvent}'
	
	// IAnythingEventObserver
	bool %{CN}::OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam)
	{		
@if '%{IncludeIUIView}' === '' && '%{IncludeIUITool}'
		if( _stricmp(eventKey.c_str(), "toolActived")==0 )
		{
			if( sender==(IUIPlugin*)this )
				return true;			
		}
@else		
		//if( _stricmp(eventKey.c_str(), "EventKey")==0 )
		//{       
		//}
@endif		
		return true;
	}
@endif

@if '%{IncludeIUIView}' === '' && ('%{IncludeIUICommand}' || '%{IncludeIUITool}')
@if '%{IncludeIUITool}'
        void %{CN}::clicked(bool checked)
	{
	}
@else
@if '%{Base}' === 'QDockWidget'
	void %{CN}::toggled(bool checked)
	{
	    if( checked )
	    {
		setVisible(true);
		raise();
	    }		
	}
@else
	void %{CN}::clicked()
	{
	}
@endif	
@endif
@endif
%{JS: Cpp.closeNamespaces('%{Class}')}\
