
// CalculatorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "CtlEdit.h"


// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//用来处理回车

	//=====================================================
	//			成员变量
	//=====================================================
	// 这是输入账目的控件变量
	CEdit m_accounts;

	//以下是结果输出的8个变量，1~7分别对应周一~周日
	float m_result1;
	float m_result2;
	float m_result3;
	float m_result4;
	float m_result5;
	float m_result6;
	float m_result7;
	float m_result_total;

	// 输入方式单选按钮变量
	CButton m_inputway;

	// 这是设置开始时间的控件变量
	CDateTimeCtrl m_begindata;

	// 这是设置结束时间的控件变量
	CDateTimeCtrl m_enddata;

	// 自动捕获按钮控件变量
	CButton m_capture;

	// 这是开始计算按钮的控件变量
	CButton m_calculate;

	//用来存储账目信息，设置为全局变量，因为需要在不同成员函数中访问
	CString data[7];	

	//用来存储日期信息，设置为全局变量，因为需要在不同成员函数中访问
	CString date[7];	

	//用来存储当天的账目总和，设置为全局变量，因为需要在不同成员函数中访问
	float Day[7];

	//用来存储每天的总和 ..这里命名不好看，为了避免与字符串型重名，只好如此处理
	float Total = 0;						

	// 这是自动填写按钮的控件变量
	CButton m_fillin;

	// 这个是账目输入控件的值类型变量，就叫这个名字了
	CString m_bill;

	//以下是结果空间的控件控制变量，使用CCtlEdit类是因为增加了全选功能
	CCtlEdit m_ctlresult1;
	CCtlEdit m_ctlresult2;
	CCtlEdit m_ctlresult3;
	CCtlEdit m_ctlresult4;
	CCtlEdit m_ctlresult5;
	CCtlEdit m_ctlresult6;
	CCtlEdit m_ctlresult7;
	CCtlEdit m_ctlresult_total;
		
	//=====================================================
	//			成员函数
	//=====================================================

	// 这是手动输入单选框控件点击的响应函数
	afx_msg void OnBnClickedRadioManual();

	// 这是自动抓取单选框控件点击的响应函数
	afx_msg void OnBnClickedRadioAuto();

	// 这是设置开始时间控件变化的响应函数
	afx_msg void OnDtnDatetimechangeDatetimeBegin(NMHDR *pNMHDR, LRESULT *pResult);

	// 这是设置结束时间控件变化的响应函数
	afx_msg void OnDtnDatetimechangeDatetimeEnd(NMHDR *pNMHDR, LRESULT *pResult);

	// 这是开始计算按钮的点击响应
	afx_msg void OnBnClickedBtnCalculate();
			
	//编辑框内容变化响应函数
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedBtnFillin();
};
