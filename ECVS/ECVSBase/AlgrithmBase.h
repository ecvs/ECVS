#pragma once
/*
* AlgrithmBase.h
*
* 创建于 2015-5-12  李春峰
*
* CAlgrithmBase 作为所有算法或者工具的基类，流程处理中也仅仅只需要使用该类
*
*/

class ECVS_EXPORT CAlgrithmBase
{
public:
	CAlgrithmBase();
	CAlgrithmBase(const CAlgrithmBase& rhs);
	CAlgrithmBase& operator= (const CAlgrithmBase &rhs);



	virtual ~CAlgrithmBase();
	virtual void Run() = 0;  //执行算法，
	virtual string GetErrorMsg() = 0; // 获取算法执行错误字符串
	
	 string GetShowText(); //获取显示字符串
	 void SetShowText(string strText);//修改显示字符串
	 string GetAlgrithmName();  //获取算法名字

	 const vector<CToolOutput*> GetOutput() ; //获取该算法的所有输出参数
	 const vector<CToolInput*> GetInput() ; //获取该算法的所有输入参数

	 const CToolInput* GetInput(string strWitch) ; //获取某指定的参数,如果不存在返回NULL
	 const CToolOutput* GetOutput(string strWitch); //获取某指定的参数,如果不存在返回NULL

	//设置某一输入参数的值，具体怎么设置有流程控制，
	 bool SetInputValue(string strWitch, const CInputOutputInfo& value) ;
	 bool SetInputValue(int nIndedx, const CInputOutputInfo& value) ;
	//获取输入参数的文字说明，即CToolInput 的m_strInfo
	virtual vector<string> GetInputParamName() = 0;
	//获取输输出参数的文字说明，即CToolOutput 的m_strInfo
	virtual vector<string> GetOutputParamName() = 0;
protected:
	//只有输出、输入参数，以及算法显示到界面的字符


	//为了简单，直接使用深拷贝 而不使用智能指针之类的技术
	//2015-5-13 李春峰将vector<CToolInput> vector<CToolOutput>  修改为vector<CToolInput*>  vector<CToolOutput*> 目的是节约数据交互时的时间与空间
 	vector<CToolInput*>  m_vectInput;  //所有的输入参数

	//注意，所有的Output至少含有两个参数，第一个代码执行错误代码，为整型，第二个为算法执行时间。
 	vector<CToolOutput*> m_vectOutput;  //所有的输出参数,
	string				m_strShowText;  //默认和算法名字一样
	string				m_strAlgrithmName; //算法名字，对外不开放修改 由算法自己修改 


protected:
	virtual void Clone(const CAlgrithmBase& rhs); //用于复制构造函数和赋值操作符使用
	virtual void DeleteMemory(); // 删除内存
};

