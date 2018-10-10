#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QStatusBar>
#include "ribbonpluginmanager.h"
#include "qribbonstylesheetmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setObjectName("QRibbonMainWindow");
    setWindowFlags( Qt::FramelessWindowHint );
    ui->setupUi(this);

    mRibbonBar = new QRibbonBar(this->centralWidget());

    mMdiArea = new QMdiArea(this->centralWidget());
    //mMdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation);
    mMdiArea->setViewMode(QMdiArea::SubWindowView);
    //mMdiArea->setViewMode(QMdiArea::TabbedView);
    mMdiArea->setTabShape(QTabWidget::Rounded);
    mMdiArea->setTabPosition(QTabWidget::North);
    connect(mMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(subWindowActivated(QMdiSubWindow *)));

    CRibbonPluginManager::getInstance()->Create(this, mRibbonBar, mMdiArea);
    setMenuWidget(mRibbonBar);
    setCentralWidget(mMdiArea);

    QRibbonStyleSheetManager::instance()->applyStyleSheet("office2007_black");
    //registerHandlers();
}

MainWindow::~MainWindow()
{
    CRibbonPluginManager::getInstance()->DestroyControl();

    if( mRibbonBar!=nullptr )
        delete mRibbonBar;
    mRibbonBar = nullptr;

    delete ui;
}

bool MainWindow::OnAnything(x3::IObject* sender, const std::string& eventKey, const QVariant& wParam, const QVariant& lParam)
{
    //if( _stricmp(eventKey.c_str(), "scaleChanged")==0 )
    //{
    //}
    return true;
}

void MainWindow::subWindowActivated(QMdiSubWindow* pSubWindow)
{
    if( pSubWindow==Q_NULLPTR )
        return;

    QVariant vtData = pSubWindow->property("IUIPlugin");
    if( !vtData.isValid() )
        return;

    x3::Object<IUIPlugin> spCommon((IUIPlugin*)(vtData.toLongLong()));
    if( !spCommon.valid() )
        return;

    CRibbonPluginManager::getInstance()->SetViewer(spCommon.p());
}
