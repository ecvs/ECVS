#pragma once
class CShowImageWnd;
#include "resource.h"

// BilateralFilterSet 对话框

class CBilateralFilterSet : public CDialogEx
{
	DECLARE_DYNAMIC(CBilateralFilterSet)

public:
	CBilateralFilterSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBilateralFilterSet();

// 对话框数据
	enum { IDD = IDD_BILATERALFILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CShowImageWnd * m_pShowImgWnd;
	Mat m_imagSrc;
	Mat m_imgDst;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOpenimg();
};
