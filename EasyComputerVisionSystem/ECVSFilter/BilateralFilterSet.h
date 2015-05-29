#ifndef BILATERALFILTERSET_H
#define BILATERALFILTERSET_H
#include "ecvsfilter_global.h"
#include "ECVSBase.h"
#include <QWidget>
#include <QDialog>
#include "ui_BilateralFilterSet.h"
#include "ShowImageWnd.h"
#include <QMainWindow>
class  CBilateralFilterSet : public QDialog
{
	Q_OBJECT

public:
	CBilateralFilterSet(QWidget *parent = 0);
	~CBilateralFilterSet();

private:
	Ui::CBilateralFilterSet ui;
	CShowImageWnd *m_pShowImgWnd;
	QMenu *m_pMenu;

protected:
	void resizeEvent(QResizeEvent *);
};

#endif // BILATERALFILTERSET_H
