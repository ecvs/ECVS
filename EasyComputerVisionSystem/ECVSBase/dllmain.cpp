#include "ECVSBase.h"
#include "PluginManager.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
using std::string;
#include <windows.h>
#include "PluginManager.h"
CPluginManager pluginManager;
BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
	)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	
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


CPluginManager* GetPlugins()
{
	return &pluginManager;
}