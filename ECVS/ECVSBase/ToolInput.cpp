
/*
* ToolInput.h
*
* 创建于 2015-5-12  李春峰
*
* 实现CToolInput
*
*/
#define  ECVS_BUILD_DLL
#include "ToolInput.h"

CToolInput::CToolInput(DataType dataType, string strInfo /*= ""*/) :m_Value(dataType), m_strInfo(strInfo)
{
}

CToolInput::CToolInput(const CToolInput &rhs) : m_Value(rhs.m_Value), m_strInfo(rhs.m_strInfo)
{

}


CToolInput& CToolInput::operator = (const CToolInput& rhs)
{
	if (this != &rhs)
	{
		m_strInfo = rhs.m_strInfo; 
		m_Value = rhs.m_Value;
	}
	return *this;
}

CToolInput::~CToolInput()
{
}


//设置值
bool CToolInput::SetInputValue(const CInputOutputInfo&rhs)
{

	//类型一但确定好就不能更改
	if (rhs.GetDataType() == m_Value.GetDataType())
	{
		this->m_Value = rhs;
		return true;
	}
	return false;

}

const CInputOutputInfo& CToolInput::GetValue()
{
	return m_Value;
}
//设置和获取说明文字
void CToolInput::SetStringInfo(string strInfo)
{
	m_strInfo = strInfo;
}
string CToolInput::GetStringInfo()
{
	return m_strInfo;
}
