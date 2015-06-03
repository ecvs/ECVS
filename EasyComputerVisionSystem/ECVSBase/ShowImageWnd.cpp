#include "stdafx.h"
#include "ShowImageWnd.h"
#include <windows.h>
#include <QWheelEvent>
#include <QMoveEvent>
CShowImageWnd::CShowImageWnd(QWidget *parent)
: QFrame(parent)
{
	
// 	QStringList colorNameList = QColor::colorNames();
// 	QColor m_color = QColor(colorNameList[cbbBase->currentIndex()]);
// 	QPalette p = contentFrame->palette();
// 	p.setColor(QPalette::Base, m_color);
// 	contentFrame->setPalette(p);

// 	QPalette palette = this->palette();
// 
// 	palette.setColor(QPalette::Base, QColor(0, 0, 0));
// 
// 
// 	this -> setPalette(palette);
// 	setMouseTracking
	setStyleSheet("border:1px solid black");
	this->setStyleSheet("background-color:black;");
	setAutoFillBackground(true);
	setMouseTracking(true);
	
}

CShowImageWnd::~CShowImageWnd()
{

}


void CShowImageWnd::paintEvent(QPaintEvent *event)
{
	//QPainter p;
	QPainter painter;
	painter.begin(this);

	if (m_matShowImgClone.data != NULL)
	{
		painter.drawImage(m_rectShowImgRect, m_imgShow);
	}
	

	painter.end();
}

void CShowImageWnd::wheelEvent(QWheelEvent *event)
{

	if (m_bCanEditView)
	{
		if (m_matShowImg.data == NULL)
		{
			return __super::wheelEvent(event);

		}
		if (event->delta() == 120)
		{
			
			Enlarge(true, event->pos());
		}
		else if (event->delta() == -120)
		{
		
			Enlarge(false, event->pos());
		}
		update();
	}
	return __super::wheelEvent(event);
}
void CShowImageWnd::mouseMoveEvent(QMouseEvent* event)   //鼠标移动消息
{

	Qt::MouseButtons btns = event->buttons();
	if ( (event->buttons() ^ Qt::MouseButton::MiddleButton) == 0)  //只有鼠标中键按下
	{
		
		QPoint point = event->pos();
		m_rectShowImgRect.setLeft(m_rectShowImgRect.left() + (point.rx() - m_ptPrev.rx()));
		m_rectShowImgRect.setRight(m_rectShowImgRect.right() + (point.rx() - m_ptPrev.rx()));
// 
		m_rectShowImgRect.setTop(m_rectShowImgRect.top() + (point.ry() - m_ptPrev.ry()));
		m_rectShowImgRect.setBottom(m_rectShowImgRect.bottom() + (point.ry() - m_ptPrev.ry()) );
// 
// 
// 		m_ptCoordinateOffset.x += (point.x - m_ptPrev.x);
// 		m_ptCoordinateOffset.y += (point.y - m_ptPrev.y);

		update();
	}
	m_ptPrev = event->pos();
	return __super::mouseMoveEvent(event);
}
bool CShowImageWnd::GetBackImg(Mat& imgBack) //获取后台图像
{
	if (m_matShowImg.data == NULL)
	{
		return false;
	}
	else
	{
		imgBack = m_matShowImg;
		return TRUE;
	}
}
void CShowImageWnd::SetImage(Mat img)
{

	bool bFixWnd = false;

	//如果图像的大小或者通道数改变了，那么重新分配资源，
	if (m_matShowImg.cols != img.cols ||
		m_matShowImg.rows != img.rows ||
		m_matShowImg.channels() != img.channels())
	{
		Init(img.rows, img.cols, img.channels());
		Init();
		bFixWnd = true;
		
	}

	m_matShowImg = img;  //赋值后台图像
	m_matShowImgClone = m_matShowImg.clone(); //显示图像
	if (m_matShowImg.channels() == 1) //灰度图
	{

		cvtColor(m_matShowImgClone, m_matShowImgClone, CV_GRAY2RGB); //图像转换成3通道RGB图
	}
	else
	{
		cvtColor(m_matShowImgClone, m_matShowImgClone, CV_BGR2RGB);
	}
	m_imgShow = QImage((const uchar*)(m_matShowImgClone.data), m_matShowImgClone.cols, m_matShowImgClone.rows, QImage::Format_RGB888);
	m_imgShow.bits();
	if (bFixWnd)
	{
		::SendMessage((HWND)this->winId(), WM_SHOWIMGFIXWINDOW, (WPARAM)img.rows, (LPARAM)img.cols);
	}
	update();
}

bool CShowImageWnd::Init()
{
	m_rectShowImgRect.setLeft ( 0);
	m_rectShowImgRect.setTop ( 0);
	m_rectShowImgRect.setRight ( m_nCols);
	m_rectShowImgRect.setBottom ( m_nRows);

	return true;
}
bool CShowImageWnd::Delete()
{

	return true;
}
bool CShowImageWnd::Init(int nRows, int nClos, int nChannels)
{
	nChannels = 3; //显示图像都是显示3通道的 ，后台图像保存实际图像


// 
 	m_nCurRate = 0;
 	m_dbShowPersent = 100; 
	m_nCols = nClos;
	m_nRows = nRows;

	return true;
}

//响应Windows 消息
bool CShowImageWnd::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	if (eventType == "windows_generic_MSG")
	{
		PMSG msg = (PMSG)message;
		if (msg->message == WM_SHOWIMGFIXWINDOW)
		{
			
			OnShowImgFixWindow();
			return true;
		}
	}
	return __super::nativeEvent(eventType, message, result);
}

void CShowImageWnd::OnShowImgFixWindow(/*int nRows, int nCols*/)
{
	if (m_matShowImg.data == NULL)
	{
		return;
	}
	else
	{
		
		const QRect& clientRect = rect();
	//	GetClientRect(clientRect);
		//图像比窗口大的情况

		if (m_rectShowImgRect.width() > clientRect.width() || m_rectShowImgRect.height() > clientRect.height())
		{
			//缩小到长宽都比客户区短
			while (TRUE)
			{
				Enlarge(false, m_rectShowImgRect.center());

				if (   m_rectShowImgRect.width()  <= clientRect.width()
					&& m_rectShowImgRect.height() <= clientRect.height())
				{
					break;
				}
			}

			//到这里大小已经合适
		}
		else  //这里两边都比客户区小，首先将一条边变得比客户区大，然后再缩小1次
		{
			while (TRUE)
			{
				Enlarge(true, m_rectShowImgRect.center());
				//一条边比客户区大
				if (m_rectShowImgRect.width() > clientRect.width() || m_rectShowImgRect.height() > clientRect.height())
				{
					break;
				}
			}

			Enlarge(false, m_rectShowImgRect.center());
		}

		//到这里边的长度已经变得合适，再将显示矩形移动到客户区中心
		int nWidth = m_rectShowImgRect.width();
		m_rectShowImgRect.setLeft ( clientRect.center().rx()  - nWidth / 2.0);
		m_rectShowImgRect.setRight ( m_rectShowImgRect.left() + nWidth);

		int nHeight = m_rectShowImgRect.height();
		QPoint pt = clientRect.center();
		m_rectShowImgRect.setTop ( clientRect.center().ry() - nHeight / 2.0);
		m_rectShowImgRect.setBottom ( m_rectShowImgRect.top() + nHeight);
		//Invalidate();
		update();

	}
}

void CShowImageWnd::Enlarge(bool bEnlarge, QPointF ptCenter)
{


	if (m_matShowImg.data == NULL)
	{
		return;
	}
	//放大显示区域
	if (bEnlarge)
	{
		if (m_nCurRate > MAXRATE)
		{
			return;
		}
		++m_nCurRate;
		double dbWidth;
		double dbHeight;
		if (m_nCurRate == 0)
		{
			dbHeight = m_nRows;
			dbWidth = m_nCols;
			m_dbShowPersent = 100;
		}
		else
		{
			dbWidth = m_rectShowImgRect.width() + ((double)m_rectShowImgRect.width()) / ((double)(ONEPERCENT - 1));
			dbHeight = m_rectShowImgRect.height() + ((double)m_rectShowImgRect.height()) / ((double)(ONEPERCENT - 1));
			m_dbShowPersent *= (1 + 1.0 / (ONEPERCENT - 1));

		}

	
		double dbOffX = -(dbWidth - m_rectShowImgRect.width())*(ptCenter.rx() - m_rectShowImgRect.left()) / ((double)m_rectShowImgRect.width());
		double dbOffY = -(dbHeight - m_rectShowImgRect.height())*(ptCenter.ry() - m_rectShowImgRect.top()) / ((double)m_rectShowImgRect.height());

		double dbX = m_rectShowImgRect.left() + dbOffX;// (dbWidth - m_rectShowImgRect.Width())*(ptCenter.x - m_rectShowImgRect.left) / ((double)m_rectShowImgRect.Width());
		double dbY = m_rectShowImgRect.top() + dbOffY;// (dbHeight - m_rectShowImgRect.Height())*(ptCenter.y - m_rectShowImgRect.top) / ((double)m_rectShowImgRect.Height());

		m_ptCoordinateOffset.rx() += dbOffX;
		m_ptCoordinateOffset.ry() += dbOffY;
		m_rectShowImgRect.setLeft(dbX);
	
		m_rectShowImgRect.setRight( dbX + dbWidth);
		m_rectShowImgRect.setTop( dbY);
		m_rectShowImgRect.setBottom ( dbY + dbHeight);


	}
	else  //缩小显示区域
	{
		if (m_nCurRate < MINRATE)
		{
			return;
		}
		--m_nCurRate;

		double dbWidth;
		double dbHeight;
		if (m_nCurRate == 0)
		{
			dbHeight = m_nRows;
			dbWidth = m_nCols;
			m_dbShowPersent = 100;
		}
		else
		{
			dbWidth = m_rectShowImgRect.width() - ((double)m_rectShowImgRect.width()) / ((double)(ONEPERCENT));
			dbHeight = m_rectShowImgRect.height() - ((double)m_rectShowImgRect.height()) / ((double)(ONEPERCENT));
			m_dbShowPersent *= (1 - 1.0 / ONEPERCENT);
		}

		double dbOffX = -(dbWidth - m_rectShowImgRect.width())*(ptCenter.x() - m_rectShowImgRect.left()) / ((double)m_rectShowImgRect.width());
		double dbOffY = -(dbHeight - m_rectShowImgRect.height())*(ptCenter.y() - m_rectShowImgRect.top()) / ((double)m_rectShowImgRect.height());
		double dbX = m_rectShowImgRect.left() + dbOffX;
		double dbY = m_rectShowImgRect.top() + dbOffY;

		m_ptCoordinateOffset.rx() += dbOffX;
		m_ptCoordinateOffset.ry() += dbOffY;

		m_rectShowImgRect.setLeft ( dbX);
		m_rectShowImgRect.setRight( dbX + dbWidth);
		m_rectShowImgRect.setTop ( dbY);
		m_rectShowImgRect.setBottom ( dbY + dbHeight);

	}
}
// void CShowImageWnd::Enlarge(bool bEnlarge, QPointF ptCenter)
// {
// 	Enlarge(bEnlarge, QPoint(ptCenter.rx(), ptCenter.ry()));
// }
void CShowImageWnd::EnlargeCenter(bool bEnlarge)  //以图像中心点为基准缩放
{
	QPointF ptCenter = m_rectShowImgRect.center();

	Enlarge(bEnlarge, ptCenter);
}
void CShowImageWnd::ShowImgFixSize()
{
	::SendMessage((HWND)this->winId(), WM_SHOWIMGFIXWINDOW, (WPARAM)0, (LPARAM)0);
}