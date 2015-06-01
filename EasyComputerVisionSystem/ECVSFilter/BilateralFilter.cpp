#include "stdafx.h"
#include "resource.h"
#include "FilterCommon.h"
#include "BilateralFilter.h"
#include "opencv2/imgproc.hpp"
#include "BilateralFilterSet.h"
#include <windows.h>
#include <QDateTime>

CBilateralFilter::CBilateralFilter() :CAlgrithmBase()
{
	//三个参数都初始化为1
	m_nDiameter = 1;
	m_dbSigmaColor = 1;
	m_dbSigmaSpace = 1;
	CToolOutput *pOutImg = new CToolOutput(DataType::TYPE_IMAGE);
	pOutImg->SetStringInfo("输出图像");
	m_vectOutput.push_back(pOutImg);

	CToolInput* pInputImg = new CToolInput(DataType::TYPE_IMAGE);
	pInputImg->SetStringInfo("输入图像");
	m_vectInput.push_back(pInputImg);
	
}


CBilateralFilter::~CBilateralFilter()
{
}


void CBilateralFilter::Run()
{

	//QDateTime t1 = QDateTime::currentDateTime(); 
	

	int t1 = GetTickCount();
	CToolInput *pInput = m_vectInput[0];  //输入图像
	Mat pImgSrc;
	bool bTrue = pInput->GetValue().GetImageValue(pImgSrc);



	if (pImgSrc.data != NULL)
	{
		Mat imgOut;
		//执行算法
		bilateralFilter(pImgSrc, imgOut, m_nDiameter, m_dbSigmaColor, m_dbSigmaSpace);

		//设置输出图像
		CInputOutputInfo info(DataType::TYPE_IMAGE);
		info.SetImageValue(imgOut);
		m_vectOutput[2]->SetValue(info);

		CInputOutputInfo err(DataType::TYPE_INT);
		err.SetIntValue(ECVS_ERROR_NO_ERROR);
		m_vectOutput[0]->SetValue(err);

	}
	else
	{
		CInputOutputInfo err(DataType::TYPE_INT);
		err.SetIntValue(ECVS_ERROR_HAS_NO_IMG_INPUT);
		m_vectOutput[0]->SetValue(err);
	}

	//设置算法执行时间
	int tall = GetTickCount() - t1;
	CInputOutputInfo t(DataType::TYPE_DOUBLE);
	t.SetDoubleValue(tall);
	m_vectOutput[1]->SetValue(t);

}


Mat CBilateralFilter::Run(Mat inputimg,int nD, double dbSigmaColor, double dbSigmaSpace)
{
	Mat imgOut;
	bilateralFilter(inputimg, imgOut, nD, dbSigmaColor, dbSigmaSpace);
	return imgOut;
}
void CBilateralFilter::Set()
{


 	CBilateralFilterSet setF(this);

	
	setF.exec();
// 	setF.setWindowModality(Qt::WindowModal);
// 	setF.show();
// 	setF.DoModal();
}
string CBilateralFilter::GetErrorMsg()
{
	string strErr = CAlgrithmBase::GetErrorMsg();

	if (strErr == "")
	{
		return "未定义错误";
	}
	return strErr;


}