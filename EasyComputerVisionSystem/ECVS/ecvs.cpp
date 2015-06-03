#include "ecvs.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include <QDockWidget>
#include <QtWidgets/QtWidgets>
#include <QTreeWidget>
#include <QFileDialog>
#include <QDialog>
#include <BilateralFilter.h>
ECVS::ECVS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pShowImgWnd = new CShowImageWnd(this);
	setCentralWidget(m_pShowImgWnd);
	createDockWindows();
	createMenu();
	setUnifiedTitleAndToolBarOnMac(true);
}

ECVS::~ECVS()
{

}

void ECVS::resizeEvent(QResizeEvent *e)
{
 	QMainWindow::resizeEvent(e);
// 	QRect rect = ui.dockWidgetObjList->geometry();
// 	int nW = rect.width();
// 	int nH = rect.height();
// 	rect.setLeft(0);
// 	rect.setTop(0);
// 	rect.setWidth(nW);
// 	rect.setHeight(nH);
//	ui.listViewObjList->setGeometry(rect);
}
void ECVS::createDockWindows()
{

	QDockWidget *dock;

	dock = new QDockWidget(QStringLiteral("对象列表"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_objList = new QListWidget(dock);



	dock->setWidget(m_objList);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	ui.menuView->addAction(dock->toggleViewAction());

	dock = new QDockWidget(QStringLiteral("工具箱"), this);
	InitObjSet();
	dock->setWidget(m_objSet);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	ui.menuView->addAction(dock->toggleViewAction());


	dock = new QDockWidget(QStringLiteral("调试"), this);
	addDockWidget(Qt::BottomDockWidgetArea, dock);
	m_pDebugTest = new QTextEdit(dock);
	dock->setWidget(m_pDebugTest);
	ui.menuView->addAction(dock->toggleViewAction());
}

//初始化工具集合
void ECVS::InitObjSet()
{
	m_objSet = new QTreeWidget(this);
	m_objSet->setHeaderHidden(true);


	//图像获取工具
	QTreeWidgetItem* pGetImg = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("图像获取")));

	//图像预处理工具
	QTreeWidgetItem* pPreImg = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("图像预处理")));
	QTreeWidgetItem*pTreeWidgetTemp = new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("双边滤波")));
	CBilateralFilter biFilter;
	string strName = biFilter.GetAlgrithmClassName();
	pTreeWidgetTemp->setData(0, Qt::UserRole, QVariant(strName.c_str()));
	 

	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("高斯模糊")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("中值模糊")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("Sobel变换")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("Canny边缘")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("膨胀")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("腐蚀")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("开运算")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("闭运算")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("金字塔")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("归一化")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("对比度增强")));
	new QTreeWidgetItem(pPreImg, QStringList(QStringLiteral("二值化")));




	//测量
	QTreeWidgetItem* pMeasure = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("测量")));

	//模板定位
	QTreeWidgetItem* pMatchModel = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("定位")));

	//数学运算
	QTreeWidgetItem* pMathCalc = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("数学工具")));


	//代码工具
	QTreeWidgetItem* pCode = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("代码工具")));



	//插件功能
	QTreeWidgetItem* pPlugins = new QTreeWidgetItem(m_objSet, QStringList(QStringLiteral("插件")));

	//void itemDoubleClicked(QTreeWidgetItem *item, int column);
	//信号连接
	
	connect(m_objSet, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int )), this, SLOT(OnAddTools(QTreeWidgetItem *, int )));


}


void ECVS::createMenu()
{
	//ui.menuFile

	m_actOpenImg = new QAction(QStringLiteral("&打开图片"), this);
	//m_actOpenImg->setShortcuts(QKeySequence::Save);
	m_actOpenImg->setStatusTip(tr("打开图片"));
	connect(m_actOpenImg, SIGNAL(triggered()), this, SLOT(OpenImg()));

	ui.menuFile->addAction(m_actOpenImg);
	//ui.menuFile->addAction(m_actSaveImg);
}

void ECVS::OpenImg()
{
	QFileDialog openImg(this);
	openImg.setWindowTitle(QStringLiteral("打开图片"));
	openImg.setNameFilter(QStringLiteral("Image Files(*.jpg *.png *.bmp)"));
	if (openImg.exec() == QDialog::Accepted)
	{
		QString path = openImg.selectedFiles()[0];
		QByteArray byteArray = path.toLocal8Bit();
		string strPath = byteArray.toStdString();
		m_pShowImgWnd->SetImage(cv::imread(strPath.c_str()));
	}
}

//双击工具，添加工具
void ECVS::OnAddTools(QTreeWidgetItem *item, int column)
{
	QString str = item->text(0);
	QVariant var = item->data(0, Qt::UserRole);
	if (var.isValid())
	{
		QString qstrData = var.toString();
		string strData = qstrData.toLocal8Bit().toStdString();
		AddVisionTool(strData);

	}
	
}
//通过流程名字来添加算法工具，软件内置的算法还是需要通过if else 来
void ECVS::AddVisionTool(string strData)
{
	CAlgrithmBase *pAlgrithm = CAlgrithmBase::CreateAlgrithm(strData);
	//内置的算法
	if (pAlgrithm != NULL)
	{
		if (pAlgrithm->Set())
		{
			AddAlgrithm(pAlgrithm);
		}

		delete pAlgrithm;
		pAlgrithm = NULL;
	}
	else //内置算法里面没有功能，那么去插件功能里面找，
	{

	}
}

void ECVS::AddAlgrithm(CAlgrithmBase* pAlgrithm)
{
	m_nCurIndex;
	m_flowProcess;
	//添加算法
	if (m_flowProcess.size() == 0)  //位流程为空时
	{
		CFlowProcess pro;
		pro.AddAlgrithm(pAlgrithm);//AddAlgrithm 里面自己重新分配存储空间，外面的空间需要外面释放
		m_flowProcess.push_back(pro);
		m_nCurIndex = 0;
	}
	else //如果不为空
	{
		CFlowProcess flow = m_flowProcess[m_nCurIndex];  //取当前的流程
		flow.AddAlgrithm(pAlgrithm);  //
		m_flowProcess.erase(m_flowProcess.begin() + m_nCurIndex + 1, m_flowProcess.end()); //删除尾巴
		m_flowProcess.push_back(flow); //添加
		m_nCurIndex = m_flowProcess.size() - 1; //设置标号
		
	}

}