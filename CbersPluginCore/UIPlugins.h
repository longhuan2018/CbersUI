#ifndef IPLUGIN_H
#define IPLUGIN_H
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QDomNode>
#include <QDomDocument>
#include "module/plugininc.h"
#include "objptr.h"
#include "cbersplugincore_global.h"

BEGIN_NAMESPACE_CBERSPLUGINS
const char* const clsidUICore = "clsidUICore";
class IUICore : public x3::IObject
{
    X3DEFINE_IID(IUICore);

public:
    virtual long size() = 0;
    virtual x3::IObject* Find(const char* key) = 0;
    virtual bool Add(const char* key, x3::IObject* obj) = 0;
    virtual bool Remove(const char* key) = 0;
    virtual bool Remove(x3::IObject* obj) = 0;
    virtual void clear() = 0;
};

// 插件接口, 所有插件都必须继承该接口
class IUIPlugin : public x3::IObject
{
    X3DEFINE_IID(IUIPlugin);

public:
    IUIPlugin() { m_spBuddy = NULL; m_defaultCategory = false; }

    const QString& Name() { return m_strName; }
    void Name(const QString& val) { m_strName = val; }

    const QString& Caption() { return m_strCaption; }
    void Caption(const QString& val) { m_strCaption = val; }

    const QString& Category() { return m_strCategory; }
    void Category(const QString& val) { m_strCategory = val; }

    bool defaultCategory() { return m_defaultCategory; }
    void defaultCategory(const bool val) { m_defaultCategory = val; }

    const QString& Tooltip() { return m_strTooltip; }
    void Tooltip(const QString& val) { m_strTooltip = val; }

    const QString& Description() { return m_strDescription; }
    void Description(const QString& val) { m_strDescription = val; }

    const QString& BitmapName() { return m_strBitmapName; }
    void BitmapName(const QString& val) { m_strBitmapName = val; }

    virtual bool readConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
    {
        return true;
    }

    virtual bool writeConfig( const QDomNode& node, QDomDocument & document, QString& errorMessage )
    {
        return true;
    }

    // 初始化
    virtual bool Initialize() = 0;
    // 析构
    virtual bool UnInitialize() = 0;
    virtual bool SetBuddy(x3::IObject* val) = 0;// { m_spBuddy = val; return true; }

protected:
    QString m_strName;
    QString m_strCaption;
    QString m_strCategory;
    QString m_strTooltip;
    QString m_strDescription;
    QString m_strBitmapName;
    x3::AnyObject m_spBuddy;
    bool         m_defaultCategory;
};

// 视图插件
class IUIView : public x3::IObject
{
    X3DEFINE_IID(IUIView);

public:
    IUIView() { mMainWindow = nullptr; }

    virtual QWidget* getViewWidget() = 0;
    virtual void setMainWindow(QMainWindow* win) { mMainWindow = win; }
    virtual QMainWindow* mainWindow() { return mMainWindow; }

protected:
    QMainWindow* mMainWindow;
};

// 按钮插件
class IUICommand : public x3::IObject
{
    X3DEFINE_IID(IUICommand);

public:
    virtual QWidget* getButtonWidget() { return 0; }
    virtual QWidget* getWndWidget() { return 0; }
};


END_NAMESPACE_CBERSPLUGINS
#endif // IPLUGIN_H
