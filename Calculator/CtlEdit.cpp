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
	// TODO:  �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		pMsg->wParam = VK_TAB;
	}
	//��ӦCtrl+Aȫѡ
	if (pMsg->message == WM_KEYDOWN)
	{
		BOOL b = GetKeyState(VK_CONTROL) & 0x80;
		if (b && (pMsg->wParam == 'a'||pMsg->wParam=='A'))
		{
			SetSel(0, -1);	//ֱ�ӵ��þ�����
			return TRUE;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}


void CCtlEdit::OnLButtonDblClk(UINT nFlags, CPoint point)	//�ñ༭�����˫��ȫѡ�Ĺ��ܣ�������֮ǰҲ���е�
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetSel(0, -1);	
	CEdit::OnLButtonDblClk(nFlags, point);
}
