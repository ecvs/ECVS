#include "ECVSBase.h"
#include "PluginManager.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
using std::string;
CPluginManager::CPluginManager()
{
	char szFilePath[MAX_PATH + 1];
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, TEXT('\\')))[1] = 0;//删除文件名，只获得路径字串
	string strPath = szFilePath;
	string basePath = strPath + "plugins\\";
	strPath += "plugins\\*.dll";
	//
	WIN32_FIND_DATAA FindData;
	HANDLE hError = FindFirstFileA(strPath.c_str(), &FindData);
	if (hError != INVALID_HANDLE_VALUE)
	{
		
		do {
			CAlgrithmPlugin * plugin = new CAlgrithmPlugin(FindData.cFileName);
			string p = (basePath + FindData.cFileName);
			plugin->m_hModuleHandle = LoadLibraryA(p.c_str());
			if (plugin->m_hModuleHandle != NULL)
			{
				plugin->m_pFuncGetName = (PFUNCGETNAME)GetProcAddress(plugin->m_hModuleHandle, "GetName");
				if (plugin->m_pFuncGetName == NULL)
				{
					//没有GetName 函数
					FreeLibrary(plugin->m_hModuleHandle);
					delete plugin;
					continue;
				}
				plugin->m_pCreateFunc = (PFUNCCREATEALGRITHM)GetProcAddress(plugin->m_hModuleHandle, "CreateAlgrithm");

				if (plugin->m_pCreateFunc == NULL)
				{
					//没有CreateAlgrithm 函数
					FreeLibrary(plugin->m_hModuleHandle);
					delete plugin;
					continue;
				}

				plugin->m_pFuncGetICon = (PFUNCGETICON)GetProcAddress(plugin->m_hModuleHandle, "GetIcon");

				if (plugin->m_pFuncGetICon == NULL)
				{
					//没有GetIcon 函数
					FreeLibrary(plugin->m_hModuleHandle);
					delete plugin;
					continue;
				}

				//全部OK
				m_pPlugins.push_back(plugin);
				m_algrithmName.push_back(plugin->m_pFuncGetName());
				m_algrithmInnerName.push_back(plugin->m_strData);
			}

		} while (::FindNextFileA(hError, &FindData));
	}


}


CPluginManager::~CPluginManager()
{
	for (int i = 0; i < m_pPlugins.size(); ++i)
	{
		FreeLibrary(m_pPlugins[i]->m_hModuleHandle);
		delete m_pPlugins[i];
	}
}

CAlgrithmBase* CPluginManager::CreateAlgrithm(string strAlgrithm)
{
	for (int i = 0; i < m_algrithmInnerName.size(); ++i)
	{
		if (strAlgrithm == m_algrithmInnerName[i])
		{
			return m_pPlugins[i]->m_pCreateFunc();
		}
	}
	return NULL;
}

vector<string> CPluginManager::GetPluginsName()
{

	return m_algrithmName;
}
vector<string> CPluginManager::GetPluginsInnerName()
{

	return m_algrithmInnerName;
}