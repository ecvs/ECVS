
#include <QtWidgets/QApplication>
#include "ECVSBase.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include "AlgrithmBase.h"
#include "BilateralFilter.h"
#include "test1.h"
#include <QTextCodec>
#pragma  comment(lib, "ECVSFilter.lib")
#pragma  comment(lib, "ECVSBase.lib")
#define  Test(class_name) asd##class_name
int main(int argc, char *argv[])
{
	
	QApplication app(argc, argv);
	QString str = QStringLiteral("Œ“");
	char str1[2];
	
	QByteArray byteArray = str.toLocal8Bit();
 	str1[0] = byteArray.at(0);
 	str1[1] = byteArray.at(1);
	Test1 t;
	Qt::WindowFlags flgs = t.windowFlags();
	/*t.setWindowModality(Qt::WindowStaysOnTopHint);*/
	t.show();
	return app.exec();
}
