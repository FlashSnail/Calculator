
// CalculatorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "CtlEdit.h"


// CCalculatorDlg �Ի���
class CCalculatorDlg : public CDialogEx
{
// ����
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);	//��������س�

	//=====================================================
	//			��Ա����
	//=====================================================
	// ����������Ŀ�Ŀؼ�����
	CEdit m_accounts;

	//�����ǽ�������8��������1~7�ֱ��Ӧ��һ~����
	float m_result1;
	float m_result2;
	float m_result3;
	float m_result4;
	float m_result5;
	float m_result6;
	float m_result7;
	float m_result_total;

	// ���뷽ʽ��ѡ��ť����
	CButton m_inputway;

	// �������ÿ�ʼʱ��Ŀؼ�����
	CDateTimeCtrl m_begindata;

	// �������ý���ʱ��Ŀؼ�����
	CDateTimeCtrl m_enddata;

	// �Զ�����ť�ؼ�����
	CButton m_capture;

	// ���ǿ�ʼ���㰴ť�Ŀؼ�����
	CButton m_calculate;

	//�����洢��Ŀ��Ϣ������Ϊȫ�ֱ�������Ϊ��Ҫ�ڲ�ͬ��Ա�����з���
	CString data[7];	

	//�����洢������Ϣ������Ϊȫ�ֱ�������Ϊ��Ҫ�ڲ�ͬ��Ա�����з���
	CString date[7];	

	//�����洢�������Ŀ�ܺͣ�����Ϊȫ�ֱ�������Ϊ��Ҫ�ڲ�ͬ��Ա�����з���
	float Day[7];

	//�����洢ÿ����ܺ� ..�����������ÿ���Ϊ�˱������ַ�����������ֻ����˴���
	float Total = 0;						

	// �����Զ���д��ť�Ŀؼ�����
	CButton m_fillin;

	// �������Ŀ����ؼ���ֵ���ͱ������ͽ����������
	CString m_bill;

	//�����ǽ���ռ�Ŀؼ����Ʊ�����ʹ��CCtlEdit������Ϊ������ȫѡ����
	CCtlEdit m_ctlresult1;
	CCtlEdit m_ctlresult2;
	CCtlEdit m_ctlresult3;
	CCtlEdit m_ctlresult4;
	CCtlEdit m_ctlresult5;
	CCtlEdit m_ctlresult6;
	CCtlEdit m_ctlresult7;
	CCtlEdit m_ctlresult_total;
		
	//=====================================================
	//			��Ա����
	//=====================================================

	// �����ֶ����뵥ѡ��ؼ��������Ӧ����
	afx_msg void OnBnClickedRadioManual();

	// �����Զ�ץȡ��ѡ��ؼ��������Ӧ����
	afx_msg void OnBnClickedRadioAuto();

	// �������ÿ�ʼʱ��ؼ��仯����Ӧ����
	afx_msg void OnDtnDatetimechangeDatetimeBegin(NMHDR *pNMHDR, LRESULT *pResult);

	// �������ý���ʱ��ؼ��仯����Ӧ����
	afx_msg void OnDtnDatetimechangeDatetimeEnd(NMHDR *pNMHDR, LRESULT *pResult);

	// ���ǿ�ʼ���㰴ť�ĵ����Ӧ
	afx_msg void OnBnClickedBtnCalculate();
			
	//�༭�����ݱ仯��Ӧ����
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedBtnFillin();
};
