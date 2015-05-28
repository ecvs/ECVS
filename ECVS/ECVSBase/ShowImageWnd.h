#pragma once
#include <QtWidgets/QGraphicsView>
#include "ECVSBase.h"
QT_END_NAMESPACE
class ECVS_EXPORT CShowImageWnd :QGraphicsView
{
	Q_OBJECT
public:
	CShowImageWnd(QWidget *parent = 0);
	~CShowImageWnd();

private:
	Mat m_matShowImg;
	Mat			m_matShowImgClone;
	QImage m_image;
	int m_nCols, m_nRows;  //当前图像的长宽

public slots:
	
protected:
	void wheelEvent(QWheelEvent *event);
	void paintEvent(QPaintEvent *event);


};

