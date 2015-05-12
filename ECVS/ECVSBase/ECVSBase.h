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
