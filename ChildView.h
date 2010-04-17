
#if !defined(AFX_CHILDVIEW_H__D578306C_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
#define AFX_CHILDVIEW_H__D578306C_745A_11D5_8E03_A40A1FE48159__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainDropTarget.h"

class CChildView : public CWnd
{

public:
	CChildView();


public:
	int m_nCurIndex;
//	int m_nCurDBCSIndex;
	int m_nCurLen;
protected:
	CMainDropTarget m_oleTarget;
//	LPCTSTR m_pLasthitToMB;

public:

	// ClassWizard
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL


public:
	int GetCurLen() const {
		return m_nCurLen;
	}
	BOOL SetCodeString(LPTSTR szCode);
	void SetTheString(LPCWSTR lpszString);
	LPCWSTR GetTheString() const 
	{
		return m_strTheString.c_str();
	}

	virtual ~CChildView();


protected:
	wstring m_strTheString;
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFontPrev();
	afx_msg void OnUpdateFontPrev(CCmdUI* pCmdUI);
	afx_msg void OnFontNext();
	afx_msg void OnUpdateFontNext(CCmdUI* pCmdUI);
	afx_msg void OnMenuInputstring();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_CHILDVIEW_H__D578306C_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
