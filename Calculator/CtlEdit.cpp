#include "stdafx.h"
#include "CtlEdit.h"


CCtlEdit::CCtlEdit()
{
}


CCtlEdit::~CCtlEdit()
{
}


BEGIN_MESSAGE_MAP(CCtlEdit, CEdit)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()




BOOL CCtlEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		pMsg->wParam = VK_TAB;
	}
	//响应Ctrl+A全选
	if (pMsg->message == WM_KEYDOWN)
	{
		BOOL b = GetKeyState(VK_CONTROL) & 0x80;
		if (b && (pMsg->wParam == 'a'||pMsg->wParam=='A'))
		{
			SetSel(0, -1);	//直接调用就行了
			return TRUE;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}


void CCtlEdit::OnLButtonDblClk(UINT nFlags, CPoint point)	//让编辑框具有双击全选的功能，但好像之前也是有的
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SetSel(0, -1);	
	CEdit::OnLButtonDblClk(nFlags, point);
}
