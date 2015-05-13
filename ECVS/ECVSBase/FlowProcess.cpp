#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include <vector>
#include "AlgrithmBase.h"
#include "FlowProcess.h"
using std::vector;

CFlowProcess::CFlowProcess()
{
}


CFlowProcess::~CFlowProcess()
{
}

//检测流程是否有错
bool CFlowProcess::ComplierFlow(string& strError)
{

	int nErrorCount = 0; //错误的个数
	//每个依次检查是否合法
	for (int i = 0; i < m_pAlgrithms.size(); ++i)
	{
		//const vector<CToolInput*> inputParam = m_pAlgrithms[i]->GetInput();
		//每个算法的每个参数检查
		for (int j = 0; j < m_vecRalationSheep[i].size(); ++j)
		{
			//首先检查是否是依赖算法集合后面的算法，如果是的话错误继续检查下一个
			//序列号不对的情况
			char strIndex[128];  //用来格式化的字符串
			if (m_vecRalationSheep[i][j]->nIndex >= m_pAlgrithms.size())
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具的输入超出了集合长度:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i][j]->nIndex);
				strError += strIndex + string(" 长度为 :");
				sprintf(strIndex, "%d", m_pAlgrithms.size());
				strError += strIndex + '\r\n';
				++nErrorCount;

				
				continue;
			}
			else if (m_vecRalationSheep[i][j]->nIndex >= i)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具不能依赖后面的算法:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i][j]->nIndex);
				strError += strIndex + string(" ") + m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetShowText();
			
				++nErrorCount;
				continue;
			}
			const CToolInput* pInput  = m_pAlgrithms[i]->GetInput(m_vecRalationSheep[i][j]->m_strWitchParam);
			const CToolOutput* pOutput = m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetOutput(m_vecRalationSheep[i][j]->m_strDestParam);
			//参数不存在的情况
			if (pInput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具不包含:" + m_vecRalationSheep[i][j]->m_strWitchParam + " 参数\r\n";
				++nErrorCount;
				continue;
			}
			if (pOutput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具依赖的输入" + m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetShowText() + " 不包含参数:" + m_vecRalationSheep[i][j]->m_strDestParam + " 参数\r\n";
				++nErrorCount;
				continue;
			}
			
			//到这里判断是否是同一种类型就OK

		
			if (!pInput->GetValue().IsSameType(pOutput->GetValue()))
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具依赖的输入" + m_pAlgrithms[m_vecRalationSheep[i][j]->nIndex]->GetShowText() + " 类型不匹配\r\n";
				++nErrorCount;
				continue;
			}

		}

	}

	return (nErrorCount <= 0);
}

//运行算法
bool  CFlowProcess::Run()
{
	string strError;
	//如果编译都不通过那么直接返回错误
	if (!ComplierFlow(strError))
	{
		return false;
	}
	int nIndex = 0;
	while (nIndex >= 0 && nIndex < m_pAlgrithms.size())
	{
		 SetInputParam(nIndex);
		 m_pAlgrithms[nIndex]->Run();
		 m_pOutput[nIndex] = m_pAlgrithms[nIndex]->GetOutput();
	}
}

void CFlowProcess::SetInputParam(int nIndex)
{
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //算法间的相互关系

	for (int i = 0; i < m_vecRalationSheep[nIndex].size(); ++i)
	{
		
		vector<CToolOutput*> pOutput = m_pOutput[m_vecRalationSheep[nIndex][i]->nIndex];
		CInputOutputInfo inOut;
		m_pAlgrithms[nIndex]->SetInputValue(m_vecRalationSheep[nIndex][i].m_strWitchParam, inOut);
	}


}