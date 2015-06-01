#include "test1.h"
#include <windows.h>
#include "ECVSBase.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include "AlgrithmBase.h"
#include "BilateralFilter.h"
Test1::Test1(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	 pSet = new CBilateralFilter();
}

Test1::~Test1()
{

}

void Test1::OnBtnClicked()
{
	
	pSet->Set();
}
