#include "module/plugininc.h"
#include "module/pluginimpl.h"
#include "module/modulemacro.h"
#include "observer/observerimpl.h"
#include "UICore.h"

USING_NAMESPACE_CBERSPLUGINS

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY_Singleton(CUICore)
XEND_DEFINE_MODULE_DLL()

OUTAPI bool x3InitializePlugin()
{
    return true;
}

OUTAPI void x3UninitializePlugin()
{
}
