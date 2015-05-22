#pragma once

class ECVS_EXPORT CBilateralFilter :
	public CAlgrithmBase
{
public:
	CBilateralFilter();
	~CBilateralFilter();

	virtual void Run();		//执行算法
	virtual void Set(){};  //设置算法
	virtual string GetErrorMsg();
	//读写函数，参数暂时未实现，等第一个算法成功实现及流程测试成功后再实现
	virtual void Read(){};
	virtual void Save() {};

//	virtual string GetErrorMsg(); // 获取算法执行错误字符串

private:
	//算法运行时私有参数

// 
// 		m_nDiameter – Diameter of each pixel neighborhood that is used during filtering.If it is non - positive, it
// 		is computed from sigmaSpace .
// 		m_dbSigmaColor – Filter sigma in the color space.A larger value of the parameter means that
// 		farther colors within the pixel neighborhood(see sigmaSpace) will be mixed together,
// 		resulting in larger areas of semi - equal color.
// 		m_dbSigmaSpace – Filter sigma in the coordinate space.A larger value of the parameter means
// 		that farther pixels will influence each other as long as their colors are close enough(see
// 		sigmaColor).When d > 0, it specifies the neighborhood size regardless of sigmaSpace .
// 		Otherwise, d is proportional to sigmaSpace .
	int		m_nDiameter;
	double	m_dbSigmaColor;
	double	m_dbSigmaSpace;


};

