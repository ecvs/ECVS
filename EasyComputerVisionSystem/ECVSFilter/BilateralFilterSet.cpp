#include "stdafx.h"
/*#include "ShowImageWnd.h"*/
#include "FilterCommon.h"
#include "ECVSBase.h"
#include <QtWidgets/QPushButton>
#include "BilateralFilterSet.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QtWidgets/QToolBox>
using namespace cv;
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QFileDialog>
#include <QDockWidget>

#include "BilateralFilter.h"
CBilateralFilterSet::CBilateralFilterSet(CBilateralFilter* pOwer, QWidget *parent)
: m_pOwerFilter(pOwer),QDialog(parent)
{

// 	QVBoxLayout *mainLayout = new QVBoxLayout(this);
// 	QToolBox *toolbox = new QToolBox();
// 	mainLayout->addWidget(toolbox);

	ui.setupUi(this);
	m_pShowImgWnd = new CShowImageWnd(ui.frame);



	ui.frame->setStyleSheet("border:1px solid black");
	ui.frame->setAutoFillBackground(true);
	
	
	QToolBar *toolBar = new QToolBar(this);
	ui.horizontalLayout_5->addWidget(toolBar);
	//添加打开图片按钮
	QToolButton*pToolButtonOpenImgs = new QToolButton(this);
	pToolButtonOpenImgs->setText(QStringLiteral("打开图片"));
	pToolButtonOpenImgs->setIcon(QPixmap(":/BilateralFilter/open.png"));
	pToolButtonOpenImgs->setIconSize(QPixmap(":/BilateralFilter/open.png").size());
	pToolButtonOpenImgs->setToolTip(QStringLiteral("打开图片")); 
	toolBar->addWidget(pToolButtonOpenImgs);
	//从相机获取图片
	QToolButton *pToolButtonGetImgs = new QToolButton(this);
	pToolButtonGetImgs->setText(QStringLiteral("拍照"));
	toolBar->addWidget(pToolButtonGetImgs);

	QToolButton*pToolButtonShowOrgImg = new QToolButton(this);
	pToolButtonShowOrgImg->setText(QStringLiteral("显示原图"));
	toolBar->addWidget(pToolButtonShowOrgImg);

	QToolButton*pToolButtonShowFilterImg = new QToolButton(this);
	pToolButtonShowFilterImg->setText(QStringLiteral("处理图"));
	toolBar->addWidget(pToolButtonShowFilterImg);

	QToolButton*pToolButtonShowFixSize= new QToolButton(this);
	pToolButtonShowFixSize->setText(QStringLiteral("图像适应窗口"));
	toolBar->addWidget(pToolButtonShowFixSize);

	//connect()
	connect(pToolButtonOpenImgs, SIGNAL(clicked()), SLOT(OnOpenImg()));
	connect(pToolButtonShowFixSize, SIGNAL(clicked()), SLOT(OnShowFixSize()));
	


	//最大化最小化按钮
	Qt::WindowFlags flags = Qt::Window;
	setWindowFlags(flags);
	
	//设置参数的取值范围
	ui.horizontalSliderD->setRange(1, 20);  //D 1 ~ 20
	ui.horizontalSliderSigmaColor->setRange(1, 255); //SigmaColor 1~255
	ui.horizontalSliderSigmaSpace->setRange(1, 255); //SigmaSpace 1~255
	ui.spinBoxD->setRange(1, 20);  //D 1 ~ 20
	ui.spinBoxSigmaColor->setRange(1, 255); //SigmaColor 1~255
	ui.spinBoxSigmaSpace->setRange(1, 255); //SigmaSpace 1~255
	ui.spinBoxD->setValue(m_pOwerFilter->m_nDiameter);
	ui.spinBoxSigmaColor->setValue(m_pOwerFilter->m_dbSigmaColor);
	ui.spinBoxSigmaSpace->setValue(m_pOwerFilter->m_dbSigmaSpace);
	ui.horizontalSliderD->setValue(m_pOwerFilter->m_nDiameter);
	ui.horizontalSliderSigmaColor->setValue(m_pOwerFilter->m_dbSigmaColor);
	ui.horizontalSliderSigmaSpace->setValue(m_pOwerFilter->m_dbSigmaSpace);
	//信号和槽的链接
	connect(ui.horizontalSliderD, SIGNAL(valueChanged(int)), SLOT(OnSliderDChanged(int)));
	connect(ui.horizontalSliderSigmaColor, SIGNAL(valueChanged(int)), SLOT(OnSliderSigmaColorChanged(int)));
	connect(ui.horizontalSliderSigmaSpace, SIGNAL(valueChanged(int)), SLOT(OnSliderSigmaSpaceChanged(int)));
	connect(ui.spinBoxD, SIGNAL(valueChanged(int)), SLOT(OnSpinDChanged(int)));
	connect(ui.spinBoxSigmaColor, SIGNAL(valueChanged(int)), SLOT(OnSpinSigmaColorChanged(int)));
	connect(ui.spinBoxSigmaSpace, SIGNAL(valueChanged(int)), SLOT(OnSpinSigmaSpaceChanged(int)));

	connect(ui.OKBtn, SIGNAL(clicked()), SLOT(OnOkClicked()));
	connect(ui.CancelBtn, SIGNAL(clicked()), SLOT(OnCancelClicled()));

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

void CBilateralFilterSet::OnOpenImg()
{

	//QString path = QFileDialog::getOpenFileName(this, QStringLiteral("打开图片"), ".", QStringLiteral("Image Files(*.jpg *.png *.bmp)"));

 	QFileDialog openImg(this);
	openImg.setWindowTitle(QStringLiteral("打开图片"));
	QDir dir;
	QStringList listFtr;
	listFtr.append("*.jpg");
	listFtr.append("*.bmp");
	listFtr.append("*.png");
	dir.setNameFilters(listFtr);
	QDir::Filters ftr;
	
	openImg.setNameFilter(QStringLiteral("Image Files(*.jpg *.png *.bmp)"));
/*	openImg.setDirectory(".");**/
	if (openImg.exec() == Accepted)
	{
		QString path = openImg.selectedFiles()[0];
		
		m_imgProcessed = imread(path.toStdString().c_str());
		BilateralFilterParamChanged(); //打开图片时需要进行一次滤波操作
		//m_pShowImgWnd->SetImage(m_imgProcessed);
	}

}
void CBilateralFilterSet::OnShowFixSize()
{
	m_pShowImgWnd->ShowImgFixSize();
}
void CBilateralFilterSet::OnSliderDChanged(int nValue)
{

	if (ui.spinBoxD->value() != nValue)
	{
		ui.spinBoxD->setValue(nValue);
		BilateralFilterParamChanged();
	}
}


void CBilateralFilterSet::OnSliderSigmaColorChanged(int nValue)
{
	
	if (ui.spinBoxSigmaColor->value() != nValue)
	{
		ui.spinBoxSigmaColor->setValue(nValue);
		BilateralFilterParamChanged();
	}

}

void CBilateralFilterSet::OnSliderSigmaSpaceChanged(int nValue)
{
	if (ui.spinBoxSigmaSpace->value() != nValue)
	{
		ui.spinBoxSigmaSpace->setValue(nValue);
		BilateralFilterParamChanged();
	}
	

}

void CBilateralFilterSet::OnSpinDChanged(int nValue)
{
	if (ui.horizontalSliderD->value() != nValue)
	{
		ui.horizontalSliderD->setValue(nValue);
		BilateralFilterParamChanged();
	}
}
void CBilateralFilterSet::OnSpinSigmaColorChanged(int nValue)
{
	if (ui.horizontalSliderSigmaColor->value() != nValue)
	{
		ui.horizontalSliderSigmaColor->setValue(nValue);
		BilateralFilterParamChanged();
	}
}
void CBilateralFilterSet::OnSpinSigmaSpaceChanged(int nValue)
{
	if (ui.horizontalSliderSigmaSpace->value() != nValue)
	{
		ui.horizontalSliderSigmaSpace->setValue(nValue);
		BilateralFilterParamChanged();
	}
}

void CBilateralFilterSet::BilateralFilterParamChanged()
{
	if (m_imgProcessed.data != NULL) //当有图像时，进行处理
	{
		::PostMessage((HWND)this->winId(), BILATERAL_FILTER_PARAM_CHANGE, 0, 0);
	}
	
}

bool CBilateralFilterSet::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	if (eventType == "windows_generic_MSG")
	{
		PMSG msg = (PMSG)message;
		if (msg->message == BILATERAL_FILTER_PARAM_CHANGE)
		{

			OnBilateralFilter();
			return true;
		}
	}
	return __super::nativeEvent(eventType, message, result);
}

void CBilateralFilterSet::OnBilateralFilter()
{
	Mat imgProcessd;


	imgProcessd = m_pOwerFilter->Run(m_imgProcessed, ui.spinBoxD->value(), ui.spinBoxSigmaColor->value(), ui.spinBoxSigmaSpace->value()); //执行
	m_pShowImgWnd->SetImage(imgProcessd);
	
}

void CBilateralFilterSet::OnOkClicked()
{
	m_pOwerFilter->m_nDiameter = ui.spinBoxD->value();
	m_pOwerFilter->m_dbSigmaColor = ui.spinBoxSigmaColor->value();
	m_pOwerFilter->m_dbSigmaSpace = ui.spinBoxSigmaSpace->value();
	this->close();
}
void CBilateralFilterSet::OnCancelClicled()
{
	this->close();
}