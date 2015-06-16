#ifndef FLOWSET_H
#define FLOWSET_H

#include <QDialog>
#include "ui_InputSet.h"
#include <QStandardItemModel>

class CInputSet : public QDialog
{
	Q_OBJECT
	friend class CFlowProcess;
public:
	CInputSet(int nIndex, QWidget *parent = 0);
	~CInputSet();
	
	void AddSrcInput(QString strInputName, QString strInputType);
	void AddSelectedParam(QString strName, QString str);
	void ClearSelectedParam();
	void AddPreAlgrithms(QString strPreAlgrithm);
public slots:
	void SelectedAlgrithmChanged( QModelIndex );

Q_SIGNALS:
	//输入算法改变了,nIndexCurParam是哪一个输入参数，nCurInput是选择哪一个输出作为输入参数
	void InputIndexChange(int nIndexCurParam,int nCurInput);

private:
	Ui::CInputSet ui;
	QStandardItemModel *m_pModelInputParam;  //需要有输入的参数
	QStandardItemModel *m_pPreAlgrithm;  // 前驱工具，
	QStandardItemModel *m_pCandidateParam;  //候 选的输入参数
	CFlowProcess*		m_pOwerProcess ;  //属于哪一个Process
	const int			m_nAlgrithmIndex;
	
};

#endif // FLOWSET_H
