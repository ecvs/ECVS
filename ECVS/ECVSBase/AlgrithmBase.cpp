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
}


CAlgrithmBase::~CAlgrithmBase()
{
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


const vector<CToolOutput*> CAlgrithmBase::GetOutput() //获取该算法的所有输出参数
{
	return m_vectOutput;
}
const vector<CToolInput*> CAlgrithmBase::GetInput() //获取该算法的所有输入参数
{
	return m_vectInput;
}