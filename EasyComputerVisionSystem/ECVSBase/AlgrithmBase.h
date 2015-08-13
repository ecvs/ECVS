#pragma once
/*
* AlgrithmBase.h
*
* 创建于 2015-5-12  李春峰
*
* CAlgrithmBase 作为所有算法或者工具的基类，流程处理中也仅仅只需要使用该类
*
*/
#include <string >
#include <map>
#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include "ECVSBase.h"
using std::string;
class CAlgrithmBase;
using std::map;


//实现类似反射的技术，用来通过类名创建类的实例，CAlgrithmBase 具体的子类必须嵌入这两个宏，类似MFC宏的嵌入
//且必须手动实现CreateAlgrithm 方法
#define DEF_REFLECT_CLASS(class_name) public:\
	static void RegistClass();

#define IML_REFLECT_CLASS(class_name)  void class_name::RegistClass()\
{\
	CAlgrithmBase::m_mapCreatedFucn.insert(std::make_pair(#class_name, class_name::CreateAlgrithm));\
}



class ECVS_EXPORT CAlgrithmBase
{
public:
	typedef CAlgrithmBase* ( *CreateFunction)();
public:
	CAlgrithmBase();
	CAlgrithmBase(const CAlgrithmBase& rhs);
	CAlgrithmBase& operator= (const CAlgrithmBase &rhs);
	


	virtual ~CAlgrithmBase();

	virtual CAlgrithmBase* Clone() = 0; // 虚构造函数
	virtual void Run() = 0;  //执行算法
	virtual bool Set() = 0;  //设置算法,设置成功返回true， 失败返回false
	//读写函数，参数暂时未实现，等第一个算法成功实现及流程测试成功后再实现
	virtual void Read() = 0;  
	virtual void Save() = 0;
	//流程中是否需要清除该存储空间,默认都是需要的,当某各类实现为单例模式时 则返回false，比如Camera类(根据相机个数实现几个实例)
	virtual bool NeedClear()
	{
		return true;
	}
	virtual string GetErrorMsg(); // 获取算法执行错误字符串
	
	 string GetShowText(); //获取显示字符串
	 void SetShowText(string strText);//修改显示字符串
	 string GetAlgrithmName();  //获取算法名字
	 string GetAlgrithmClassName();  //获取算法的类名
	 const vector<CToolOutput*> GetOutput() ; //获取该算法的所有输出参数
	 const vector<CToolInput*> GetInput() ; //获取该算法的所有输入参数

	 const CToolInput* GetInput(string strWitch) ; //获取某指定的参数,如果不存在返回NULL
	 const CToolOutput* GetOutput(string strWitch); //获取某指定的参数,如果不存在返回NULL

	//设置某一输入参数的值，具体怎么设置有流程控制，
	 bool SetInputValue(string strWitch, const CInputOutputInfo& value) ;
	 bool SetInputValue(int nIndedx, const CInputOutputInfo& value) ;
	//获取输入参数的文字说明，即CToolInput 的m_strInfo
	 vector<string> GetInputParamName() ;
	//获取输输出参数的文字说明，即CToolOutput 的m_strInfo
	 vector<string> GetOutputParamName();
protected:
	//只有输出、输入参数，以及算法显示到界面的字符


	//为了简单，直接使用深拷贝 而不使用智能指针之类的技术
	//2015-5-13 李春峰将vector<CToolInput> vector<CToolOutput>  修改为vector<CToolInput*>  vector<CToolOutput*> 目的是节约数据交互时的时间与空间
 	vector<CToolInput*>  m_vectInput;  //所有的输入参数

	//注意，所有的Output至少含有两个参数，第一个代码执行错误代码，为整型，第二个为算法执行时间。
 	vector<CToolOutput*> m_vectOutput;  //所有的输出参数,
	string				m_strShowText;  //默认和算法名字一样
	string				m_strAlgrithmName; //算法名字，对外不开放修改 由算法自己修改 
	string				m_strClassName; //算法的类名，内部使用，用来动态创建对象



protected:
	virtual void Clone(const CAlgrithmBase& rhs); //用于复制构造函数和赋值操作符使用
	virtual void DeleteMemory(); // 删除内存



	
public:

protected:
	static map<string, CreateFunction> m_mapCreatedFucn;
public:
	static CAlgrithmBase* CreateAlgrithm(string strClassName);
};

