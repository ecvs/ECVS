#include "stdafx.h"
#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"

#include <vector>
using std::vector;
#include "AlgrithmPlugin.h"


CAlgrithmPlugin::CAlgrithmPlugin(string strInnerName):m_strData(strInnerName)
{
}


CAlgrithmPlugin::~CAlgrithmPlugin()
{
}

string CAlgrithmPlugin::GetAlgrithmInnerName()
{
	return m_strData;
}
