// dllmain.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "FilterCommon.h"
#include "BilateralFilter.h"
BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
	)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CBilateralFilter::RegistClass();
		break;
	case  DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	return true;
}