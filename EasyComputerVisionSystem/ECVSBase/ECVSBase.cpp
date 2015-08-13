#include "stdafx.h"
#include <string>
using std::string;
#include "ECVSBase.h"
#include "AlgrithmBase.h"
#include "ECVSCamera.h"
//导入OpenCV
#ifdef _DEBUG
#pragma  comment(lib,"opencv_world300d.lib" )
#pragma  comment(lib, "opencv_ts300d.lib")
#else
#pragma  comment(lib, "opencv_ts300.lib")
#pragma  comment(lib,"opencv_world300.lib" )
#endif


string GetErrorMsg(int nCode)
{
	switch (nCode)
	{
	case ECVS_ERROR_NO_ERROR:
		return string("成功");
	case ECVS_ERR_HAS_NO_EXECUTE:
		return string("算法未执行");
	case ECVS_ERROR_HAS_NO_IMG_INPUT:
		return "没有图像输入";
	default:
		return string();
	//	break;
	}

}

QString StdStr2QString(string str)
{
	QByteArray byteArray = QByteArray::fromStdString(str);
	QString qStr = QString::fromLocal8Bit(byteArray);
	return qStr;
}
string  QString2StdStr(QString str)
{
	QByteArray byteArray = str.toLocal8Bit();
	string strStd = byteArray.toStdString();
	return strStd;
}




CAlgrithmBase* CreateAlgrithmGloble(string strAlgrithm)  //根据不同的string来创建算法实例
{
	CAlgrithmBase *pRet = NULL;


	//判断是不是相机ECVS_Camera
	string strCamera = "ECVS_Camera";
	if (strAlgrithm.size() > strCamera.size())
	{
		string strName(strAlgrithm.begin(), strAlgrithm.begin() + strCamera.size());
		if (strName == strCamera)
		{
			string strIndex(strAlgrithm.begin() + strCamera.size(), strAlgrithm.end());
			int nIndex = atoi(strIndex.c_str());
			if (nIndex >= 0 && nIndex < CECVSCamera::m_pCameras.size())
			{
				return CECVSCamera::m_pCameras[nIndex];
			}
			
		}
	}
	


	return pRet;
}