#ifndef BILATERALFILTERSET_H
#define BILATERALFILTERSET_H
#include "ecvsfilter_global.h"
#include "ECVSBase.h"
#include <QWidget>
#include <QDialog>
#include "ui_BilateralFilterSet.h"
#include "ShowImageWnd.h"
#include <QMainWindow>
#include <QGraphicsWidget>
class CBilateralFilter;
class  CBilateralFilterSet : public QDialog
{
	Q_OBJECT

public:
	CBilateralFilterSet(CBilateralFilter* pOwer,QWidget *parent = 0);
	~CBilateralFilterSet();

private:
	Ui::CBilateralFilterSet ui;
	CShowImageWnd *m_pShowImgWnd;

 	QPushButton* m_pButtonTest;
	CBilateralFilter*	m_pOwerFilter;  //被哪个Filter调用的
	Mat m_imgProcessed;			//待处理的图像，从文件读取，或从相机获取到的
protected:
	void resizeEvent(QResizeEvent *);
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);  //处理Windows消息

private slots:
	void OnOpenImg();
	void OnShowFixSize();
	void OnShowOrgImg();
	void OnShowFilterImg();
	void OnSliderDChanged(int nValue);
	void OnSliderSigmaColorChanged(int nValue);
	void OnSliderSigmaSpaceChanged(int nValue);

	void OnSpinDChanged(int nValue);
	void OnSpinSigmaColorChanged(int nValue);
	void OnSpinSigmaSpaceChanged(int nValue);
	void OnOkClicked();
	void OnCancelClicled();
private:
	void BilateralFilterParamChanged();  //当3个参数任何一个改变时，调用该函数
	void OnBilateralFilter();  //实际执行BilateralFilter的函数


	
};

#endif // BILATERALFILTERSET_H
