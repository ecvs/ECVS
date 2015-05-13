/*
* InputOutputInfo.cpp
*
* 创建于 2015-5-12  李春峰
*
* 实现CInputOutputInfo数据类型
*
*/

#define  ECVS_BUILD_DLL
#include "InputOutputInfo.h"

//构造函数,必须指定类型
CInputOutputInfo::CInputOutputInfo(DataType type) :m_dataType(type)
{
}


CInputOutputInfo::~CInputOutputInfo()
{
}

//赋值构造函数
CInputOutputInfo::CInputOutputInfo(const CInputOutputInfo& rhs) //复制构造函数
{
	CopyValue(rhs);
}

//赋值操作符
CInputOutputInfo& CInputOutputInfo::operator = (const CInputOutputInfo& rhs)
{
	//如果不是自身赋值,那么赋值
	if (this != &rhs)
	{
		CopyValue(rhs);
	}
	return *this;
}

//将rhs的值复制到该对象
void CInputOutputInfo::CopyValue(const CInputOutputInfo& rhs)
{
	//类型
	this->m_dataType = rhs.m_dataType;

	//通过不同的类型来赋值
	switch (m_dataType)
	{
	case TYPE_INT:
		m_nIntValue = rhs.m_nIntValue;
		break;
	case TYPE_DOUBLE:
		m_dbValue = rhs.m_dbValue;
		break;
	case TYPE_STRING:
		m_strValue = rhs.m_strValue;
		break;
	case TYPE_POINT:
		break;
	case TYPE_POINT2F:
		break;
	case TYPE_IMAGE:
		break;
	case TYPE_INT_VECTOR:
		m_vecIntValue = rhs.m_vecIntValue;
		break;
	case TYPE_DOUBLE_VECTOR:
		m_vecDoubleValue = rhs.m_vecDoubleValue;
		break;
	case TYPE_STRING_VECTOR:
		m_vecStrValue = rhs.m_vecStrValue;
		break;
	case TYPE_POINT_VECTOR:
		break;
	case TYPE_POINT2F_VECTOR:
		break;
	case TYPE_IMAGE_VECTOR:
		break;
	default:
		break;
	}

}


//获取该对象的类型,返回DataTyoe
DataType CInputOutputInfo::GetDataType()
{
	return m_dataType;
}
const DataType CInputOutputInfo::GetDataType() const
{
	return m_dataType;
}


//判断数据类型是否是Vector类型如果是返回true，否则false
bool  CInputOutputInfo::IsVector()
{
	if ( (m_dataType & DATA_TYPE_VEC_BASE) == DATA_TYPE_VEC_BASE)
	{
		return true;
	}
	return false;
}

bool CInputOutputInfo::IsSameType(const CInputOutputInfo& rhs) const
{
	return ::IsSameType(m_dataType, rhs.m_dataType);
}

bool CInputOutputInfo::IsSameType(const CInputOutputInfo& rhs)
{
	return ::IsSameType(m_dataType, rhs.m_dataType);
}

//以下一系列函数为设置和获取数据值的函数，如果尝试获取或设置不同类型的值那么返回false
bool CInputOutputInfo::GetIntValue(int& nValue)
{
	if (m_dataType == DataType::TYPE_INT)
	{
		nValue = m_nIntValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetDoubleValue(double& dbValue)
{
	if (m_dataType == DataType::TYPE_DOUBLE)
	{
		dbValue = m_dbValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetStringValue(string& strValue)
{
	if (m_dataType == DataType::TYPE_STRING)
	{
		strValue = m_strValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetVectIntValue(vector<int>& vecInt)
{
	if (m_dataType == DataType::TYPE_INT_VECTOR)
	{
		vecInt = m_vecIntValue;
	}
	return false;
}
bool CInputOutputInfo::GetVectDoubleValue(vector<double>& vecDouble)
{
	if (m_dataType == DataType::TYPE_DOUBLE_VECTOR)
	{
		vecDouble = m_vecDoubleValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::GetVecStrValue(vector<string>& strValue)
{
	if (m_dataType == DataType::TYPE_STRING_VECTOR)
	{
		strValue = m_vecStrValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetIntValue(const int& nValue)
{
	if (m_dataType == DataType::TYPE_INT)
	{
		m_dbValue = nValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetDoubleValue(const double& dbValue)
{
	if (m_dataType == DataType::TYPE_DOUBLE)
	{
		m_dbValue = dbValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetStringValue(const string& strValue)
{
	if (m_dataType == DataType::TYPE_STRING)
	{
		m_strValue = strValue;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetVectIntValue(const vector<int>& vecInt)
{
	if (m_dataType == DataType::TYPE_INT_VECTOR)
	{
		m_vecIntValue = vecInt;
		return true;
	}
	return false;
}
bool CInputOutputInfo::SetVectDoubleValue(const vector<double>& vecDouble)
{
	if (m_dataType == DataType::TYPE_DOUBLE_VECTOR)
	{
		m_vecDoubleValue = vecDouble;
	}
	return false;
}
bool CInputOutputInfo::SetVecStrValue(const vector<string>& strValue)
{
	if (m_dataType == DataType::TYPE_STRING_VECTOR)
	{
		m_vecStrValue = strValue;
		return true;
	}
	return false;
}


//两个全局函数
bool IsVector(DataType dt) //判断dt是否是vector类型
{
	return ((dt&DATA_TYPE_VEC_BASE) == DATA_TYPE_VEC_BASE);
}
bool IsSameType(DataType dt1, DataType dt2)// 判断dt1和 dt2是否为同一种类型 比如vector<int> 和int是同一种类型
{
	 return ( (dt1 ^ dt2) &0x00FF == 0);
}