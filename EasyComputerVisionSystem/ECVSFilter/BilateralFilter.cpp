#include "stdafx.h"
#include "resource.h"
#include "FilterCommon.h"
#include "BilateralFilter.h"
#include "opencv2/imgproc.hpp"
#include "BilateralFilterSet.h"
#include <windows.h>
#include <QDateTime>
#include <string>
using std::string;
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

	m_strAlgrithmName = string("ECVS_BilateralFilter");
	m_strClassName = string("CBilateralFilter");
	m_strShowText = "双边滤波";
}


CBilateralFilter::~CBilateralFilter()
{
}

CBilateralFilter::CBilateralFilter(const CBilateralFilter& rhs)
{
	Clone(rhs);
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
		//cv::threshold(pImgSrc, imgOut, 128, 255, cv::THRESH_BINARY);
		//设置输出图像
		CInputOutputInfo info(DataType::TYPE_IMAGE);
		info.SetImageValue(imgOut);
		m_vectOutput[3]->SetValue(info);


		//设置显示图像

		CInputOutputInfo infoShow(DataType::TYPE_IMAGE);
		infoShow.SetImageValue(imgOut.clone());
		m_vectOutput[2]->SetValue(infoShow);

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
bool CBilateralFilter::Set()
{


 	CBilateralFilterSet setF(this);

	
	setF.exec();
	if (setF.result() == QDialog::Accepted)
	{
		return true;
	}
	return false;
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




CAlgrithmBase* CBilateralFilter::CreateAlgrithm()
{
	return new CBilateralFilter();
}

//虚构造函数
CAlgrithmBase* CBilateralFilter::Clone()
{
	return new CBilateralFilter(*this);
}


void CBilateralFilter::Clone(const CBilateralFilter& rhs) //用于复制构造函数和赋值操作符使用 
{
	__super::Clone(rhs);
	m_nDiameter = rhs.m_nDiameter;
	m_dbSigmaColor = rhs.m_dbSigmaColor;
	m_dbSigmaSpace = rhs.m_dbSigmaSpace;
}


IML_REFLECT_CLASS(CBilateralFilter)




// void CBilateralFilter::RegistClass()
// {
// 	CAlgrithmBase::m_mapCreatedFucn.insert(std::make_pair("CBilateralFilter", CBilateralFilter::CreateAlgrithm));
// }
