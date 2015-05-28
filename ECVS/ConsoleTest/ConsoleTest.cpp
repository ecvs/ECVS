// ConsoleTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ECVSBase.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include<vector>
#include <iostream>
#include <string>
using std::string;
#include "AlgrithmBase.h"
#include "BilateralFilter.h"
#pragma  comment(lib, "ECVSFilter.lib")
using namespace std;
int a = 5;
const int& GetIntValue()
{
	return a;
}
int _tmain(int argc, _TCHAR* argv[])
{

	CBilateralFilter *pBi = new CBilateralFilter();
	pBi->Set();
	vector<string> vec1;
	for (int i = 0; i < 10; ++i)
	{
		vec1.push_back("asd");
	}
	vector<string> vec2 = vec1;
	const int& b = GetIntValue();

	return 0;
}

