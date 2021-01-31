// MainFrm.h : CMainFrame クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D578306A_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
#define AFX_MAINFRM_H__D578306A_745A_11D5_8E03_A40A1FE48159__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "strings.h"
#include "ChildView.h"
#include "MainToolBar.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

public:


public:
	UINT GetFlag() const { return m_nFlags; }
	BOOL IsBold() const { return m_nFlags & APPFLAGS_BOLD; }
	BOOL IsItalic() const { return m_nFlags & APPFLAGS_ITALIC; }


	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

	virtual void GetMessageString(UINT nID, CString& rMessage) const override;

public:
	CString GetCurFontName();
	BOOL InitCombobox();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CStatusBar  m_wndStatusBar;
	CMainToolBar    m_wndToolBar;

public:
	CChildView    m_wndView;

protected:
	HWND m_hNextWnd;
	
	UINT m_nFlags;
	enum {
		APPFLAGS_WATCHCB         = 1,
		APPFLAGS_ALWAYSTOP       = 2,
		APPFLAGS_BOLD            = 4,
		APPFLAGS_ITALIC          = 8,
	};
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnWatchClipboard();
	afx_msg void OnUpdateWatchClipboard(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnDrawClipboard();
	afx_msg void OnWindowAlwaystop();
	afx_msg void OnUpdateWindowAlwaystop(CCmdUI* pCmdUI);
	afx_msg void OnFontBold();
	afx_msg void OnUpdateFontBold(CCmdUI* pCmdUI);
	afx_msg void OnFontItalic();
	afx_msg void OnUpdateFontItalic(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateCode(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateDBCSIndex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndex(CCmdUI* pCmdUI);
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_MAINFRM_H__D578306A_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
