#include "stdafx.h"
/*#include "ShowImageWnd.h"*/
#include "ECVSBase.h"
#include <QtWidgets/QPushButton>
#include "BilateralFilterSet.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
using namespace cv;
#include <QMenu>
CBilateralFilterSet::CBilateralFilterSet(QWidget *parent)
: QDialog(parent)
{
	
	ui.setupUi(this);
	m_pShowImgWnd = new CShowImageWnd(ui.frame);



	ui.frame->setStyleSheet("border:1px solid black");
	ui.frame->setAutoFillBackground(true);
	m_pMenu = new QMenu(this);
}

CBilateralFilterSet::~CBilateralFilterSet()
{

}

void CBilateralFilterSet::resizeEvent(QResizeEvent *e)
{
	QDialog::resizeEvent(e);
	QRect rect = ui.frame->geometry();
	int nW = rect.width();
	int nH = rect.height();
	rect.setLeft(0);
	rect.setTop(0);
	rect.setWidth(nW);
	rect.setHeight(nH);
	m_pShowImgWnd->setGeometry(rect);
}

