#ifndef SHOWIMAGEWND_H
#define SHOWIMAGEWND_H
#include "ECVSBase.h"
#include <QGraphicsView>

#define  WM_SHOWIMGFIXWINDOW WM_USER + 5017  //自定义消息，用于适应窗口显示图片
#define NUMOFCANNEL 1
#define	MAXRATE	 80
#define	MINRATE	 -80
#define	ONEPERCENT  10
class ECVS_EXPORT CShowImageWnd : public QFrame
{
	Q_OBJECT
public:
	CShowImageWnd(QWidget *parent);
	~CShowImageWnd();
	
	void SetImage(Mat img); //设置显示图像

private:
	Mat m_matShowImg;
	Mat m_matShowImgClone;
	QImage	m_imgShow;
	QRect	m_rectShowImgRect;  //显示图像的矩形框
	int m_nCols, m_nRows;
	//用于图像缩放操作的变量
	int m_nCurRate;      //当前倍率，放大 缩小次数
	double	m_dbShowPersent;  //当前显示图像的百分比
	QPoint		m_ptCoordinateOffset; //图像显示矩形相对于左上角的偏移量


public slots:
	
protected:
	void wheelEvent(QWheelEvent* event);
	void paintEvent(QPaintEvent* event);
	void OnShowImgFixWindow(/*int nRows, int nCols*/);
	void Enlarge(bool bEnlarge, QPoint ptCenter);
	void EnlargeCenter(bool bEnlarge);  //以图像中心点为基准缩放
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:

	//分配资源和删除资源函数
	bool Init();
	bool Init(int nRows, int nClos, int nChannels);
	bool Delete();
	//将Mat转换为QImage
	
};

#endif // SHOWIMAGEWND_H
