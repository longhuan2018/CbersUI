#ifndef RIBBONPLUGINMANAGER_H
#define RIBBONPLUGINMANAGER_H
#include "pluginmanager.h"
#include "qribbonbar.h"
USING_NAMESPACE_CBERSUI

#include <QMdiArea>
#include <QMainWindow>
#include <QToolButton>

class CRibbonPluginManager : public CPluginManager
{
public:
    CRibbonPluginManager();
    ~CRibbonPluginManager(void);

public:
    static CRibbonPluginManager* getInstance();
    static void Destroy();

private:
    static CRibbonPluginManager* s_pManager;

public:
    bool Create(QMainWindow* pFrameWnd, QRibbonBar* pRibbonBar, QMdiArea* pMdiArea);
    bool CreateViews(QMainWindow* pFrameWnd, QMdiArea* pMdiArea);
    bool CreateControl(QRibbonBar* pRibbonBar, QMainWindow* pFrameWnd);
    void SetViewer(x3::IObject* val);
    void DestroyControl();

protected:
    bool AddRibbonButton(QRibbonBar* pRibbonBar, IUIPlugin* pCommon, int id);
    QRibbonCategory* FindRibbonCategory(QRibbonBar* pRibbonBar, const QString& lpszCategory);
    QRibbonPanel*  FindRibbonPanel(QRibbonCategory* pCategory, const QString& lpszCaption);
    QRibbonPanel*  FindRibbonPanel(QRibbonBar* pRibbonBar, const QString& lpszCategory, const QString& lpszCaption);

protected:
    x3::AnyObject m_spViewer;
};

#endif // RIBBONPLUGINMANAGER_H
