#ifndef DDD_H
#define DDD_H

#include <QWidget>
#include "ui_ddd.h"

class ddd : public QWidget
{
	Q_OBJECT

public:
	ddd(QWidget *parent = 0);
	~ddd();

private:
	Ui::ddd ui;
};

#endif // DDD_H
