#include "stdafx.h"
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
	
	}
}


//设置输入参数，nIndex是算法集合的第几个,
//该函数代码逻辑简单，但是代码繁琐，难以理解，仅由李春峰维护----2015-5-14
void CFlowProcess::SetInputParam(int nIndex)
{
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //算法间的相互关系

	//算法的每个字段依次设置输入参数，到了该函数所有的检测都完成所以不用做任何检测 只需按条件赋值就行
	for (int i = 0; i < m_vecRalationSheep[nIndex]->m_relationShip.size(); ++i)
	{

		vector<CToolOutput*> pOutput = m_pOutput[m_vecRalationSheep[nIndex]->m_relationShip[i]->nIndex];
		CInputOutputInfo inOut(m_pAlgrithms[nIndex]->GetInput(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strWitchParam)->GetValue().GetDataType());
		DataType dtInput = inOut.GetDataType();  //输入的类型
		//获取输入参数的源数据
		const CToolOutput* pSrc = m_pAlgrithms[m_vecRalationSheep[nIndex]->m_relationShip[i]->nIndex]->GetOutput(m_vecRalationSheep[nIndex]->m_relationShip[i]->m_strDestParam);
		const CInputOutputInfo& valueSrc = pSrc->GetValue();
		//设置输入的值，这里由于是构造 CInputOutputInfo 的值 所以需要对所有CInputOutputInfo能支持的类型进行设置
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