#include "stdafx.h"
#include <string>
using std::string;
#include "ECVSBase.h"

//导入OpenCV
#ifdef _DEBUG
#pragma  comment(lib,"opencv_world300d.lib" )
#pragma  comment(lib, "opencv_ts300d.lib")
#pragma  comment(lib, "QT5Cored.lib")
#pragma  comment(lib, "Qt5Guid.lib")
#pragma  comment(lib, "Qt5Widgetsd.lib")

#else
#pragma  comment(lib, "opencv_ts300.lib")
#pragma  comment(lib,"opencv_world300.lib" )
#pragma  comment(lib, "QT5Core.lib")
#pragma  comment(lib, "Qt5Gui.lib")
#pragma  comment(lib, "Qt5Widgets.lib")
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