#define  ECVS_BUILD_DLL

#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"

#include <vector>
using std::vector;
#include "AlgrithmBase.h"


CAlgrithmBase::CAlgrithmBase()
{
	//至少有两个输出 一个是错误代码 一个是处理时间

	CToolOutput *pErrorCode = new CToolOutput(DataType::TYPE_INT); //错误代码
	CInputOutputInfo err(DataType::TYPE_INT);
	err.SetIntValue(ECVS_ERR_HAS_NO_EXECUTE);  //初始化为未执行。
	pErrorCode->SetValue(err);
	pErrorCode->SetStringInfo("错误代码");
	m_vectOutput.push_back(pErrorCode);
	//初始化时间为0
	CInputOutputInfo ti(DataType::TYPE_DOUBLE);
	ti.SetDoubleValue(0);

	CToolOutput* pProcessTime = new CToolOutput(DataType::TYPE_DOUBLE);
	pProcessTime->SetStringInfo("处理时间");
	pProcessTime->SetValue(ti);
	m_vectOutput.push_back(pProcessTime);

}


CAlgrithmBase::~CAlgrithmBase()
{
	DeleteMemory();
}

string CAlgrithmBase::GetShowText() //获取显示字符串
{
	return m_strShowText;
}
void CAlgrithmBase::SetShowText(string strText)//修改显示字符串
{
	m_strShowText = strText;
}
string CAlgrithmBase::GetAlgrithmName()  //获取算法名字
{
	return m_strAlgrithmName;
}
const CToolInput* CAlgrithmBase::GetInput(string strWitch)
{
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		if (m_vectInput[i]->GetStringInfo() == strWitch)
		{
			return m_vectInput[i];
		}
	}
	return NULL;
	
}
const CToolOutput* CAlgrithmBase::GetOutput(string strWitch)
{
	for (int i = 0; i < m_vectOutput.size(); ++i)
	{
		if (m_vectOutput[i]->GetStringInfo() == strWitch)
		{
			return m_vectOutput[i];
		}
	}
	return NULL;
}

const vector<CToolOutput*> CAlgrithmBase::GetOutput() //获取该算法的所有输出参数
{
	return m_vectOutput;
}
const vector<CToolInput*> CAlgrithmBase::GetInput() //获取该算法的所有输入参数
{
	return m_vectInput;
}

bool CAlgrithmBase::SetInputValue(string strWitch, const CInputOutputInfo& value)
{
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		if (m_vectInput[i]->GetStringInfo() == strWitch)
		{
			return m_vectInput[i]->SetValue(value);
			
		}
	}
	return false;
}
bool CAlgrithmBase::SetInputValue(int nIndedx, const CInputOutputInfo& value)
{
	if (nIndedx >= m_vectInput.size())
	{
		return false;
	}
	return m_vectInput[nIndedx]->SetValue(value);
}
CAlgrithmBase::CAlgrithmBase(const CAlgrithmBase& rhs)
{
	Clone(rhs);
}
CAlgrithmBase& CAlgrithmBase::operator= (const CAlgrithmBase &rhs)
{

	if (this != &rhs)
	{
		Clone(rhs);
	}
	

	return *this;
}
//用于复制构造函数和赋值操作符使用,实现拷贝所有成员变量
void CAlgrithmBase::Clone(const CAlgrithmBase& rhs)
{
	DeleteMemory();
	for (int i = 0; i < rhs.m_vectInput.size(); ++i)
	{
		CToolInput *pInput = new CToolInput(*rhs.m_vectInput[i]);
		m_vectInput.push_back(pInput);
	}
	for (int i = 0; i < rhs.m_vectOutput.size(); ++i)
	{
		CToolOutput* pOutput = new CToolOutput(*rhs.m_vectOutput[i]);
		m_vectOutput.push_back(pOutput);
	}
	m_strAlgrithmName = rhs.m_strAlgrithmName;
	m_strShowText = rhs.m_strShowText;
}
void CAlgrithmBase::DeleteMemory() // 删除内存
{
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		delete m_vectInput[i];
		m_vectInput[i] = NULL;
	}
	m_vectInput.clear();

	for (int i = 0; i < m_vectOutput.size(); ++i)
	{
		delete m_vectOutput[i];
		m_vectOutput[i] = NULL;
	}
	m_vectOutput.clear();
	
}


//获取输入参数的文字说明，即CToolInput 的m_strInfo
vector<string> CAlgrithmBase::GetInputParamName()
{
	vector<string> inputVec;
	for (int i = 0; i < m_vectInput.size(); ++i)
	{
		inputVec.push_back(m_vectInput[i]->GetStringInfo());
	}
	
	return inputVec;
}
//获取输输出参数的文字说明，即CToolOutput 的m_strInfo
vector<string> CAlgrithmBase::GetOutputParamName()
{
	vector<string> outVec;
	for (int i = 0; i < m_vectOutput.size(); ++i)
	{
		outVec.push_back(m_vectOutput[i]->GetStringInfo());
	}
	return outVec;
	
}

//默认获取错误操作
string CAlgrithmBase::GetErrorMsg()
{
	const CInputOutputInfo & info = m_vectOutput[0]->GetValue();
	int nErr = 0;
	info.GetIntValue(nErr);
	return ::GetErrorMsg(nErr);
}