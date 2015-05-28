#include "stdafx.h"
#include <QtWidgets/QWidget>
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
#include "opencv2/imgproc.hpp"
using cv::Mat;
using cv::Point;
using cv::Point2f;
#include "ShowImageWnd.h"


CShowImageWnd::CShowImageWnd(QWidget *parent) : QGraphicsView(parent)
{

}


CShowImageWnd::~CShowImageWnd()
{
}

void CShowImageWnd::paintEvent(QPaintEvent *event)
{
// 	if (m_renderer == Image) {
// 		if (m_image.size() != viewport()->size()) {
// 			m_image = QImage(viewport()->size(), QImage::Format_ARGB32_Premultiplied);
// 		}
// 
// 		QPainter imagePainter(&m_image);
// 		QGraphicsView::render(&imagePainter);
// 		imagePainter.end();
// 
// 		QPainter p(viewport());
// 		p.drawImage(0, 0, m_image);
// 
// 	}
// 	else {
// 		QGraphicsView::paintEvent(event);
// 	}
}

void CShowImageWnd::wheelEvent(QWheelEvent *event)
{
// 	qreal factor = qPow(1.2, event->delta() / 240.0);
// 	scale(factor, factor);
// 	event->accept();
}

