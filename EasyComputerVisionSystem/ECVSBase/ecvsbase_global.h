#ifndef ECVSBASE_GLOBAL_H
#define ECVSBASE_GLOBAL_H
#define  ECVS_BUILD_DLL
#include <QtCore/qglobal.h>

#ifdef ECVSBASE_LIB
# define ECVSBASE_EXPORT Q_DECL_EXPORT
#else
# define ECVSBASE_EXPORT Q_DECL_IMPORT
#endif

#endif // ECVSBASE_GLOBAL_H
