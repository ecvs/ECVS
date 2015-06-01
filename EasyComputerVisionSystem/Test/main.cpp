
#include <QtWidgets/QApplication>
#include "ECVSBase.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include "AlgrithmBase.h"
#include "BilateralFilter.h"
#include "test1.h"
#pragma  comment(lib, "ECVSFilter.lib")
#pragma  comment(lib, "ECVSBase.lib")
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Test1 t;
	Qt::WindowFlags flgs = t.windowFlags();
//	t.setWindowModality(Qt::WindowStaysOnTopHint);
	t.show();
	return app.exec();
}
