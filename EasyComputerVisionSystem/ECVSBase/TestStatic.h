#pragma once
#include<QWidget>
class ECVS_EXPORT CTestStatic
{
public:
	CTestStatic();
	~CTestStatic();

public:
	const static int n;
	//static const int a;
public:
	int getA()
	{
		return CTestStatic::n;
	}
};

