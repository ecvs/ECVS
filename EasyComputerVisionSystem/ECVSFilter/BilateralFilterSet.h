#pragma once


// CBilateralFilterSet 对话框

class CBilateralFilterSet : public CDialogEx
{
	DECLARE_DYNAMIC(CBilateralFilterSet)

public:
	CBilateralFilterSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBilateralFilterSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_BILATERALFILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
