// TestLog4Cpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/SimpleLayout.hh>
#define LOGFILE "./test.log"
#pragma  comment(lib, "../../log4Cpp/msvc10/log4cpp/Debug/log4cpp.lib")
int _tmain(int argc, _TCHAR* argv[])
{

	log4cpp::Appender *appender = new log4cpp::FileAppender("FileAppender", LOGFILE);
	log4cpp::Layout *layout = new log4cpp::SimpleLayout();
	log4cpp::Category& category = log4cpp::Category::getInstance("abc");
	appender->setLayout(layout);
	category.setAppender(appender);
	category.setPriority(log4cpp::Priority::INFO);

	category.info("测试");
	category.notice("测试1");
	category.warn("sdfsd");
	category.debug("debug");
	
	log4cpp::Category::shutdown();
	return 0;
}

