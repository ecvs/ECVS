/*
* ToolInput.h
*
* 创建于 2015-5-12  李春峰
*
* 实现CToolOutput
*
*/
#define  ECVS_BUILD_DLL
#include "ToolOutput.h"


CToolOutput::CToolOutput(DataType dataType, string strInfo = "") :m_Value(dataType), m_strInfo(strInfo)
{
}

CToolOutput::CToolOutput(const CToolOutput &rhs) : m_Value(rhs.m_Value), m_strInfo(rhs.m_strInfo)
{

}

CToolOutput::~CToolOutput()
{
}



//设置值
bool CToolOutput::SetInputValue(const CInputOutputInfo&rhs)
{

	//类型一但确定好就不能更改
	if (rhs.GetDataType() == m_Value.GetDataType())
	{
		this->m_Value = rhs;
		return true;
	}
	return false;

}

const CInputOutputInfo& CToolOutput::GetValue()
{
	return m_Value;
}
//设置和获取说明文字
void CToolOutput::SetStringInfo(string strInfo)
{
	m_strInfo = strInfo;
}
string CToolOutput::GetStringInfo()
{
	return m_strInfo;
}
