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
	virtual ~CAlgrithmBase();
	virtual void Run() = 0;  //执行算法，
	virtual string GetErrorMsg() ; // 获取算法执行错误字符串
	
	virtual const vector<CToolOutput>& GetOutput(); //获取该算法的所有输出参数
	//设置某一输入参数的值，具体怎么设置有流程控制，
	virtual bool SetInputValue(string strWitch, const CInputOutputInfo& value);
	virtual bool SetInputValue(int nIndedx, const CInputOutputInfo& value);
	//获取输入参数的文字说明，即CToolInput 的m_strInfo
	virtual vector<string> GetInputParamName();
	//获取输输出参数的文字说明，即CToolOutput 的m_strInfo
	virtual vector<string> GetOutputParamName();
protected:
	//只有输出和输入参数是对外开放的
	vector<CToolInput>  m_vectInput;  //所有的输入参数
	vector<CToolOutput> m_vectOutput;  //所有的输出参数
};

