#ifndef TEST1_H
#define TEST1_H

#include <QWidget>
#include "ui_test1.h"
class CBilateralFilter;
class Test1 : public QWidget
{
	Q_OBJECT

public:
	Test1(QWidget *parent = 0);
	~Test1();

public slots:
void OnBtnClicked();
private:
	Ui::Test1 ui;
	//CBilateralFilter *pSet;
};

#endif // TEST1_H
