#pragma  once
/*
* ECVSBase.h
*
* 创建于 2015-5-12  李春峰
* 
* ECVSBase所有的公用定义常量都在该文件定义
* 导出的全局函数也在该文件定义 
*/
#ifdef ECVS_BUILD_DLL
#define ECVS_EXPORT __declspec(dllexport)
#else
#define  ECVS_EXPORT
#endif

#include <string>
#include <vector>
using std::vector;
using std::string;
#define  ECVSString string;

//类型的定义

//普通数据的起始定义
#define DATA_TYPE_BASE		0x0F00
//数据类型是vector的起始定义
#define DATA_TYPE_VEC_BASE	0xFF00

#define DATA_TYPE_INT		0x01
#define  DATA_TYPE_DOUBLE	0x02
#define DATA_TYPE_STRING	0x03
#define  DATA_TYPE_POINT	0x04
#define  DATA_TYPE_POINT2F  0x05
#define  DATA_TYPE_IMAGE	0x06
enum DataType
{
	TYPE_INT = DATA_TYPE_BASE + DATA_TYPE_INT,				//整型
	TYPE_DOUBLE = DATA_TYPE_BASE + DATA_TYPE_DOUBLE,			//浮点型
	TYPE_STRING = DATA_TYPE_BASE + DATA_TYPE_STRING,			//字符串类型
	TYPE_POINT = DATA_TYPE_BASE + DATA_TYPE_POINT,				//CV::Point类型
	TYPE_POINT2F = DATA_TYPE_BASE + DATA_TYPE_POINT2F,			//CV::Point2F类型
	TYPE_IMAGE = DATA_TYPE_BASE + DATA_TYPE_IMAGE,				//CV::Mat 类型
	//下面的字段都是上面的Vector类型
	TYPE_INT_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_INT,
	TYPE_DOUBLE_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_DOUBLE,
	TYPE_STRING_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_STRING,
	TYPE_POINT_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_POINT,
	TYPE_POINT2F_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_POINT2F,
	TYPE_IMAGE_VECTOR = DATA_TYPE_VEC_BASE + DATA_TYPE_IMAGE,




};




//错误定义
#define  ECVS_ERROR_NO_ERROR 0

//系统设计时的所有错误


//算法还未执行
#define ECVS_ERR_HAS_NO_EXECUTE 1
//需要图像输入的算法，没有设置输入图像
#define  ECVS_ERROR_HAS_NO_IMG_INPUT 2


//自定义错误的起始位 所有插件返回错误 能改变的只有后16位
#define  ECVS_ERROR_USER_MASK 0x00FF0000





bool IsVector(DataType dt); //判断dt是否是vector类型
bool IsSameType(DataType dt1, DataType dt2);// 判断dt1和 dt2是否为同一种类型 比如vector<int> 和int是同一种类型
string GetErrorMsg(int nCode);