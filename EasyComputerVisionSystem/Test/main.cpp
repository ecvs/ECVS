
#include <QtWidgets/QApplication>
//#include "ECVSBase.h"
// #include "ToolInput.h"
// #include "ToolOutput.h"
// #include "AlgrithmBase.h"
// #include "BilateralFilter.h"
#include "test1.h"
#include <QTextCodec>
// #pragma  comment(lib, "ECVSFilter.lib")
// #pragma  comment(lib, "ECVSBase.lib")
#define  Test(class_name) asd##class_name
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>  

#pragma  comment(lib, "qscintilla2.lib")
#include <vector>
#include <QmessageBox>
using std::vector;
class TestVector
{

public:
	vector<int> m_vecInt;
};

class TestClear
{
public:
	int *pInt;
	TestClear()
	{
		pInt = new int;
		*pInt = 5;

	}

	void ClearMemry()
	{
		delete this;
		
	}

	~TestClear()
	{
		delete pInt;
	}
};
#include <string>
using std::string;
int main(int argc, char *argv[])
{
	string str11 = "asd";
	str11 += 1;
	TestClear *p = new TestClear();
	p->ClearMemry();
	TestVector a;
	a.m_vecInt.push_back(11);
	TestVector b = a;
	
	QApplication app(argc, argv);
	
	QString str = QStringLiteral("Œ“");
	char str1[2];
	QMessageBox::aboutQt(NULL);
	QByteArray byteArray = str.toLocal8Bit();
 	str1[0] = byteArray.at(0);
 	str1[1] = byteArray.at(1);
	Test1 t;
	Qt::WindowFlags flgs = t.windowFlags();
	/*t.setWindowModality(Qt::WindowStaysOnTopHint);*/
	t.show();

	return app.exec();
}
