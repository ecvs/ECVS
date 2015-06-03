#ifndef ECVS_H
#define ECVS_H
#include <ECVSBaseHeader.h>
#include <ECVSBase.h>
#include <QtWidgets/QMainWindow>
#include <QListWidget>
#include <ShowImageWnd.h>
#include <vector>
#include <FlowProcess.h>
#include<QTreeWidget>
#include "ui_ecvs.h"
class QTextEdit;
class QTreeWidget;
using std::vector;
class ECVS : public QMainWindow
{
	Q_OBJECT

public:
	ECVS(QWidget *parent = 0);
	~ECVS();
	
protected:
	//虚函数

	void resizeEvent(QResizeEvent *); //窗口大小发生改变
private:
	Ui::ECVSClass ui;
	QListWidget *m_objList;  //流程工具列表
	QTreeWidget *m_objSet; //工具箱
	CShowImageWnd *m_pShowImgWnd;  //显示图像的窗口

	QTextEdit*		m_pDebugTest;
	
	//私有方法
private:
	void InitObjSet();
	void createDockWindows();
	void createMenu();
	void AddVisionTool(string strData);  //通过算法名字来添加流程处理工具
	void AddAlgrithm(CAlgrithmBase* pAlgrithm); //添加算法，需要记录步骤 用于Redo UnDo, 以及和流程里面的UI交互
	//信号和槽
public slots:
	void OpenImg();
	void OnAddTools(QTreeWidgetItem *item, int column);
private:

	//包括一个流程的集合 用于redo undo 操作 ，m_nCurIndex用来
	vector<CFlowProcess>  m_flowProcess;
	int m_nCurIndex;

	QAction* m_actOpenImg;
	QAction* m_actSaveImg;

};

#endif // ECVS_H
