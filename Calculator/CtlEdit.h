#pragma once
#include "afxwin.h"
class CCtlEdit :
	public CEdit
{
public:
	CCtlEdit();
	~CCtlEdit();
	CEdit m_ctledit;
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

