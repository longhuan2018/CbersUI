#ifndef CPLUGINMANAGER_H
#define CPLUGINMANAGER_H
#include "x3py/module/plugininc.h"
#include "x3py/objptr.h"
#include "x3py/utilfunc/lockrw.h"
#include "UIPlugins.h"
USING_NAMESPACE_CBERSPLUGINS

#include <map>
#include <vector>

#define hash_multimap std::multimap
#define hash_map std::map

class CPluginManager
{
public:
    CPluginManager();
    ~CPluginManager(void);

public:
    static bool Initialize(const char* folder = "plugins");
    static bool UnInitialize();

public:
    bool LoadPlugins();
    bool UnloadPlugins();
    int  GetPluginCount();
    bool GetPlugin(int index, int& id, IUIPlugin** ppICommon);
    IUIPlugin* FindPlugin(int id);

    int  GetViewPluginCount();
    bool GetViewPlugin(int index, IUIView** ppIView);

protected:
    int  GetNextID();
    void FreeID(int id);

public:
    static int MINID;
    static int MAXID;

protected:
    x3::LockRW_<hash_map<int, x3::AnyObject>> m_mapPlugin;
    x3::LockRW_<std::vector<x3::AnyObject>> m_mapView;
    x3::LockRW_<std::vector<int>> m_mapIdleID;
    int m_nNextID;
    int m_nLastTool;
};

#endif // CPLUGINMANAGER_H
