#include "ribbonpluginmanager.h"
#include "x3py/manager/iworkpath.h"
#include "x3py/manager/x3manager.h"
#include <math.h>
#include <QToolButton>
#include <QApplication>
#include <QMdiSubWindow>
#include <QDockWidget>
#include <QVariant>

CRibbonPluginManager* CRibbonPluginManager::s_pManager = nullptr;
CRibbonPluginManager::CRibbonPluginManager(void)
{
    m_spViewer = NULL;
}

CRibbonPluginManager::~CRibbonPluginManager(void)
{
    DestroyControl();
}

CRibbonPluginManager* CRibbonPluginManager::getInstance()
{
    if( s_pManager==nullptr )
        s_pManager = new CRibbonPluginManager();
    return s_pManager;
}

void CRibbonPluginManager::Destroy()
{
    if( s_pManager!=nullptr )
        delete s_pManager;
    s_pManager = nullptr;
}

bool CRibbonPluginManager::Create(QMainWindow* pFrameWnd, QRibbonBar* pRibbonBar, QMdiArea* pMdiArea)
{
    if( !LoadPlugins() )
        return false;

    if( !CreateViews(pFrameWnd, pMdiArea) )
        return false;

    return CreateControl(pRibbonBar, pFrameWnd);
}

bool CRibbonPluginManager::CreateViews(QMainWindow* pFrameWnd, QMdiArea* pMdiArea)
{
    if( pMdiArea==nullptr )
        return false;

    x3::LockRW lockcls(m_mapView.locker);
    bool ret = false;
    if( lockcls.canRead() )
    {
        m_spViewer = nullptr;
        std::vector<x3::AnyObject>::iterator it = m_mapView.begin();
        for( ; it!=m_mapView.end(); it++ )
        {
            x3::Object<IUIPlugin> spCommon(*it);
            if( !spCommon.valid() )
                continue;

            x3::Object<IUIView> spView(spCommon);
            if( !spView.valid() )
                continue;

            spView->setMainWindow(pFrameWnd);
            qDebug("CreateView: %s\n", (*it)->getClassName());
            QWidget* pWidget = spView->getViewWidget();
            if( pWidget==nullptr )
                continue;

            QMdiSubWindow* pSubWindow = pMdiArea->addSubWindow(pWidget);
            pSubWindow->setAttribute(Qt::WA_DeleteOnClose);
            pSubWindow->setProperty("IUIPlugin", QVariant((qlonglong)(spCommon.p())));
            //pSubWindow->setWindowFlags(Qt::FramelessWindowHint);
            pSubWindow->showMaximized();
            pWidget->showMaximized();
            if( pSubWindow!=nullptr && pMdiArea->subWindowList().size()==1 )
                pMdiArea->setActiveSubWindow(pSubWindow);
            if( !m_spViewer.valid() )
                m_spViewer = spView;
            ret = true;
        }
        qDebug("CreateViews End\n");
    }

    return ret;
}

bool CRibbonPluginManager::CreateControl(QRibbonBar* pRibbonBar, QMainWindow* pFrameWnd)
{
    if( pRibbonBar==nullptr || pFrameWnd==nullptr )
        return false;

    x3::LockRW lockcls(m_mapPlugin.locker);
    bool ret = false;
    if( lockcls.canRead() )
    {
        QDockWidget* pFirstLeftDockWidget = Q_NULLPTR;
        QDockWidget* pFirstRightDockWidget = Q_NULLPTR;
        QDockWidget* pFirstTopDockWidget = Q_NULLPTR;
        QDockWidget* pFirstBottomDockWidget = Q_NULLPTR;
        hash_map<int, x3::AnyObject>::iterator it = m_mapPlugin.begin();
        for( ; it!=m_mapPlugin.end(); it++ )
        {
            x3::Object<IUIPlugin> spCommon(it->second);
            if( !spCommon.valid() )
                continue;

            qDebug("CreateControl: %s\n", it->second->getClassName());
            if( m_spViewer.valid() )
                spCommon->SetBuddy(m_spViewer.p());

            x3::Object<IUICommand> spCommand(spCommon);
            if( !spCommand.valid() )
                continue;

            AddRibbonButton(pRibbonBar, spCommon.p(), it->first);

            QWidget* pWidget = spCommand->getWndWidget();
            if( pWidget!=nullptr )
            {
                QDockWidget* pDockWidget = qobject_cast<QDockWidget*>(pWidget);
                if( pDockWidget!=Q_NULLPTR )
                {
                    bool bVisible = pDockWidget->isVisible();
                    if( pDockWidget->isAreaAllowed(Qt::LeftDockWidgetArea) )
                    {
                        if( pFirstLeftDockWidget==Q_NULLPTR )
                            pFrameWnd->addDockWidget(Qt::LeftDockWidgetArea, pDockWidget);
                        else
                            pFrameWnd->tabifyDockWidget(pFirstLeftDockWidget, pDockWidget);
                        pFirstLeftDockWidget = pDockWidget;
                    }
                    else if( pDockWidget->isAreaAllowed(Qt::RightDockWidgetArea) )
                    {
                        if( pFirstRightDockWidget==Q_NULLPTR )
                            pFrameWnd->addDockWidget(Qt::RightDockWidgetArea, pDockWidget);
                        else
                            pFrameWnd->tabifyDockWidget(pFirstRightDockWidget, pDockWidget);
                        pFirstRightDockWidget = pDockWidget;
                    }
                    else if( pDockWidget->isAreaAllowed(Qt::BottomDockWidgetArea) )
                    {
                        if( pFirstBottomDockWidget==Q_NULLPTR )
                            pFrameWnd->addDockWidget(Qt::BottomDockWidgetArea, pDockWidget);
                        else
                            pFrameWnd->tabifyDockWidget(pFirstBottomDockWidget, pDockWidget);
                        pFirstBottomDockWidget = pDockWidget;
                    }
                    else if( pDockWidget->isAreaAllowed(Qt::TopDockWidgetArea) )
                    {
                        if( pFirstTopDockWidget==Q_NULLPTR )
                            pFrameWnd->addDockWidget(Qt::TopDockWidgetArea, pDockWidget);
                        else
                            pFrameWnd->tabifyDockWidget(pFirstTopDockWidget, pDockWidget);
                        pFirstTopDockWidget = pDockWidget;
                    }
                    else
                    {
                        if( pFirstLeftDockWidget==Q_NULLPTR )
                            pFrameWnd->addDockWidget(Qt::LeftDockWidgetArea, pDockWidget);
                        else
                            pFrameWnd->tabifyDockWidget(pFirstLeftDockWidget, pDockWidget);
                        pFirstLeftDockWidget = pDockWidget;
                    }

                    if( !bVisible )
                        pDockWidget->hide();
                }
            }

            ret = true;
        }
        qDebug("CreateControl End\n");

        /*
        QRibbonPanel* pPanel = FindRibbonPanel(pRibbonBar, _T("主页"), _T("视图"));
        if( pPanel!=NULL )
        pPanel->Add(new CMFCRibbonCheckBox(ID_VIEW_STATUS_BAR, _T("状态栏")));*/
    }

    return ret;
}

bool CRibbonPluginManager::AddRibbonButton(QRibbonBar* pRibbonBar, IUIPlugin* pCommon, int id)
{
    if( pRibbonBar==nullptr || pCommon==nullptr )
        return false;

    x3::Object<IUICommand> spCommand(pCommon);
    if( !spCommand.valid() )
        return false;

    if( spCommand->getButtonWidget()==nullptr )
        return  false;

    QString strCategory = pCommon->Category();
    if( strCategory.isEmpty() )
        strCategory = QObject::tr("Custom Plugin");

    // 获取插件的标题
    QString strCaption = pCommon->Caption();
    if( strCaption.isEmpty() )
        strCaption = strCategory;

    // 根据范畴名称, 查找插件所属的QRibbonCategory
    QRibbonCategory* pCategory = FindRibbonCategory(pRibbonBar, strCategory);
    // 如果不存在该范畴,则自动创建
    if( pCategory==nullptr )
        pCategory = pRibbonBar->AddCategory(strCategory);

    if( pCommon->defaultCategory() )
        pRibbonBar->SetActiveCategory(pCategory);

    // 根据标题,查找插件所属的QRibbonPanel
    QRibbonPanel* pPanel = FindRibbonPanel(pCategory, strCaption);
    // 如果不存在,将自动创建
    if( pPanel==nullptr )
        pPanel = pCategory->addPanel(strCaption);

    pPanel->Add(spCommand->getButtonWidget());
    return true;
}

QRibbonCategory* CRibbonPluginManager::FindRibbonCategory(QRibbonBar* pRibbonBar, const QString& strCategory)
{
    if( pRibbonBar==nullptr || strCategory.isEmpty() )
        return nullptr;

    // 根据范畴名称, 查找插件所属的QRibbonCategory
    QRibbonCategory* pCategory = nullptr;
    for( int i=0; i<pRibbonBar->GetCategoryCount(); i++ )
    {
        QRibbonCategory* pTmp = pRibbonBar->GetCategory(i);
        if( pTmp==NULL )
            continue;

        if( strCategory.compare(pTmp->windowTitle(), Qt::CaseInsensitive)==0 )
        {
            pCategory = pTmp;
            break;
        }
    }

    return pCategory;
}

QRibbonPanel*  CRibbonPluginManager::FindRibbonPanel(QRibbonCategory* pCategory, const QString& strCaption)
{
    if( pCategory==nullptr || strCaption.isEmpty() )
        return nullptr;

    // 根据标题,查找插件所属的QRibbonPanel
    QRibbonPanel* pPanel = nullptr;
    for( int i=0; i<pCategory->GetPanelCount(); i++ )
    {
        QRibbonPanel* pTmp = pCategory->GetPanel(i);
        if( pTmp==nullptr )
            continue;

        if( strCaption.compare(pTmp->windowTitle(), Qt::CaseInsensitive)==0 )
        {
            pPanel = pTmp;
            break;
        }
    }

    return pPanel;
}

QRibbonPanel*  CRibbonPluginManager::FindRibbonPanel(QRibbonBar* pRibbonBar, const QString& strCategory, const QString& strCaption)
{
    if( pRibbonBar==nullptr || strCategory.isEmpty() || strCaption.isEmpty() )
        return nullptr;

    // 根据范畴名称, 查找插件所属的QRibbonCategory
    QRibbonCategory* pCategory = FindRibbonCategory(pRibbonBar, strCategory);
    if( pCategory==nullptr )
        return nullptr;

    // 根据标题,查找插件所属的QRibbonPanel
    QRibbonPanel* pPanel = FindRibbonPanel(pCategory, strCaption);
    return pPanel;
}

void CRibbonPluginManager::DestroyControl()
{
    if(m_spViewer.valid())
    {
        //x3::Object<IUIView> spViewer3D(m_spViewer);
        //if(spViewer3D.valid())
        //	spViewer3D->StopRender();
    }
    m_spViewer = NULL;
    UnloadPlugins();
}

void CRibbonPluginManager::SetViewer(x3::IObject* val)
{
    if( m_spViewer==val )
        return;

    m_spViewer = val;
    x3::LockRW lockcls(m_mapPlugin.locker);
    bool ret = false;
    if( lockcls.canRead() )
    {
        hash_map<int, x3::AnyObject>::iterator it = m_mapPlugin.begin();
        for( ; it!=m_mapPlugin.end(); it++ )
        {
            x3::Object<IUIPlugin> spCommon(it->second);
            if( !spCommon.valid() )
                continue;

            spCommon->SetBuddy(m_spViewer.p());
        }
    }
}
