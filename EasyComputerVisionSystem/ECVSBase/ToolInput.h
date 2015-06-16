#pragma once
/*
* ToolInput.h
*
* 创建于 2015-5-12  李春峰
*
* 对CInputOutputInfo的封装，专门做Input
*
*/

#include "InputOutputInfo.h"
class ECVS_EXPORT CToolInput
{
	friend class CToolOutput;
public:
	CToolInput(DataType dataType, string strInfo = "");
	//复制构造函数
	CToolInput(const CToolInput &rhs);
	//赋值操作符
	CToolInput& operator=(const CToolInput&);
	~CToolInput();
	//设置值
	bool SetValue(const CInputOutputInfo&rhs);

	bool IsSameType(const CToolOutput &rhs);
	bool IsSameType(const CToolInput& rhs);

	const CInputOutputInfo& GetValue();
	const CInputOutputInfo& GetValue() const;
	//设置和获取说明文字
	void SetStringInfo(string strInfo);
	string GetStringInfo();
	
private:
	CInputOutputInfo	m_Value;
	string				m_strInfo;   //对于该字段的说明文字, 比如 “输入图像” 、"偏移X"

	

};

