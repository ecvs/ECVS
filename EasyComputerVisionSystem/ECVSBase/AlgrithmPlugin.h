#pragma once

/*
* AlgrithmBase.h
*
* 创建于 2015-6-9  李春峰
*
* CAlgrithmPlugin 管理插件的类
*
*/
#include <string>
using std::string;
#include <windows.h>
class CAlgrithmBase;
typedef void(__stdcall * PFUNCRUN)();
typedef string(__stdcall * PFUNCGETNAME)();
typedef HICON(__stdcall * PFUNCGETICON)();
typedef CAlgrithmBase*(__stdcall * PFUNCCREATEALGRITHM)();
class ECVS_EXPORT CAlgrithmPlugin
{
	friend class CPluginManager;
public:
	CAlgrithmPlugin(string strInnerName);
	~CAlgrithmPlugin();
	string GetAlgrithmInnerName();
	//CAlgrithmBase* CreateAlgrithm();
	//PFUNCRUN m_pFuncRun;
	PFUNCGETNAME m_pFuncGetName;
	PFUNCGETICON m_pFuncGetICon;
	PFUNCCREATEALGRITHM m_pCreateFunc;
	//PFUNCCREATEALGRITHM m_pFuncGetErrorMsg;
private:
	HMODULE  m_hModuleHandle;
	const string	 m_strData;
};

