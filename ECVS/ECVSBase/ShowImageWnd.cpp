// ShowImageWnd.cpp : 实现文件
//

#include "stdafx.h"
#include <cxcore.h>
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
#include "opencv2/imgproc.hpp"
using cv::Mat;
using cv::Point;
using cv::Point2f;
#include "ECVSBase.h"
#include "ShowImageWnd.h"


// CShowImageWnd

IMPLEMENT_DYNAMIC(CShowImageWnd, CStatic)

CShowImageWnd::CShowImageWnd() : m_backBrush(RGB(0,0,0))
{
	//初始化成员
	m_hMemdc = NULL;
	m_pBmpInfo = NULL;
	m_hImage = NULL;
	m_pImg = NULL;
	m_pParentWnd = NULL;
	m_hBmpCompatible = NULL;
	m_hdcDraw = NULL;
	m_hdcDoubleBuffer = NULL;
}

CShowImageWnd::~CShowImageWnd()
{
}


BEGIN_MESSAGE_MAP(CShowImageWnd, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CShowImageWnd 消息处理程序

//绘制函数
void CShowImageWnd::OnPaint()
{
	CPaintDC dc(this); //获取DC
	::SetStretchBltMode(dc.m_hDC, STRETCH_HALFTONE);

	StretchBlt(dc.m_hDC, m_rectShowImgRect.left, m_rectShowImgRect.top,
		m_rectShowImgRect.Width(), m_rectShowImgRect.Height(), m_hMemdc, 0, 0,
		m_matShowImg.cols, m_matShowImg.rows, SRCCOPY);
}


void CShowImageWnd::SetImage(Mat img)
{

	//如果图像的大小或者通道数改变了，那么重新分配资源，
	if (m_matShowImg.cols != img.cols||
		m_matShowImg.rows != img.rows ||
		m_matShowImg.channels() != img.channels())
	{
		Init(img.rows, img.cols, img.channels());
		Init();
		PostMessage(WM_SHOWIMGFIXWINDOW, 0, 0);
	}

	m_matShowImg = img;  //赋值后台图像
	m_matShowImgClone = m_matShowImg.clone(); //显示图像
	if (m_matShowImg.channels() == 1) //灰度图
	{
		
		cvtColor(m_matShowImgClone, m_matShowImgClone, CV_GRAY2BGR); //图像转换成3通道RGB图
	}


	//拷贝图像数据
	CvMat stub, dst, *image;
	SIZE size;
	size.cx = m_matShowImgClone.cols;
	size.cy = m_matShowImgClone.rows;
	//CvArr arr = m;
	CvMat c_mat = m_matShowImgClone;
	IplImage lpimg = m_matShowImgClone;
	CvArr* arr = &c_mat;
	int origin = lpimg.origin;
	cvInitMatHeader(&dst, size.cy, size.cx, CV_8UC3,
		m_pImg, (size.cx * m_matShowImgClone.channels() + 3) & -4);
	image = cvGetMat(arr, &stub);
	cvConvertImage(image, &dst, origin == 0 ? CV_CVTIMG_FLIP : 0);


	//	delete []pSrc;
	Invalidate();
}


bool CShowImageWnd::Init()
{
	m_rectShowImgRect.left = 0;
	m_rectShowImgRect.top = 0;
	m_rectShowImgRect.right = m_nCols;
	m_rectShowImgRect.bottom = m_nRows;
	return true;
}
bool CShowImageWnd::Init(int nRows, int nClos, int nChannels)
{

	nChannels = 3; //显示图像都是显示3通道的 ，后台图像保存实际图像
	
	//清空资源
	if (m_hMemdc != NULL)
	{
		
		HGDIOBJ hSelection = ::SelectObject(m_hMemdc, m_hImage);
		DeleteObject(hSelection);
		DeleteObject(m_hImage);
		DeleteDC(m_hMemdc);
		m_hMemdc = NULL;
	}
	if (m_pBmpInfo != NULL)
	{
		char *p = (char*)m_pBmpInfo;
		delete[] p;
		p = NULL;
	}

	m_nCurRate = 0;
	m_dbShowPersent = 100; // 
	m_nCols = nClos;
	m_nRows = nRows;
	m_hMemdc = ::CreateCompatibleDC(NULL);
	m_pBmpInfo = (BITMAPINFO*)(new char[sizeof(BITMAPINFOHEADER)+256 * sizeof(RGBQUAD)]);
	m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth = m_nCols;
	m_pBmpInfo->bmiHeader.biHeight = m_nRows;
	m_pBmpInfo->bmiHeader.biPlanes = 1;
	m_pBmpInfo->bmiHeader.biBitCount = (UINT16)(nChannels * 8);
	m_pBmpInfo->bmiHeader.biCompression = BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage = m_nCols*m_nRows * 1;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biClrUsed = 256;
	m_pBmpInfo->bmiHeader.biClrImportant = 0;

	for (int i = 0; i < 256; ++i)
	{
		m_pBmpInfo->bmiColors[i].rgbRed = (UINT8)i;
		m_pBmpInfo->bmiColors[i].rgbGreen = (UINT8)i;
		m_pBmpInfo->bmiColors[i].rgbBlue = (UINT8)i;
		m_pBmpInfo->bmiColors[i].rgbReserved = 0;
	}

	HANDLE hSelection = CreateDIBSection(m_hMemdc, m_pBmpInfo, DIB_RGB_COLORS, &m_pImg, 0, 0);

	m_hImage = ::SelectObject(m_hMemdc, hSelection);


	return true;
}
bool CShowImageWnd::Delete()
{
	if (m_hMemdc != NULL)
	{

		HGDIOBJ hSelection = ::SelectObject(m_hMemdc, m_hImage);
		DeleteObject(hSelection);
		DeleteObject(m_hImage);
		DeleteDC(m_hMemdc);
		m_hMemdc = NULL;
	}
	if (m_pBmpInfo != NULL)
	{
		char*p = (char*)m_pBmpInfo;
		delete[] p;
		m_pBmpInfo = NULL;
	}
	if (m_hdcDraw != NULL)
	{
		::DeleteDC(m_hdcDraw);
		m_hdcDraw = NULL;
	}
	if (m_hBmpCompatible != NULL)
	{
		DeleteObject(m_hBmpCompatible);
		m_hBmpCompatible = NULL;
	}
	if (m_hdcDoubleBuffer != NULL)
	{
		::DeleteObject(m_hdcDoubleBuffer);
		m_hdcDoubleBuffer = NULL;
	}
	return true;
}