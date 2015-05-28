#pragma once
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define  QWT_DLL
//作为DLL导出
#define  ECVS_BUILD_DLL
#include "ECVSBase.h"
