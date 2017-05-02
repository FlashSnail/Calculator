
// CalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#include "CtlEdit.h"
#include "afxtempl.h"	//为了使用CArray而引入

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCalculatorDlg 对话框



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


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//===========================================================
	//设置单选按钮初始选中手动输入
	m_inputway.SetCheck(TRUE);

	//===========================================================
	//这段代码是设置结束日期自动设置为一周后，然而未来如果改进程序为任意日期，此段代码需要修改
	COleDateTime CurrentTime(COleDateTime::GetCurrentTime());
	m_enddata.SetTime(CurrentTime + COleDateTimeSpan(6, 0, 0, 0));
	
	//设置初始焦点在编辑框上，还避免了回车退出程序的问题
	GetDlgItem(IDC_EDIT)->SetFocus();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	//这一段代码是VS2013的bug，关于图片控件载入位图是出现的
	//CStatic* pWnd = (CStatic*)GetDlgItem(IDC_CalOK); // 得到 Picture Control 句柄  
	//pWnd->ModifyStyle(0, SS_BITMAP); // 修改它的属性为位图 

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CCalculatorDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}



BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	//=======================================================================
	//这段代码是修改回车键的响应，我们不想按下回车键就退出程序了，因此将回车的功能修改为Tab
	/*if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		pMsg->wParam = VK_TAB;
	}*/				//为了编辑框可以换行，这里取消这个功能
	//=======================================================================
	//本段代码是使编辑框具有全选功能
	if (pMsg->message == WM_KEYDOWN)
	{
		BOOL b = GetKeyState(VK_CONTROL) & 0x80;
		if (b && (pMsg->wParam == 'a'||pMsg->wParam=='A'))
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETSEL, 0, -1);    //或 SendDlgItemMessage(IDC_Log, EM_SETSEL, 0, -1);</span>  
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCalculatorDlg::OnBnClickedRadioManual()
{
	// TODO:  在此添加控件通知处理程序代码
	// 简单说就是:如果UpdateData(TRUE) == 将控件的值赋值给成员变量; UpdateData(FALSE) == 将成员变量的值赋值给控件。
	UpdateData(TRUE);
	if (!m_bill.IsEmpty())	//如果控件有内容，填写方式改变后清空控件
	{
		m_bill = ("");
	}
	//本段代码是使能填写方式相关控件的
	m_accounts.SetReadOnly(FALSE);	
	m_capture.EnableWindow(FALSE);
	m_begindata.EnableWindow(FALSE);
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedRadioAuto()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!m_bill.IsEmpty())	//如果控件有内容，填写方式改变后清空控件
	{
		m_bill = ("");
	}
	//本段代码是使能填写方式相关控件的
	m_accounts.SetReadOnly(TRUE);
	m_capture.EnableWindow(TRUE);
	m_begindata.EnableWindow(TRUE);	
	UpdateData(FALSE);
}



void CCalculatorDlg::OnDtnDatetimechangeDatetimeBegin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	//本段程序是获取当前选择时间，并且自动设置END TIME
	COleDateTime SelectTime;
	m_begindata.GetTime(SelectTime);
	m_enddata.SetTime(SelectTime + COleDateTimeSpan(6, 0, 0, 0));

	*pResult = 0;
}


void CCalculatorDlg::OnDtnDatetimechangeDatetimeEnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void CCalculatorDlg::OnBnClickedBtnCalculate()	//计算按钮的响应
{
	// TODO:  在此添加控件通知处理程序代码
	m_fillin.EnableWindow(TRUE);	//使能自动填写按钮

	for (int i = 0; i < 7; i++)		//初始化账目信息
	{
		data[i] = "";
	}

	for (int i = 0; i < 7; i++)		//初始化日期信息
	{
		date[i] = "";
	}

	int StartPos = 0;	//索引起始位置
	int EndPos = 0;		//索引终止位置

	StartPos = m_bill.Find(_T("\r\n"));				//对周日进行特殊处理，因为他上一索引方法与其他不同
	EndPos = m_bill.Find(_T("\r\n"), StartPos+1);	//获取下一个换行符的索引

	data[6] = m_bill.Mid(StartPos + 2, EndPos - StartPos -2);	//Mid函数参数是后值减前值得长度。 +2是为了过滤起点的\r\n，-2是为了过滤重点的\r\n
	date[6] = m_bill.Left(StartPos);							//获取周日的日期信息

	for (int i = 5; i >= 0; i--)								//依次获得各天的账目和日期信息
	{
		StartPos = m_bill.Find(_T("\r\n"), EndPos+1);
		date[i] = m_bill.Mid(EndPos + 2, StartPos - EndPos - 2);	//日期信息，注意这个索引位置和减数被减数的关系，
		EndPos = m_bill.Find(_T("\r\n"), StartPos+1);				//另外他必须放在这两个变量赋值中间
		data[i] = m_bill.Mid(StartPos + 2, EndPos - StartPos - 2);	//账目信息				
	}

	//===================================================================
	//	以下是提取支出数字的核心算法，由于账目信息中可能含有数字的干扰 ！！！这里有个BUG隐患，虽然排除了数字的干扰，但如果账目中存在“元”就会出现BUG

//	CString DataDetail_n;

	TCHAR DataTemp;							//存储遍历缓存
//	CArray <CString, CString&> DataDetail_n;	//用来存储当天的账目数值，但这个存储的字符型
//	CString DataDetai[100];
	CString DataDetail_n[50];				//用来存储当天账目数值，但这个存储的数字的倒序
//	CString DataDetail_p[50];				//用来存储当天账目数值，但这个存储的数字的正序  //这里就不用了，直接负遍历了
	CString Temp;							//用来调整数字顺序的缓存
//	DataDetail_n.SetSize(0);					//为了避免内存碎片和提高效率，MSDN建议这么做
	int m;								//单天账目数值个数
	int EndPos_Day[50];				//存储每天的“元”位置，此处的50是预设值，估计一天也没有100个账目；！！！此处是一个BUG隐患
	int End;							//“元”数组索引
//	EndPos_Day.SetSize(1);
	
	//为了避免多次点击计算按钮出现double的情况，初始化和
	//这是一种保护机制，但是我想到了另外一个保护的方法，在计算完后我用一个计算完毕的按钮覆替换计算按钮，想点击也不行了
	//检测到编辑区变化后再复现，这样的UI也更友好，但是这个处理机制也保存在这里
	Total = 0;
	for (int i = 0; i < 7; i++)
	{
		Day[i] = 0;
	}

	for (int i = 0; i < 7; i++)
	{
//		DataDetail_n.RemoveAll();
		//==========================================================
		//这部分是各种参数的初始化
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

		EndPos = data[i].Find(_T("元"));	//现在的工作是要获取一天所有的“元”，并存储起来，在下面的循环中遍历
		EndPos_Day[End] = EndPos;				//第一个“元”
		//===============================================================
		//这是对第一个“元”之前内容的处理，因为他们没有在两个“元”之间
		for (int q = EndPos - 1 ; q > 0; q--)
		{
			DataTemp = data[i].GetAt(q);
			if (DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.'))	//如果是数字或者小数点的话就存储
			{
				DataDetail_n[m] += DataTemp;			//先存储成字符型，因为有小数点的存在，只能这样处理
			}
			if (!(DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.')))	//如果从“元”向前遍历到第一个非数型字符，则跳出循环
			{
				for (int i = DataDetail_n[m].GetLength() - 1; i > -1; i--)	//利用反向遍历或者账目的正序并暂时存储在字符型变量Temp中
				{
					Temp += DataDetail_n[m].GetAt(i);
				}
				Day[i] += _wtof(Temp);	//利用_wtof()将字符型变量转为数型，并和本日账目和进行加和
				//将二者初始化后退出本个账目的循环
				Temp = "";				
				m++;
				break;
			}
		}
		//================================================================
		for (int n = 0; n < data[i].GetLength(); n++)	//通过这个循环来遍历这一天的所有“元”
		{
			EndPos = data[i].Find(_T("元"), EndPos + 1);	//起始位置设置为当前元的下一个位置来寻找下一个元
			if (EndPos != -1)								//如果找到了元
			{
				End++;										//数组索引值+1
				EndPos_Day[End] = EndPos;					//并存储位置索引
			}
			else                                            //如果没有找到或者到达最后一个元，则退出
			{
				break;
			}
//			EndPos_Day.Add(EndPos);
		}		
		//================================================================
		//以下是“元”之间的遍历方法
		for (int p = 0; p < End; p++)	//然后每个“元”之间进行搜索
		{
			for (int j = EndPos_Day[p+1] - 1; j > EndPos_Day[p]; j--)		//j是每个“元”的索引位置
			{
				DataTemp = data[i].GetAt(j);			//开始这一天的信息遍历
				if (DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.'))	//如果是数字或者小数点的话就存储
				{
					DataDetail_n[m] += DataTemp;			//先存储成字符型，因为有小数点的存在，只能这样处理
				}
				if (!(DataTemp >= _T('0') && DataTemp <= _T('9') || DataTemp == _T('.')))	//如果从“元”向前遍历到第一个非数型字符，则跳出循环
				{
					for (int i = DataDetail_n[m].GetLength() - 1; i > -1; i--)		//利用反向遍历或者账目的正序并暂时存储在字符型变量Temp中
					{
						Temp += DataDetail_n[m].GetAt(i);
					}
					Day[i] += _wtof(Temp);		//利用_wtof()将字符型变量转为数型，并和本日账目和进行加和
					//将二者初始化后退出本个账目的循环
					Temp = "";
					m++;
					break;
				}
			}
		}
		//==================================================================
		//回到此层循环进行下一天的计算
	}
	for (int i = 0; i < 7; i++)		//求一周的总和
	{
		Total += Day[i];
	}
	//=======================================================================
	//本周数值计算完毕，以下是显示的功能

	//==========定义各天的数值型变量====================
	CString Monday;
	CString Thursday;
	CString Wednesday;
	CString Tuesday;
	CString Friday;
	CString Saturday;
	CString Sunday;
	CString WeekTotal;		
	//====================================================

	//===========规范化格式并赋值=========================
	Monday.Format(_T("%.2f"), Day[0]);
	Thursday.Format(_T("%.2f"), Day[1]);
	Wednesday.Format(_T("%.2f"), Day[2]);
	Tuesday.Format(_T("%.2f"), Day[3]);
	Friday.Format(_T("%.2f"), Day[4]);				//后续发现命名每天的名称不利于后续编程，但是为了程序的可读性，就保留了这种方法
	Saturday.Format(_T("%.2f"), Day[5]);
	Sunday.Format(_T("%.2f"), Day[6]);
	WeekTotal.Format(_T("%.2f"), Total);
	//====================================================

	//================置于显示区==========================
	m_ctlresult1.SetWindowTextW(Monday);
	m_ctlresult2.SetWindowTextW(Thursday);
	m_ctlresult3.SetWindowTextW(Wednesday);
	m_ctlresult4.SetWindowTextW(Tuesday);
	m_ctlresult5.SetWindowTextW(Friday);
	m_ctlresult6.SetWindowTextW(Saturday);
	m_ctlresult7.SetWindowTextW(Sunday);
	m_ctlresult_total.SetWindowTextW(WeekTotal);
	//====================================================

	m_calculate.EnableWindow(FALSE);		//禁用计算按钮
//	GetDlgItem(IDC_CalOK)->ShowWindow(SW_SHOW);

}


void CCalculatorDlg::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	//本段代码是将从印象笔记中复制出的账目信息在编辑区时改变显示样式
	//原因在于windows中和印象笔记中换行代码不同

	m_calculate.EnableWindow(TRUE);			//一旦编辑区发生变化则使能计算按钮
	UpdateData(TRUE);						//如果UpdateData(TRUE) == 将控件的值赋值给成员变量; UpdateData(FALSE) == 将成员变量的值赋值给控件。
	m_accounts.GetWindowTextW(m_bill);		//读取编辑框的内容，存到m_bill里
	m_bill.Replace(_T("\n"), _T("\r\n"));	//因为Windows下换行是"\r\n"，而印象笔记中赋值下来的使用的是"\n"，因此替换一下，达到显示美观的目的
	m_bill += "\r\n";						//这是因为标准格式的账单最后（即周一账目）是没有换行的，为了让程序自动识别，手动修改格式
	m_accounts.SetWindowTextW(m_bill);		// \r是回车符：光标置于下一行的起始位置，\n是换行符：换行
}


void CCalculatorDlg::OnBnClickedBtnFillin()
{
	//本段代码是点击“自动填写”后的响应
	//本段代码是点击后让编辑区的内容显示为标准结算格式

	CString DaySum[7];	//一个过渡变量，为了减少并令代码美观，引入这个变量
	CString	WeekSum;	//过渡变量，存放一周总和，不把之前的变量存为全局的了，不利于代码理解

	for (int i = 0; i < 7; i++)		//存入每天的总和
	{
		DaySum[i].Format(_T("%.2f"), Day[i]);
	}

	for (int i = 0; i < 7; i++)		//把日期修改为结算形式
	{
		date[i] += _T("(") + DaySum[i] + _T(")");
	}

	m_bill = "";					//将编辑区内容清空
	for (int i = 6; i >= 0; i--)	//化为结算形式
	{
		m_bill += (date[i] + _T("\r\n")) + (data[i] + _T("\r\n"));
	}

	WeekSum.Format(_T("%.2f"), Total);
	m_bill = _T("周计: ") + WeekSum + _T("元") + _T("\r\n") + m_bill;
	UpdateData(FALSE);
	m_accounts.SetWindowTextW(m_bill);	
	m_fillin.EnableWindow(FALSE);	//为了避免多次点击造成多次填写，一次计算后只能填写一次
}
