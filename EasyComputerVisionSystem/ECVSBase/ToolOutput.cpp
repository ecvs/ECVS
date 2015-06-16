/*
* ToolInput.h
*
* 创建于 2015-5-12  李春峰
*
* 实现CToolOutput
*
*/
#include "stdafx.h"
#include "ToolOutput.h"

#include "ToolInput.h"
CToolOutput::CToolOutput(DataType dataType, string strInfo/* = ""*/) :m_Value(dataType), m_strInfo(strInfo)
{
}

CToolOutput::CToolOutput(const CToolOutput &rhs) : m_Value(rhs.m_Value), m_strInfo(rhs.m_strInfo)
{

}

CToolOutput::~CToolOutput()
{
}



//设置值
bool CToolOutput::SetValue(const CInputOutputInfo&rhs)
{

	//类型一但确定好就不能更改
	if (rhs.GetDataType() == m_Value.GetDataType())
	{
		this->m_Value = rhs;
		return true;
	}
	return false;

}


const CInputOutputInfo& CToolOutput::GetValue() const
{
	return m_Value;
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


bool CToolOutput::IsSameType(const CToolOutput &rhs)
{
	return m_Value.IsSameType(rhs.m_Value);
}
bool CToolOutput::IsSameType(const CToolInput& rhs)
{
	return m_Value.IsSameType(rhs.m_Value);
}

CToolOutput& CToolOutput::operator = (const CToolOutput& rhs)
{
	if (this != &rhs)
	{
		m_strInfo = rhs.m_strInfo;
		m_Value = rhs.m_Value;
	}
	return *this;
}
