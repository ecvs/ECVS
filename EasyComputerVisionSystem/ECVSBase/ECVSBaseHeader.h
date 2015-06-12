#pragma  once
#include "ECVSBase.h"
#include "ToolInput.h"
#include "ToolOutput.h"
#include "AlgrithmBase.h"
#include "FlowProcess.h"
#include "InputOutputInfo.h"
#include "ShowImageWnd.h"
#ifdef _DEBUG
#pragma  comment(lib,"opencv_world300d.lib" )
#pragma  comment(lib, "opencv_ts300d.lib")
#else
#pragma  comment(lib, "opencv_ts300.lib")
#pragma  comment(lib,"opencv_world300.lib" )
#endif