#include "stdafx.h"

#include "ECVSBase.h"
#include "InputOutputInfo.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include <vector>
#include "AlgrithmBase.h"


#include "InputSet.h"
#include "FlowProcess.h"
using std::vector;
CShowImageWnd* CFlowProcess::m_pImgWnd = NULL;
CFlowProcess::CFlowProcess()
{
/*	m_pImgWnd = NULL;*/
}


CFlowProcess::~CFlowProcess()
{
	DeleteMemory();
}

CFlowProcess::CFlowProcess(const CFlowProcess& rhs)
{
	Copy(rhs);

}

const CFlowProcess& CFlowProcess::operator = (const CFlowProcess& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

void CFlowProcess::Copy(const CFlowProcess& rhs)
{
	//首先删除所有内存空间
	DeleteMemory();

	//然后依次赋值
// 	vector<CAlgrithmBase*> m_pAlgrithms;   // 流程中的算法集合
// 	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //算法间的相互关系
// 	vector<AlgrithmRelateship*> m_vecRalationSheep;  //算法间的相互关系
// 	vector< vector<CToolOutput*> >  m_pOutput; // 执行过程中每个算法的输出值
	for (int i = 0; i < rhs.m_pAlgrithms.size(); ++i)
	{
		CAlgrithmBase* pAlg = rhs.m_pAlgrithms[i]->Clone();
		m_pAlgrithms.push_back(pAlg);
	}

	for (int i = 0; i < rhs.m_vecRalationSheep.size(); ++i)
	{
		m_vecRalationSheep.push_back(new AlgrithmRelateship(*rhs.m_vecRalationSheep[i]));
	}

	for (int i = 0; i < rhs.m_pOutput.size(); ++i)
	{
		vector<CToolOutput*> pOutput;
		for (int j = 0; j < rhs.m_pOutput[i].size(); ++j)
		{
			pOutput.push_back(new CToolOutput(*rhs.m_pOutput[i][j]));
		}
		m_pOutput.push_back(pOutput);
	}
}

//删除所有存储空间
void CFlowProcess::DeleteMemory()
{

	for (int i = m_pAlgrithms.size() - 1; i >= 0; --i)
	{
// 		delete m_pAlgrithms[i];
// 		m_pAlgrithms[i] = NULL;

		ClearAlgrithm(m_pAlgrithms[i]);

		m_pAlgrithms.pop_back();

	}

	for (int i = m_vecRalationSheep.size() - 1; i >= 0; --i)
	{
		delete m_vecRalationSheep[i];
		m_vecRalationSheep[i] = NULL;
		m_vecRalationSheep.pop_back();
	}

	for (int i = m_pOutput.size() - 1; i >= 0; --i)
	{
		for (int j = m_pOutput[i].size() - 1; j >= 0; --j)
		{
			delete m_pOutput[i][j];
			m_pOutput[i][j] = NULL;
			
			m_pOutput[i].pop_back();
		}
		
		m_pOutput.pop_back();
	}

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
		for (int j = 0; j < m_vecRalationSheep[i]->m_relationShip.size(); ++j)
		{
			//首先检查是否是依赖算法集合后面的算法，如果是的话错误继续检查下一个
			//序列号不对的情况
			char strIndex[128];  //用来格式化的字符串
			if (m_vecRalationSheep[i]->m_relationShip[j]->nIndex >= m_pAlgrithms.size())
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具的输入超出了集合长度:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i]->m_relationShip[j]->nIndex);
				strError += strIndex + string(" 长度为 :");
				sprintf(strIndex, "%d", m_pAlgrithms.size());
				strError += strIndex + '\r\n';
				++nErrorCount;


				continue;
			}
			else if (m_vecRalationSheep[i]->m_relationShip[j]->nIndex >= i)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具不能依赖后面的算法:";
				sprintf(strIndex, "%d", m_vecRalationSheep[i]->m_relationShip[j]->nIndex);
				strError += strIndex + string(" ") + m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetShowText();

				++nErrorCount;
				continue;
			}
			const CToolInput* pInput = m_pAlgrithms[i]->GetInput(m_vecRalationSheep[i]->m_relationShip[j]->m_strWitchParam);
			const CToolOutput* pOutput = m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetOutput(m_vecRalationSheep[i]->m_relationShip[j]->m_strDestParam);
			//参数不存在的情况
			if (pInput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具不包含:" + m_vecRalationSheep[i]->m_relationShip[j]->m_strWitchParam + " 参数\r\n";
				++nErrorCount;
				continue;
			}
			if (pOutput == NULL)
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具依赖的输入" + m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetShowText() + " 不包含参数:" + m_vecRalationSheep[i]->m_relationShip[j]->m_strDestParam + " 参数\r\n";
				++nErrorCount;
				continue;
			}

			//到这里判断是否是同一种类型就OK


			if (!pInput->GetValue().IsSameType(pOutput->GetValue()))
			{
				sprintf(strIndex, "%d", i + 1);
				strError += string("第") + strIndex + "个工具依赖的输入" + m_pAlgrithms[m_vecRalationSheep[i]->m_relationShip[j]->nIndex]->GetShowText() + " 类型不匹配\r\n";
				++nErrorCount;
				continue;
			}

		}

	}

	return (nErrorCount <= 0);
}
void CFlowProcess::SetShowImgWnd(CShowImageWnd * pWnd)
{
	m_pImgWnd = pWnd;
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
	m_imgCur.clear();
	int nIndex = 0;
	while (nIndex >= 0 && nIndex < m_pAlgrithms.size())
	{
		SetInputParam(nIndex);
		m_pAlgrithms[nIndex]->Run();
		
		vector<CToolOutput*> pOut = m_pAlgrithms[nIndex]->GetOutput();
		
		//清空输出空间
		for (int i = 0; i < m_pOutput[nIndex].size(); ++i)
		{
			delete m_pOutput[nIndex][i];
			m_pOutput[nIndex][i] = NULL;
		}
		m_pOutput[nIndex].clear();


		for (int i = 0; i < pOut.size(); ++i)
		{
			m_pOutput[nIndex].push_back(new CToolOutput(*pOut[i]));
		}

		//每个输出都要事先 “错误代码”和"运行时间"
		const CToolOutput* pOutErrorCode = m_pAlgrithms[nIndex]->GetOutput("错误代码");


		int nErrorCode;
		bool b = pOutErrorCode->GetValue().GetIntValue(nErrorCode);
		if (nErrorCode != ECVS_ERROR_NO_ERROR)
		{
			// 错误后的处理流程
			if (m_vecRalationSheep[nIndex]->m_FalidProcess == RunFaildProcess::BREAK)
			{
				break;
			}
			else if (m_vecRalationSheep[nIndex]->m_FalidProcess == RunFaildProcess::IGNORED)
			{
				++nIndex; // 继续执行下一次
				continue;  //忽略 继续进行
			}
			else if (m_vecRalationSheep[nIndex]->m_FalidProcess == RunFaildProcess::STEPTO)
			{
				nIndex = m_vecRalationSheep[nIndex]->m_nStep2Index;  //设置跳转
				continue;
			}
			else  //应该不会走到这里面去，如果意外走进去，停止执行
			{
				break;
			}
		}
		else
		{
			vector<CToolOutput*>pOut =  m_pAlgrithms[nIndex]->GetOutput();
			for (int i = 3; i < pOut.size(); ++i)
			{
				if (pOut[i]->GetValue().GetDataType() == DataType::TYPE_IMAGE)
				{
					Mat img;
					pOut[i]->GetValue().GetImageValue(img);
					m_imgCur.push_back(img.clone());
				}
			}

			const CToolOutput* pImgResult = m_pAlgrithms[nIndex]->GetOutput("结果图像");
			Mat imgRet;
			bool bOk = pImgResult->GetValue().GetImageValue(imgRet);
			if (imgRet.data != NULL && m_pImgWnd != NULL )
			{
				m_pImgWnd->SetImage(imgRet);
			}
			++nIndex; //执行下一次
		}

	
	}
}


//设置输入参数，nIndex是算法集合的第几个,
//该函数代码逻辑简单，但是代码繁琐，难以理解，仅由李春峰维护----2015-5-14
void CFlowProcess::SetInputParam(int nIndex)
{
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //算法间的相互关系


	//如果没有为输入参数设置参数，那么如果是图像的话，就选择当前的图像
	vector<CToolInput*> pInput = m_pAlgrithms[nIndex]->GetInput();
	for (int i = 0; i < pInput.size(); ++i)
	{
		bool bHasSet = false;
		for (int j = 0; j < m_vecRalationSheep[nIndex]->m_relationShip.size(); ++j)
		{
			if (m_vecRalationSheep[nIndex]->m_relationShip[j]->m_strWitchParam == pInput[i]->GetStringInfo())
			{
				bHasSet = true;
				break;
			}
			
		}
		//如果是图像的话
		if (!bHasSet && (pInput[i]->GetValue().GetDataType() == TYPE_IMAGE))
		{
			if (m_imgCur.size() > 0)
			{
				CInputOutputInfo inout(TYPE_IMAGE);
				inout.SetImageValue(m_imgCur[0].clone());

				pInput[i]->SetValue(inout);
			}
		}
	}

	//算法的每个字段依次设置输入参数，到了该函数所有的检测都完成所以不用做任何检测 只需按条件赋值就行
	for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip.size(); ++i)
	{
		vector<CToolOutput*> pOutput = m_pOutput[m_vecRalationSheep[nIndex]->m_relationShip[i]->nIndex];
		CInputOutputInfo inOut(m_pAlgrithms[nIndex]->GetInput(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strWitchParam)->GetValue().GetDataType());
		DataType dtInput = inOut.GetDataType();  //输入的类型
		//如果是默认操作,当为负1时为默认操作,图像就取最近的一张返回图像
		if (m_vecRalationSheep[nIndex]->m_relationShip[i]->nIndex == -1)
		{
			if (inOut.GetDataType() == DataType::TYPE_IMAGE || inOut.GetDataType() == DataType::TYPE_IMAGE_VECTOR)
			{
				if (m_imgCur.size() > 0)
				{
					inOut.SetImageValue(m_imgCur[0].clone());
				}
			
			}
		}

	


	
		//获取输入参数的源数据
		const CToolOutput* pSrc = m_pAlgrithms[m_vecRalationSheep[nIndex]->m_relationShip[i]->nIndex]->GetOutput(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strDestParam);
		const CInputOutputInfo& valueSrc = pSrc->GetValue();
		//设置输入的值，这里由于是构造 CInputOutputInfo 的值 所以需要对所有CInputOutputInfo能支持的类型进行设置
	
		
		//为图像设置默认的操作
	

		//下面的代码比较繁琐，
		if (inOut.IsVector())  //如果输入类型是序列
		{
			if (valueSrc.IsVector())  //如果数据源也是序列
			{
				//inOut  是vector类型
				switch (inOut.GetDataType())
				{
				case TYPE_INT_VECTOR:
				{
										vector<int> vecValue;
										vector<int> nValue;
										valueSrc.GetVectIntValue(nValue);
										for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //依次设值
										{
											if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= nValue.size())
											{
												continue;
											}
											vecValue.push_back(nValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										}
										inOut.SetVectIntValue(vecValue);
										break;
				}

				case TYPE_DOUBLE_VECTOR:
				{

										   vector<double> vecValue;
										   vector<double> dbValue;
										   valueSrc.GetVectDoubleValue(dbValue);
										   for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //依次设值
										   {
											   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= dbValue.size())
											   {
												   continue;
											   }
											   vecValue.push_back(dbValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										   }
										   inOut.SetVectDoubleValue(vecValue);
										   break;
				}


				case TYPE_STRING_VECTOR:

				{
										   vector<string> vecValue;
										   vector<string> strValue;
										   valueSrc.GetVecStrValue(strValue);
										   for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //依次设值
										   {
											   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= strValue.size())
											   {
												   continue;
											   }
											   vecValue.push_back(strValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										   }
										   inOut.SetVecStrValue(strValue);
										   break;
				}

					break;
				case TYPE_POINT_VECTOR:
				{
										  vector<Point> vecValue;
										  vector<Point> ptValue;
										  valueSrc.GetVecPointValue(ptValue);
										  for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //依次设值
										  {
											  if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= ptValue.size())
											  {
												  continue;
											  }
											  vecValue.push_back(ptValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										  }
										  inOut.SetVecPointValue(vecValue);
										  break;
				}

					
				case TYPE_POINT2F_VECTOR:
				{
											vector<Point2f> vecValue;
											vector<Point2f> ptValue;
											valueSrc.GetVecPointFValue(ptValue);
											for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //依次设值
											{
												if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= ptValue.size())
												{
													continue;
												}
												vecValue.push_back(ptValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
											}
											inOut.SetVecPointFValue(vecValue);
											break;
				}
				
				case TYPE_IMAGE_VECTOR:
				{
										  vector<Mat> vecValue;
										  vector<Mat> ptValue;
										  valueSrc.GetVecImageValue(ptValue);
										  for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size(); ++i)  //依次设值
										  {
											  if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i] >= ptValue.size())
											  {
												  continue;
											  }
											  vecValue.push_back(ptValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[i]]);
										  }
										  inOut.SetVecImageValue(vecValue);
										  break;
				}
				
				default:
					break;
				}
			}
			else  // 如果数据源不是序列，那么直接将当个数据添加进来，
			{

				//inOut  不是vector类型
				switch (inOut.GetDataType())
				{
				case TYPE_INT_VECTOR:
				{
										vector<int> vecValue;
										int nValue;
										valueSrc.GetIntValue(nValue);
										vecValue.push_back(nValue);
										inOut.SetVectIntValue(vecValue);
										break;
				}

				case  TYPE_DOUBLE_VECTOR:
				{

											vector<double> vecValue;
											double dbValue;
											valueSrc.GetDoubleValue(dbValue);
											vecValue.push_back(dbValue);
											inOut.SetVectDoubleValue(vecValue);
											break;
				}


				case TYPE_STRING_VECTOR:

				{
										   vector<string> vecValue;
										   string strValue;
										   valueSrc.GetStringValue(strValue);
										   vecValue.push_back(strValue);
										   inOut.SetVecStrValue(vecValue);
				}

					break;
				case TYPE_POINT_VECTOR:
				{
										  vector<Point> vecValue;
										  Point ptValue;
										  valueSrc.GetPointValue(ptValue);
										  vecValue.push_back(ptValue);
										  inOut.SetVecPointValue(vecValue);
										
				}
					break;
				case TYPE_POINT2F_VECTOR:
				{
											vector<Point2f> vecValue;
											Point2f ptValue;
											valueSrc.GetPointFValue(ptValue);
											vecValue.push_back(ptValue);
											inOut.SetVecPointFValue(vecValue);

				}
					break;
				case TYPE_IMAGE_VECTOR:
				{
										  vector<Mat> vecValue;
										  Mat img;
										  valueSrc.GetImageValue(img);
										  vecValue.push_back(img);
										  inOut.SetVecImageValue(vecValue);

				}
					break;
				default:
					break;
				}






			}
		}
		else  //否则是单个类型
		{
			if (valueSrc.IsVector())  //如果源数据是vector
			{
				switch (inOut.GetDataType())
				{
				case TYPE_INT:
				{

								 vector<int> vecValue;
								 valueSrc.GetVectIntValue(vecValue);
								 if (vecValue.size() < 0)  //输入数据为空，错误处理交给算法本身
								 {
									 break;
								 }
								 int nValue;
								 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
								 {
									 nValue = vecValue[0];
								 }
								 else
								 {
									 ////如果所选的值超出范围 直接返回 不去做任何处理
									 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
									 {
										 break;
									 }
									 nValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
								 }
								 inOut.SetIntValue(nValue);
								 break;
				}

				case TYPE_DOUBLE:
				{

									vector<double> vecValue;
									double dbValue;
									valueSrc.GetVectDoubleValue(vecValue);

									if (vecValue.size() < 0)  //输入数据为空，错误处理交给算法本身
									{
										break;
									}
									if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
									{
										dbValue = vecValue[0];
									}
									else
									{
										////如果所选的值超出范围 直接返回 不去做任何处理
										if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
										{
											break;
										}
										dbValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
									}

									inOut.SetDoubleValue(dbValue);
									break;
				}


				case TYPE_STRING:

				{
									vector<string> vecValue;
									string strValue;
									valueSrc.GetVecStrValue(vecValue);

									if (vecValue.size() < 0)  //输入数据为空，错误处理交给算法本身
									{
										break;
									}
									if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
									{
										strValue = vecValue[0];
									}
									else
									{
										////如果所选的值超出范围 直接返回 不去做任何处理
										if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
										{
											break;
										}
										strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
									}

									inOut.SetStringValue(strValue);
									break;
				}

					break;
				case TYPE_POINT:

				{
								   vector<Point> vecValue;
								   Point strValue;
								   valueSrc.GetVecPointValue(vecValue);

								   if (vecValue.size() < 0)  //输入数据为空，错误处理交给算法本身
								   {
									   break;
								   }
								   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
								   {
									   strValue = vecValue[0];
								   }
								   else
								   {
									   ////如果所选的值超出范围 直接返回 不去做任何处理
									   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
									   {
										   break;
									   }
									   strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
								   }

								   inOut.SetPointValue(strValue);
								   break;
				}
					break;
				case TYPE_POINT2F:

				{
									 vector<Point2f> vecValue;
									 Point2f strValue;
									 valueSrc.GetVecPointFValue(vecValue);

									 if (vecValue.size() < 0)  //输入数据为空，错误处理交给算法本身
									 {
										 break;
									 }
									 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
									 {
										 strValue = vecValue[0];
									 }
									 else
									 {
										 ////如果所选的值超出范围 直接返回 不去做任何处理
										 if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
										 {
											 break;
										 }
										 strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
									 }

									 inOut.SetPointFValue(strValue);
									 break;
				}
					break;
				case TYPE_IMAGE:

				{
								   vector<Mat> vecValue;
								   Mat strValue;
								   valueSrc.GetVecImageValue(vecValue);

								   if (vecValue.size() < 0)  //输入数据为空，错误处理交给算法本身
								   {
									   break;
								   }
								   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex.size() <= 0)
								   {
									   strValue = vecValue[0];
								   }
								   else
								   {
									   ////如果所选的值超出范围 直接返回 不去做任何处理
									   if (m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0] >= vecValue.size())
									   {
										   break;
									   }
									   strValue = vecValue[m_vecRalationSheep[nIndex]->m_relationShip[i]->m_vecIndex[0]];
								   }

								   inOut.SetImageValue(strValue);
								   break;
				}
					break;
				default:
					break;
				}
			}
			else //源数据也是单个类型
			{
				//inOut  不是vector类型
				switch (inOut.GetDataType())
				{
				case TYPE_INT:
				{
								 // vector<int> vecValue;
								 int nValue;
								 valueSrc.GetIntValue(nValue);
								 //vecValue.push_back(nValue);
								 inOut.SetIntValue(nValue);
								 break;
				}

				case  TYPE_DOUBLE:
				{


									 double dbValue;
									 valueSrc.GetDoubleValue(dbValue);

									 inOut.SetDoubleValue(dbValue);
									 break;
				}


				case TYPE_STRING:

				{

									string strValue;
									valueSrc.GetStringValue(strValue);
									inOut.SetStringValue(strValue);
				}

					break;
				case TYPE_POINT:
				{

								   Point ptPos;
								   valueSrc.GetPointValue(ptPos);
								   inOut.SetPointValue(ptPos);
				}
					break;
				case TYPE_POINT2F:
				{

									 Point2f ptPos;
									 valueSrc.GetPointFValue(ptPos);
									 inOut.SetPointFValue(ptPos);
				}
					break;
				case TYPE_IMAGE:
				{

								   Mat img;
								   valueSrc.GetImageValue(img);
								   inOut.SetImageValue(img);
				}
					break;
				default:
					break;
				}
			}


			m_pAlgrithms[nIndex]->SetInputValue(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strWitchParam, inOut);
		}


	}
}


bool CFlowProcess::AddAlgrithm(CAlgrithmBase* pAlgrithm) //往集合最后添加一个算法
{
	CAlgrithmBase* pAdd = pAlgrithm->Clone();
	m_pAlgrithms.push_back(pAdd);  //重新分配一个新的对象
	AlgrithmRelateship *pShip = new AlgrithmRelateship();


	m_vecRalationSheep.push_back(pShip);
	vector<CToolOutput*> pOutput = pAdd->GetOutput();
	vector<CToolOutput*> pOutputClone;
	for (int i = 0; i < pOutput.size(); ++i)
	{
		pOutputClone.push_back(new CToolOutput(*pOutput[i]));
	}
	m_pOutput.push_back(pOutputClone); 
	return true;
}
bool CFlowProcess::InsertAlgirthm(CAlgrithmBase* pAlgrithm, int nIndex) //插入一个算法到nIndex处，如果超出范围 ,返回false，什么都不做
{
	if (nIndex < 0 || nIndex > m_pAlgrithms.size())
	{
		return false;
	}

	m_pAlgrithms.insert(m_pAlgrithms.begin() + nIndex, pAlgrithm->Clone());
	m_vecRalationSheep.insert(m_vecRalationSheep.begin() + nIndex, new AlgrithmRelateship());
	vector<CToolOutput*> pOutput = pAlgrithm->GetOutput();
	vector<CToolOutput*> pOutputClone;
	for (int i = 0; i < pOutput.size(); ++i)
	{
		pOutputClone.push_back(new CToolOutput(*pOutput[i]));
	}
	m_pOutput.insert(m_pOutput.begin() + nIndex, pOutputClone);
	return true;
}

//两个函数暂未实现
bool CFlowProcess::ExchangeAlgrithmIndex(int nIndex1, int nIndex2) //将nIndex1和nIndex2的算法相互交换,下标不在范围返回false
{
	return true;
}
bool CFlowProcess::ChangeAlgrithmIndex(int nIndex, int nChangedIndex) //将nIndex的算法放到nChangedIndex处 之间的算法依次填补过去,下标非法返回错误
{
	if (nIndex < 0 || nIndex >= m_pAlgrithms.size() || nChangedIndex < 0 ||
		nChangedIndex >= m_pAlgrithms.size())
	{
		return false;
	}


	CAlgrithmBase* pPre = m_pAlgrithms[nIndex];
	CAlgrithmBase* pAft = m_pAlgrithms[nChangedIndex];

// 	vector<AlgrithmRelateship*> m_vecRalationSheep;  //算法间的相互关系
// 	vector< vector<CToolOutput*> >  m_pOutput; // 执行过程中每个算法的输出值

	AlgrithmRelateship* pShipPre = m_vecRalationSheep[nIndex];
	AlgrithmRelateship* pShipAft = m_vecRalationSheep[nChangedIndex];
	vector<CToolOutput*> pOutPre = m_pOutput[nIndex];
	vector<CToolOutput*> pOutAft = m_pOutput[nChangedIndex];

	m_pAlgrithms[nChangedIndex] = pPre;
	m_vecRalationSheep[nChangedIndex] = pShipPre;
	m_pOutput[nChangedIndex] = pOutPre;
	int nAdd = (nIndex - nChangedIndex) > 0 ? 1 : -1;
	int i = nChangedIndex;
	do 
	{
		i += nAdd;
		pPre = m_pAlgrithms[i];
		m_pAlgrithms[i] = pAft;
		pAft = pPre;

		pShipPre = m_vecRalationSheep[i];
		m_vecRalationSheep[i] = pShipAft;
		pShipAft = pShipPre;

		pOutPre = m_pOutput[i];
		m_pOutput[i] = pOutAft;
		pOutAft = pOutPre;



	} while (i != nIndex);

	return true;
}
bool CFlowProcess::DelAlgrithm(int nIndex) //删除nIndex处的Algorithm,如果下标非法则返回false
{
	if (nIndex < 0 || nIndex >= m_pAlgrithms.size())
	{
		return false;
	}

// 	delete m_pAlgrithms[nIndex];
// 	m_pAlgrithms[nIndex] = NULL;

	ClearAlgrithm(m_pAlgrithms[nIndex]);

	m_pAlgrithms.erase(m_pAlgrithms.begin() + nIndex);

	delete m_vecRalationSheep[nIndex];
	m_vecRalationSheep[nIndex] = NULL;
	m_vecRalationSheep.erase(m_vecRalationSheep.begin() + nIndex);

	for (int i = 0; i < m_pOutput[nIndex].size(); ++i)
	{
		delete m_pOutput[nIndex][i];
		
	}
	m_pOutput[nIndex].clear();
	m_pOutput.erase(m_pOutput.begin() + nIndex);
	return true;
}
void CFlowProcess::ClearAlgrithm(CAlgrithmBase* pAlgrithm)
{
	if (pAlgrithm->NeedClear())
	{
		delete pAlgrithm;
		pAlgrithm = NULL;
	}

}
bool CFlowProcess::SetAlgrithmName(int nIndex, std::string strName) //设置算法显示名字
{
	if (nIndex >= 0 && nIndex < m_pAlgrithms.size())
	{
		 m_pAlgrithms[nIndex]->SetShowText(strName);
		 return true;
	}
	return false;
}
bool CFlowProcess::SetAlgrithm(int nIndex)
{
	if (nIndex >= 0 && nIndex < m_pAlgrithms.size())
	{
		return m_pAlgrithms[nIndex]->Set();
	}
	return false;
	
}


bool CFlowProcess::SetInput(int nIndex)
{
	CInputSet *pSet = new CInputSet(nIndex);

	pSet->m_pOwerProcess = this;

	vector<CToolInput*>  pInput = m_pAlgrithms[nIndex]->GetInput();
	vector<string>  pStrName = m_pAlgrithms[nIndex]->GetInputParamName();
	for (int i = 0; i < pInput.size(); ++i)
	{
		string strInfo  = pInput[i]->GetStringInfo();
		pSet->AddSrcInput(StdStr2QString(pStrName[i]), StdStr2QString(pInput[i]->GetStringInfo()));
	}


	for (int i = 0; i < nIndex; ++i)
	{
		string strAlgrithm = m_pAlgrithms[i]->GetShowText();
		pSet->AddPreAlgrithms(StdStr2QString(strAlgrithm));
	}

	pSet->exec();
	return true;
}