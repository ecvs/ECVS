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
#include <QStandardItemModel>
#include "ui_ecvs.h"
class QTextEdit;
class QTreeWidget;
class QsciScintilla;
using std::vector;
class ECVS : public QMainWindow
{
	Q_OBJECT


	friend class CFlowSet;
public:
	ECVS(QWidget *parent = 0);
	~ECVS();
	void contextMenuEvent(QContextMenuEvent *);
protected:
	//虚函数

	void resizeEvent(QResizeEvent *); //窗口大小发生改变
private:
	Ui::ECVSClass ui;
	QTableView *m_objList;  //流程工具列表
	QStandardItemModel *m_modelFlow;
	bool		m_bChangeToolText; //是否为设置算法的显示字符
	QTreeWidget *m_objSet; //工具箱
	CShowImageWnd *m_pShowImgWnd;  //显示图像的窗口

	QMenu *m_pMenuSetFlowMenu;
	QAction* m_pActSetTool; 
	QAction* m_pActSetFlows; 
	QAction* m_pActChangeToolName; 

	QTextEdit*		m_pDebugTest;
	QsciScintilla*  m_pCodeEdit;

	
	//私有方法
private:
	void InitObjSet();
	void createDockWindows();
	void createMenu();
	void AddVisionTool(string strData);  //通过算法名字来添加流程处理工具
	void AddAlgrithm(CAlgrithmBase* pAlgrithm); //添加算法，需要记录步骤 用于Redo UnDo, 以及和流程里面的UI交互
	void SetAlgrithm(int nIndex); //对某一个算法进行设置，需要记录步骤 用于Redo UnDo, 以及和流程里面的UI交互

	//信号和槽
public slots:
	void OpenImg();
	void OnAddTools(QTreeWidgetItem *item, int column);
	void SetFlow(const QPoint&);
	void SetTools();
	void SetToolsFlow();
	void ChangeToolName();
	void OnDoubleClicked(const QModelIndex &);
	void ToolTextChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &);
	void MoveObjIndex(int nWitch, int nAfter);
	void OnRun();
	void OnSetCamera(QAction *);  //设置相机
private:

	//包括一个流程的集合 用于redo undo 操作 ，m_nCurIndex用来
	vector<CFlowProcess>  m_flowProcess;
	int m_nCurIndex;

	QAction* m_actOpenImg;
	QAction* m_actSaveImg;
	QAction* m_pRunProcess;
	//工具栏的获取图像跟
	QTreeWidgetItem* m_pGetImg;
	//私有方法
private:
	void InitCamera();  //初始化所有相机
	void ExitCamera();  //退出相机
};

#endif // ECVS_H
