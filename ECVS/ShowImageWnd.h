#pragma once

//显示图像窗口，所有该系统默认显示图像窗口 都使用这个，最基本的窗口，
//可以被继承 2015-5-22

// CShowImageWnd
#define  WM_SHOWIMGFIXWINDOW WM_USER + 5017  //自定义消息，用于适应窗口显示图片
enum ShowImageWndOperator
{
	OperatorNone,   //无任何操作,默认为选择操作
	OperatorMoveObj, //移动对象
	OperatorZoomLeft,
	OperatorZoomLeftTop,
	OperatorZoomTop,
	OperatorZoomRightTop,
	OperatorZoomRight,
	OperatorZoomRightBottom,
	OperatorZoomBottom,
	OperatorZoomLeftBottom,

};

class ECVS_EXPORT CShowImageWnd : public CStatic
{
	DECLARE_DYNAMIC(CShowImageWnd)

public:
	CShowImageWnd();
	virtual ~CShowImageWnd();


public:
	afx_msg void OnPaint();

	// 设置显示图像
	void SetImage(Mat img);  //////////////////////////////////////////////////////////////////////////
	void SetParentWnd(CWnd* pPrarent)
	{
		m_pParentWnd = pPrarent;
	}

protected:
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_backBrush; //背景画刷
	CWnd*	m_pParentWnd; //父窗口
	//用于绘图操作
	HDC		m_hdcDraw;
	HBITMAP	m_hBmpCompatible;
	HDC		m_hdcDoubleBuffer;
	CRect	m_rectShowImgRect; // 显示图像的窗口
	HGDIOBJ			m_hImage;
	void*			m_pImg;
	BITMAPINFO*		m_pBmpInfo;
	HDC				m_hMemdc;

	//图像
	Mat			m_matShowImg;
	Mat			m_matShowImgClone;
	int m_nCols, m_nRows;  //当前图像的长宽
	ShowImageWndOperator m_OperatorOnView;


	//用于图像缩放操作的变量
	int m_nCurRate;      //当前倍率，放大 缩小次数
	double	m_dbShowPersent;  //当前显示图像的百分比
	CPoint		m_ptCoordinateOffset; //图像显示矩形相对于左上角的偏移量

private:  //私有方法

	//分配资源和删除资源函数
	bool Init();
	bool Init(int nRows, int nClos, int nChannels);
	bool Delete();

	//放大或缩小显示区域，bEnlarge = true 放大， ptCenter 为放大的中心点
	void Enlarge(bool bEnlarge, CPoint ptCenter);
	void EnlargeCenter(bool bEnlarge);  //以图像中心点为基准缩放
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


