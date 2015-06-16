#pragma once
#include "AlgrithmPlugin.h"
#include <vector>
#include <string>
using std::vector;
using std::string;
/*
* AlgrithmBase.h
*
* 创建于 2015-6-9  李春峰
*
* CPluginManager 管理所有的插件，包括装载插件，和卸载插件
*
*/

// extern "C" __declspec(dllexport) HICON GetIcon(); //用于显示的图标;
// extern "C" __declspec(dllexport) const char* GetName();//获取名字
// extern "C" __declspec(dllexport) CAlgrithmBase* CreateAlgrithm();//创建算法


// 
// extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam);

class ECVS_EXPORT CPluginManager
{
	
public:
	CPluginManager();
	~CPluginManager();
	vector<string> GetPluginsName();
	vector<string> GetPluginsInnerName();
	CAlgrithmBase* CreateAlgrithm(string strAlgrithm);

private:
	vector<CAlgrithmPlugin*> m_pPlugins;
	vector<string>		m_algrithmName;
	vector<string>		m_algrithmInnerName;
};

