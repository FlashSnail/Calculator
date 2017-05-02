
// CalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#include "CtlEdit.h"
#include "afxtempl.h"	//Ϊ��ʹ��CArray������

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg �Ի���



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculatorDlg::IDD, pParent)
	, m_result1(0)
	, m_result2(0)
	, m_result3(0)
	, m_result4(0)
	, m_result5(0)
	, m_result6(0)
	, m_result7(0)
	, m_result_total(0)
	, m_bill(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_accounts);
	DDX_Control(pDX, IDC_RADIO_MANUAL, m_inputway);
	DDX_Control(pDX, IDC_DATETIME_BEGIN, m_begindata);
	DDX_Control(pDX, IDC_DATETIME_END, m_enddata);
	DDX_Control(pDX, IDC_BTN_CAPTURE, m_capture);
	DDX_Control(pDX, IDC_BTN_CALCULATE, m_calculate);
	DDX_Text(pDX, IDC_RESULT1, m_result1);
	DDX_Text(pDX, IDC_RESULT2, m_result2);
	DDX_Text(pDX, IDC_RESULT3, m_result3);
	DDX_Text(pDX, IDC_RESULT4, m_result4);
	DDX_Text(pDX, IDC_RESULT5, m_result5);
	DDX_Text(pDX, IDC_RESULT6, m_result6);
	DDX_Text(pDX, IDC_RESULT7, m_result7);
	DDX_Text(pDX, IDC_RESULT_TOTAL, m_result_total);
	DDX_Control(pDX, IDC_BTN_FILLIN, m_fillin);
	DDX_Text(pDX, IDC_EDIT, m_bill);
	DDX_Control(pDX, IDC_RESULT1, m_ctlresult1);
	DDX_Control(pDX, IDC_RESULT2, m_ctlresult2);
	DDX_Control(pDX, IDC_RESULT3, m_ctlresult3);
	DDX_Control(pDX, IDC_RESULT4, m_ctlresult4);
	DDX_Control(pDX, IDC_RESULT5, m_ctlresult5);
	DDX_Control(pDX, IDC_RESULT6, m_ctlresult6);
	DDX_Control(pDX, IDC_RESULT7, m_ctlresult7);
	DDX_Control(pDX, IDC_RESULT_TOTAL, m_ctlresult_total);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CCalculatorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCalculatorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_MANUAL, &CCalculatorDlg::OnBnClickedRadioManual)
	ON_BN_CLICKED(IDC_RADIO_AUTO, &CCalculatorDlg::OnBnClickedRadioAuto)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME_BEGIN, &CCalculatorDlg::OnDtnDatetimechangeDatetimeBegin)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME_END, &CCalculatorDlg::OnDtnDatetimechangeDatetimeEnd)
	ON_BN_CLICKED(IDC_BTN_CALCULATE, &CCalculatorDlg::OnBnClickedBtnCalculate)
	ON_EN_CHANGE(IDC_EDIT, &CCalculatorDlg::OnEnChangeEdit)
	ON_BN_CLICKED(IDC_BTN_FILLIN, &CCalculatorDlg::OnBnClickedBtnFillin)
END_MESSAGE_MAP()


// CCalculatorDlg ��Ϣ�������

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//===========================================================
	//���õ�ѡ��ť��ʼѡ���ֶ�����
	m_inputway.SetCheck(TRUE);

	//===========================================================
	//��δ��������ý��������Զ�����Ϊһ�ܺ�Ȼ��δ������Ľ�����Ϊ�������ڣ��˶δ�����Ҫ�޸�
	COleDateTime CurrentTime(COleDateTime::GetCurrentTime());
	m_enddata.SetTime(CurrentTime + COleDateTimeSpan(6, 0, 0, 0));
	
	//���ó�ʼ�����ڱ༭���ϣ��������˻س��˳����������
	GetDlgItem(IDC_EDIT)->SetFocus();

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCalculatorDlg::OnPaint()
{
	//��һ�δ�����VS2013��bug������ͼƬ�ؼ�����λͼ�ǳ��ֵ�
	//CStatic* pWnd = (CStatic*)GetDlgItem(IDC_CalOK); // �õ� Picture Control ���  
	//pWnd->ModifyStyle(0, SS_BITMAP); // �޸���������Ϊλͼ 

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CCalculatorDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}



BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//=======================================================================
	//��δ������޸Ļس�������Ӧ�����ǲ��밴�»س������˳������ˣ���˽��س��Ĺ����޸�ΪTab
	/*if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		pMsg->wParam = VK_TAB;
	}*/				//Ϊ�˱༭����Ի��У�����ȡ���������
	//=======================================================================
	//���δ�����ʹ�༭�����ȫѡ����
	if (pMsg->message == WM_KEYDOWN)
	{
		BOOL b = GetKeyState(VK_CONTROL) & 0x80;
		if (b && (pMsg->wParam == 'a'||pMsg->wParam=='A'))
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETSEL, 0, -1);    //�� SendDlgItemMessage(IDC_Log, EM_SETSEL, 0, -1);</span>  
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCalculatorDlg::OnBnClickedRadioManual()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��˵����:���UpdateData(TRUE) == ���ؼ���ֵ��ֵ����Ա����; UpdateData(FALSE) == ����Ա������ֵ��ֵ���ؼ���
	UpdateData(TRUE);
	if (!m_bill.IsEmpty())	//����ؼ������ݣ���д��ʽ�ı����տؼ�
	{
		m_bill = ("");
	}
	//���δ�����ʹ����д��ʽ��ؿؼ���
	m_accounts.SetReadOnly(FALSE);	
	m_capture.EnableWindow(FALSE);
	m_begindata.EnableWindow(FALSE);
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedRadioAuto()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (!m_bill.IsEmpty())	//����ؼ������ݣ���д��ʽ�ı����տؼ�
	{
		m_bill = ("");
	}
	//���δ�����ʹ����д��ʽ��ؿؼ���
	m_accounts.SetReadOnly(TRUE);
	m_capture.EnableWindow(TRUE);
	m_begindata.EnableWindow(TRUE);	
	UpdateData(FALSE);
}



void CCalculatorDlg::OnDtnDatetimechangeDatetimeBegin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���γ����ǻ�ȡ��ǰѡ��ʱ�䣬�����Զ�����END TIME
	COleDateTime SelectTime;
	m_begindata.GetTime(SelectTime);
	m_enddata.SetTime(SelectTime + COleDateTimeSpan(6, 0, 0, 0));

	*pResult = 0;
}


void CCalculatorDlg::OnDtnDatetimechangeDatetimeEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CCalculatorDlg::OnBnClickedBtnCalculate()	//���㰴ť����Ӧ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_fillin.EnableWindow(TRUE);	//ʹ���Զ���д��ť

	for (int i = 0; i < 7; i++)		//��ʼ����Ŀ��Ϣ
	{
		data[i] = "";
	}

	for (int i = 0; i < 7; i++)		//��ʼ��������Ϣ
	{
		date[i] = "";
	}

	int StartPos = 0;	//������ʼλ��
	int EndPos = 0;		//������ֹλ��

	StartPos = m_bill.Find(_T("\r\n"));				//�����ս������⴦����Ϊ����һ����������������ͬ
	EndPos = m_bill.Find(_T("\r\n"), StartPos+1);	//��ȡ��һ�����з�������

	data[6] = m_bill.Mid(StartPos + 2, EndPos - StartPos -2);	//Mid���������Ǻ�ֵ��ǰֵ�ó��ȡ� +2��Ϊ�˹�������\r\n��-2��Ϊ�˹����ص��\r\n
	date[6] = m_bill.Left(StartPos);							//��ȡ���յ�������Ϣ

	for (int i = 5; i >= 0; i--)								//���λ�ø������Ŀ��������Ϣ
	{
		StartPos = m_bill.Find(_T("\r\n"), EndPos+1);
		date[i] = m_bill.Mid(EndPos + 2, StartPos - EndPos - 2);	//������Ϣ��ע���������λ�úͼ����������Ĺ�ϵ��
		EndPos = m_bill.Find(_T("\r\n"), StartPos+1);				//�������������������������ֵ�м�
		data[i] = m_bill.Mid(StartPos + 2, EndPos - StartPos - 2);	//��Ŀ��Ϣ				
	}

	//===================================================================
	//	��������ȡ֧�����ֵĺ����㷨��������Ŀ��Ϣ�п��ܺ������ֵĸ��� �����������и�BUG��������Ȼ�ų������ֵĸ��ţ��������Ŀ�д��ڡ�Ԫ���ͻ����BUG

//	CString DataDetail_n;

	TCHAR DataTemp;							//�洢��������
//	CArray <CString, CString&> DataDetail_n;	//�����洢�������Ŀ��ֵ��������洢���ַ���
//	CString DataDetai[100];
	CString DataDetail_n[50];				//�����洢������Ŀ��ֵ��������洢�����ֵĵ���
//	CString DataDetail_p[50];				//�����洢������Ŀ��ֵ��������洢�����ֵ�����  //����Ͳ����ˣ�ֱ�Ӹ�������
	CString Temp;							//������������˳��Ļ���
//	DataDetail_n.SetSize(0);					//Ϊ�˱����ڴ���Ƭ�����Ч�ʣ�MSDN������ô��
	int m;								//������Ŀ��ֵ����
	int EndPos_Day[50];				//�洢ÿ��ġ�Ԫ��λ�ã��˴���50��Ԥ��ֵ������һ��Ҳû��100����Ŀ���������˴���һ��BUG����
	int End;							//��Ԫ����������
//	EndPos_Day.SetSize(1);
	
	//Ϊ�˱����ε�����㰴ť����double���������ʼ����
	//����һ�ֱ������ƣ��������뵽������һ�������ķ������ڼ����������һ��������ϵİ�ť���滻���㰴ť������Ҳ������
	//��⵽�༭���仯���ٸ��֣�������UIҲ���Ѻã���������������Ҳ����������
	Total = 0;
	for (int i = 0; i < 7; i++)
	{
		Day[i] = 0;
	}

	for (int i = 0; i < 7; i++)
	{
//		DataDetail_n.RemoveAll();
		//==========================================================
		//�ⲿ���Ǹ��ֲ����ĳ�ʼ��
		for (int i = 0; i < 50; i++)
		{
			DataDetail_n[i] = { "" };	
	//		DataDetail_p[i] = { "" };
			EndPos_Day[i] = { 0 };
		}		
		EndPos = 0;
		End = 0;
		m = 0;
		//==========================================================

		EndPos = data[i].Find(_T("Ԫ"));	//���ڵĹ�����Ҫ��ȡһ�����еġ�Ԫ�������洢�������������ѭ���б���
		EndPos_Day[End] = EndPos;				//��һ����Ԫ��
		//===============================================================
		//���ǶԵ�һ����Ԫ��֮ǰ���ݵĴ�����Ϊ����û����������Ԫ��֮��
		for (int q = EndPos - 1 ; q > 0; q--)
		{
			DataTemp = data[i].GetAt(q);
			if (DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.'))	//��������ֻ���С����Ļ��ʹ洢
			{
				DataDetail_n[m] += DataTemp;			//�ȴ洢���ַ��ͣ���Ϊ��С����Ĵ��ڣ�ֻ����������
			}
			if (!(DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.')))	//����ӡ�Ԫ����ǰ��������һ���������ַ���������ѭ��
			{
				for (int i = DataDetail_n[m].GetLength() - 1; i > -1; i--)	//���÷������������Ŀ��������ʱ�洢���ַ��ͱ���Temp��
				{
					Temp += DataDetail_n[m].GetAt(i);
				}
				Day[i] += _wtof(Temp);	//����_wtof()���ַ��ͱ���תΪ���ͣ����ͱ�����Ŀ�ͽ��мӺ�
				//�����߳�ʼ�����˳�������Ŀ��ѭ��
				Temp = "";				
				m++;
				break;
			}
		}
		//================================================================
		for (int n = 0; n < data[i].GetLength(); n++)	//ͨ�����ѭ����������һ������С�Ԫ��
		{
			EndPos = data[i].Find(_T("Ԫ"), EndPos + 1);	//��ʼλ������Ϊ��ǰԪ����һ��λ����Ѱ����һ��Ԫ
			if (EndPos != -1)								//����ҵ���Ԫ
			{
				End++;										//��������ֵ+1
				EndPos_Day[End] = EndPos;					//���洢λ������
			}
			else                                            //���û���ҵ����ߵ������һ��Ԫ�����˳�
			{
				break;
			}
//			EndPos_Day.Add(EndPos);
		}		
		//================================================================
		//�����ǡ�Ԫ��֮��ı�������
		for (int p = 0; p < End; p++)	//Ȼ��ÿ����Ԫ��֮���������
		{
			for (int j = EndPos_Day[p+1] - 1; j > EndPos_Day[p]; j--)		//j��ÿ����Ԫ��������λ��
			{
				DataTemp = data[i].GetAt(j);			//��ʼ��һ�����Ϣ����
				if (DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.'))	//��������ֻ���С����Ļ��ʹ洢
				{
					DataDetail_n[m] += DataTemp;			//�ȴ洢���ַ��ͣ���Ϊ��С����Ĵ��ڣ�ֻ����������
				}
				if (!(DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.')))	//����ӡ�Ԫ����ǰ��������һ���������ַ���������ѭ��
				{
					for (int i = DataDetail_n[m].GetLength() - 1; i > -1; i--)		//���÷������������Ŀ��������ʱ�洢���ַ��ͱ���Temp��
					{
						Temp += DataDetail_n[m].GetAt(i);
					}
					Day[i] += _wtof(Temp);		//����_wtof()���ַ��ͱ���תΪ���ͣ����ͱ�����Ŀ�ͽ��мӺ�
					//�����߳�ʼ�����˳�������Ŀ��ѭ��
					Temp = "";
					m++;
					break;
				}
			}
		}
		//==================================================================
		//�ص��˲�ѭ��������һ��ļ���
	}
	for (int i = 0; i < 7; i++)		//��һ�ܵ��ܺ�
	{
		Total += Day[i];
	}
	//=======================================================================
	//������ֵ������ϣ���������ʾ�Ĺ���

	//==========����������ֵ�ͱ���====================
	CString Monday;
	CString Thursday;
	CString Wednesday;
	CString Tuesday;
	CString Friday;
	CString Saturday;
	CString Sunday;
	CString WeekTotal;		
	//====================================================

	//===========�淶����ʽ����ֵ=========================
	Monday.Format(_T("%.2f"), Day[0]);
	Thursday.Format(_T("%.2f"), Day[1]);
	Wednesday.Format(_T("%.2f"), Day[2]);
	Tuesday.Format(_T("%.2f"), Day[3]);
	Friday.Format(_T("%.2f"), Day[4]);				//������������ÿ������Ʋ����ں�����̣�����Ϊ�˳���Ŀɶ��ԣ��ͱ��������ַ���
	Saturday.Format(_T("%.2f"), Day[5]);
	Sunday.Format(_T("%.2f"), Day[6]);
	WeekTotal.Format(_T("%.2f"), Total);
	//====================================================

	//================������ʾ��==========================
	m_ctlresult1.SetWindowTextW(Monday);
	m_ctlresult2.SetWindowTextW(Thursday);
	m_ctlresult3.SetWindowTextW(Wednesday);
	m_ctlresult4.SetWindowTextW(Tuesday);
	m_ctlresult5.SetWindowTextW(Friday);
	m_ctlresult6.SetWindowTextW(Saturday);
	m_ctlresult7.SetWindowTextW(Sunday);
	m_ctlresult_total.SetWindowTextW(WeekTotal);
	//====================================================

	m_calculate.EnableWindow(FALSE);		//���ü��㰴ť
//	GetDlgItem(IDC_CalOK)->ShowWindow(SW_SHOW);

}


void CCalculatorDlg::OnEnChangeEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	//���δ����ǽ���ӡ��ʼ��и��Ƴ�����Ŀ��Ϣ�ڱ༭��ʱ�ı���ʾ��ʽ
	//ԭ������windows�к�ӡ��ʼ��л��д��벻ͬ

	m_calculate.EnableWindow(TRUE);			//һ���༭�������仯��ʹ�ܼ��㰴ť
	UpdateData(TRUE);						//���UpdateData(TRUE) == ���ؼ���ֵ��ֵ����Ա����; UpdateData(FALSE) == ����Ա������ֵ��ֵ���ؼ���
	m_accounts.GetWindowTextW(m_bill);		//��ȡ�༭������ݣ��浽m_bill��
	m_bill.Replace(_T("\n"), _T("\r\n"));	//��ΪWindows�»�����"\r\n"����ӡ��ʼ��и�ֵ������ʹ�õ���"\n"������滻һ�£��ﵽ��ʾ���۵�Ŀ��
	m_bill += "\r\n";						//������Ϊ��׼��ʽ���˵���󣨼���һ��Ŀ����û�л��еģ�Ϊ���ó����Զ�ʶ���ֶ��޸ĸ�ʽ
	m_accounts.SetWindowTextW(m_bill);		// \r�ǻس��������������һ�е���ʼλ�ã�\n�ǻ��з�������
}


void CCalculatorDlg::OnBnClickedBtnFillin()
{
	//���δ����ǵ�����Զ���д�������Ӧ
	//���δ����ǵ�����ñ༭����������ʾΪ��׼�����ʽ

	CString DaySum[7];	//һ�����ɱ�����Ϊ�˼��ٲ���������ۣ������������
	CString	WeekSum;	//���ɱ��������һ���ܺͣ�����֮ǰ�ı�����Ϊȫ�ֵ��ˣ������ڴ������

	for (int i = 0; i < 7; i++)		//����ÿ����ܺ�
	{
		DaySum[i].Format(_T("%.2f"), Day[i]);
	}

	for (int i = 0; i < 7; i++)		//�������޸�Ϊ������ʽ
	{
		date[i] += _T("(") + DaySum[i] + _T(")");
	}

	m_bill = "";					//���༭���������
	for (int i = 6; i >= 0; i--)	//��Ϊ������ʽ
	{
		m_bill += (date[i] + _T("\r\n")) + (data[i] + _T("\r\n"));
	}

	WeekSum.Format(_T("%.2f"), Total);
	m_bill = _T("�ܼ�: ") + WeekSum + _T("Ԫ") + _T("\r\n") + m_bill;
	UpdateData(FALSE);
	m_accounts.SetWindowTextW(m_bill);	
	m_fillin.EnableWindow(FALSE);	//Ϊ�˱����ε����ɶ����д��һ�μ����ֻ����дһ��
}
