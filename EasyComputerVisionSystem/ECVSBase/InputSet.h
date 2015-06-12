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
	CInputSet(QWidget *parent = 0);
	~CInputSet();
	
	void AddSrcInput(QString strInputName, QString strInputType);
	void AddPreAlgrithms(QString strPreAlgrithm);

private:
	Ui::CInputSet ui;
	QStandardItemModel *m_pModelInputParam;
	QStandardItemModel *m_pPreAlgrithm;
};

#endif // FLOWSET_H
