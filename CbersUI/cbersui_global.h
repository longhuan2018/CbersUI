#ifndef CBERSUI_GLOBAL_H
#define CBERSUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CBERSUI_LIBRARY)
#  define CBERSUI_EXPORT Q_DECL_EXPORT
#else
#  define CBERSUI_EXPORT Q_DECL_IMPORT
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#define BEGIN_NAMESPACE_CBERSUI  namespace Cbers { namespace UI {
#define END_NAMESPACE_CBERSUI   } }
#define USING_NAMESPACE_CBERSUI  using namespace Cbers::UI;
#else
#define BEGIN_NAMESPACE_CBERSUI
#define END_NAMESPACE_CBERSUI
#define USING_NAMESPACE_CBERSUI
#endif

#endif // CBERSUI_GLOBAL_H
