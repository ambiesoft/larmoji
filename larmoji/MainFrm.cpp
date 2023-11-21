// MainFrm.cpp
//

#include "stdafx.h"

#include "../../lsMisc/HighDPI.h"
#include "../../lsMisc/UrlEncode.h"
#include "../../lsMisc/GetClipboardText.h"

#include "larmoji.h"
#include "COptionDialog.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace Ambiesoft;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDM_WATCH_CLIPBOARD, OnWatchClipboard)
	ON_UPDATE_COMMAND_UI(IDM_WATCH_CLIPBOARD, OnUpdateWatchClipboard)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
	ON_COMMAND(IDM_WINDOW_ALWAYSTOP, OnWindowAlwaystop)
	ON_UPDATE_COMMAND_UI(IDM_WINDOW_ALWAYSTOP, OnUpdateWindowAlwaystop)
	ON_COMMAND(IDM_FONT_BOLD, OnFontBold)
	ON_UPDATE_COMMAND_UI(IDM_FONT_BOLD, OnUpdateFontBold)
	ON_COMMAND(IDM_FONT_ITALIC, OnFontItalic)
	ON_UPDATE_COMMAND_UI(IDM_FONT_ITALIC, OnUpdateFontItalic)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_UNICODE, OnUpdateCode)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_INDEX, OnUpdateIndex)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnToolsOptions)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
//	ID_INDICATOR_KANA,
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
	ID_INDICATOR_INDEX,
	ID_INDICATOR_UNICODE,
};


CMainFrame::CMainFrame() :
	m_options(theApp.GetIniPath())
{
	m_nFlags = (UINT)theApp.GetProfileInt(STR_SECTION_SETTING, STR_SECKEY_FLAGS, 0);
	m_hNextWnd = NULL;
}

CMainFrame::~CMainFrame()
{
}




int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	const bool bBigToolbar = (GetDPIScale() > 96);

	HICON hIcon = LoadIcon(theApp.m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	const UINT uIDR_MAINFRAME = bBigToolbar ? IDR_MAINFRAME_BIG : IDR_MAINFRAME;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(uIDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	int nWatchCBIndex = m_wndToolBar.CommandToIndex(IDM_WATCH_CLIPBOARD);
	ASSERT(nWatchCBIndex != -1);
	m_wndToolBar.SetButtonStyle(nWatchCBIndex, TBBS_CHECKBOX); 

	CRect rect;
	int nIndex = m_wndToolBar.GetToolBarCtrl().CommandToIndex(IDP_FONTNAME);
	m_wndToolBar.SetButtonInfo(nIndex, IDP_FONTNAME, TBBS_SEPARATOR, 205);
	m_wndToolBar.GetToolBarCtrl().GetItemRect(nIndex, &rect);
//	rect.top = 1;
	rect.bottom = rect.top + 250 /*drop height*/;

	// then .Create the combo box and show it
	if (!m_wndToolBar.m_cmbFontName.Create(
		WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST,
		rect, &m_wndToolBar, IDP_FONTNAME))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}
	if (bBigToolbar)
		m_wndToolBar.m_cmbFontName.SetItemHeight(-1, 30);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}
	else
	{
		UINT nID = 0;
		UINT nStyle = 0;
		int cxWidth = 0;
		m_wndStatusBar.GetPaneInfo(0, nID, nStyle, cxWidth);
		m_wndStatusBar.SetPaneInfo(0, nID, nStyle, cxWidth / 3);
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if( m_nFlags & APPFLAGS_WATCHCB )
		m_hNextWnd = SetClipboardViewer();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~WS_VISIBLE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	if( m_nFlags & APPFLAGS_ALWAYSTOP )
		cs.dwExStyle |= WS_EX_TOPMOST;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}


#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	UNREFERENCED_PARAMETER(pOldWnd);
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
	CFrameWnd::GetMessageString(nID, rMessage);
	rMessage = I18N(rMessage);
}


BOOL CMainFrame::OnToolTipText(UINT uID, NMHDR* pNMHDR, LRESULT* pResult)
{
	ENSURE_ARG(pNMHDR != NULL);
	ENSURE_ARG(pResult != NULL);
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	TCHAR szFullText[256];
	CString strTipText;
	UINT_PTR nID = pNMHDR->idFrom;
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
		return CFrameWnd::OnToolTipText(uID, pNMHDR, pResult);
	}

	if (nID != 0) // will be zero on a separator
	{
		// don't handle the message if no string resource found
		if (AfxLoadString((UINT)nID, szFullText) == 0)
			return FALSE;

		// this is the command id, not the button index
		AfxExtractSubString(strTipText, szFullText, 1, '\n');

		strTipText = I18N(strTipText);
	}
#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		Checked::strncpy_s(pTTTA->szText, _countof(pTTTA->szText), strTipText, _TRUNCATE);
	else
		_mbstowcsz(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		Checked::wcsncpy_s(pTTTW->szText, _countof(pTTTW->szText), strTipText, _TRUNCATE);
#endif
	* pResult = 0;

	// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE | SWP_NOOWNERZORDER);

	return TRUE;    // message was handled
}
void CMainFrame::OnWatchClipboard() 
{
	m_nFlags ^= APPFLAGS_WATCHCB;
	if( m_nFlags & APPFLAGS_WATCHCB )
	{
		ASSERT(m_hNextWnd==NULL);
		m_hNextWnd = SetClipboardViewer();
	}
	else
	{
		ChangeClipboardChain(m_hNextWnd);
		m_hNextWnd = NULL;
	}
}

void CMainFrame::OnUpdateWatchClipboard(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( (m_nFlags & APPFLAGS_WATCHCB) != 0 );
	pCmdUI->Enable();
}

void CMainFrame::OnDestroy() 
{
	WINDOWPLACEMENT wp = {0};
	if( GetWindowPlacement(&wp) )
	{
		WritePrivateProfileStruct(STR_SECTION_SETTING, STR_SECKEY_WP, &wp, sizeof(wp),
			theApp.m_pszProfileName);
	}
	theApp.WriteProfileInt(STR_SECTION_SETTING, STR_SECKEY_FLAGS, m_nFlags);

	if( m_nFlags & APPFLAGS_WATCHCB )
	{
		ChangeClipboardChain(m_hNextWnd);
		m_hNextWnd = NULL;
	}

	int nLastSel = m_wndToolBar.m_cmbFontName.GetCurSel();
	if (nLastSel != CB_ERR)
	{
		CString strFontName;
		m_wndToolBar.m_cmbFontName.GetLBText(nLastSel, strFontName);
		VERIFY(!strFontName.IsEmpty());
		theApp.WriteProfileString(STR_SECTION_SETTING, STR_FONTFACECOMBO_FONTNAME,
			UrlEncodeStd(strFontName).c_str());
		theApp.WriteProfileInt(STR_SECTION_SETTING, STR_FONTFACECOMBO_INDEX, nLastSel);
	}
	CFrameWnd::OnDestroy();
}

void CMainFrame::OnEditPaste() 
{
	if( !::IsClipboardFormatAvailable(CF_UNICODETEXT) )
		return;

	if( !OpenClipboard() )
		return;

	struct stCPCloser {
		~stCPCloser() {
			::CloseClipboard();
		}
	} stcpcloser;

	if ( ::IsClipboardFormatAvailable(theApp.CF_LARMOJIIGNORE) )
	{
		return;
	}

	HANDLE h = ::GetClipboardData(CF_UNICODETEXT);

	m_wndView.SetTheString( (LPCWSTR)GlobalLock(h) );
	GlobalUnlock(h);
}

void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(::IsClipboardFormatAvailable(CF_UNICODETEXT));
}




void CMainFrame::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter) 
{
	CFrameWnd::OnChangeCbChain(hWndRemove, hWndAfter);
	
	ASSERT(m_nFlags & APPFLAGS_WATCHCB);
	if(m_hNextWnd == hWndRemove)
	{
		m_hNextWnd = hWndAfter;
	}
	else if(m_hNextWnd != NULL)
	{
		::SendMessage(m_hNextWnd, WM_CHANGECBCHAIN, (WPARAM)hWndRemove, (LPARAM)hWndAfter);
	}
}


void CMainFrame::OnDrawClipboard() 
{
	CFrameWnd::OnDrawClipboard();
	
	ASSERT(m_nFlags & APPFLAGS_WATCHCB);

	if (::GetActiveWindow() != m_hWnd)
	{
		OnEditPaste();
	}

	if(m_hNextWnd)
		::SendMessage(m_hNextWnd, WM_DRAWCLIPBOARD, 0, 0);

	// Update the status bar
	PostMessage(WM_SETMESSAGESTRING);
}

void CMainFrame::OnWindowAlwaystop() 
{
	m_nFlags ^= APPFLAGS_ALWAYSTOP;
	
	SetWindowPos( (m_nFlags & APPFLAGS_ALWAYSTOP) ? &wndTopMost: &wndNoTopMost,
		0,0,0,0, SWP_NOMOVE|SWP_NOSIZE );
}

void CMainFrame::OnUpdateWindowAlwaystop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( (m_nFlags & APPFLAGS_ALWAYSTOP) != 0 );
}

struct custom_compare final
{
	bool operator() (const wstring& left, const wstring& right) const
	{
		return lstrcmpi(right.c_str(), left.c_str()) < 0;
	}
};
int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe,NEWTEXTMETRICEX *lpntme,int nFontType,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lpntme);
	ASSERT(lpelfe);
	ASSERT(lParam);

	if( nFontType == TRUETYPE_FONTTYPE 
		&& lpelfe->elfLogFont.lfFaceName[0] != _T('@') )
	{
		set<wstring, custom_compare>* pset = (set<wstring, custom_compare>*)lParam;
		pset->insert(lpelfe->elfLogFont.lfFaceName);
	}
	return 1;
}

BOOL CMainFrame::InitCombobox()
{
	CDC* pDC = GetDC();

	set<wstring, custom_compare> stringset({}, custom_compare{});

	{
		LOGFONT lf = {0};
		lf.lfCharSet = SHIFTJIS_CHARSET;
		lf.lfFaceName[0] = '\0';

		EnumFontFamiliesEx( *pDC, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&stringset, 0);
	}
	{
		LOGFONT lf = {0};
		lf.lfCharSet = HANGEUL_CHARSET;
		lf.lfFaceName[0] = '\0';

		EnumFontFamiliesEx( *pDC, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&stringset, 0);
	}
	{
		LOGFONT lf = {0};
		lf.lfCharSet = GB2312_CHARSET;
		lf.lfFaceName[0] = '\0';

		EnumFontFamiliesEx( *pDC, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&stringset, 0);
	}
	{
		LOGFONT lf = {0};
		lf.lfCharSet = CHINESEBIG5_CHARSET;
		lf.lfFaceName[0] = '\0';

		EnumFontFamiliesEx( *pDC, &lf, (FONTENUMPROC)EnumFontFamExProc, (LPARAM)&stringset, 0);
	}


	for ( auto&& s : stringset)
	{
		COMBOBOXEXITEM item = {0};
		item.iItem = 0;
		item.mask = CBEIF_TEXT;
		item.pszText = (LPTSTR)(s.c_str());
		m_wndToolBar.m_cmbFontName.InsertItem(&item);
	}

	int nLastSel = -1;
	CString strFontName = theApp.GetProfileString(STR_SECTION_SETTING, STR_FONTFACECOMBO_FONTNAME);
	strFontName = UrlDecodeStd<wstring>(strFontName).c_str();
	if(!strFontName.IsEmpty())
		nLastSel = m_wndToolBar.m_cmbFontName.FindStringExact(0, strFontName);
	
	// old measure
	if(nLastSel < 0)
		nLastSel = theApp.GetProfileInt(STR_SECTION_SETTING, STR_FONTFACECOMBO_INDEX, 0);
	
	if (nLastSel < 0)
		nLastSel = 0;
	if( nLastSel > m_wndToolBar.m_cmbFontName.GetCount() )
		nLastSel = 0;

	m_wndToolBar.m_cmbFontName.SetCurSel(nLastSel);
	
	ReleaseDC(pDC);

	Invalidate();
	UpdateWindow();
	return TRUE;
}

CString CMainFrame::GetCurFontName()
{
	CString strRet;
	
	int nCurSel = m_wndToolBar.m_cmbFontName.GetCurSel();
	if (nCurSel == CB_ERR)
		return strRet;
	
	COMBOBOXEXITEM item = {0};
	item.iItem = nCurSel;
	item.cchTextMax = LF_FACESIZE + 1;
	item.mask = CBEIF_TEXT;
	item.pszText = strRet.GetBuffer(LF_FACESIZE+1);
	m_wndToolBar.m_cmbFontName.GetItem(&item);

	strRet.ReleaseBuffer();
	return strRet;
}

void CMainFrame::OnUpdateCode(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(m_wndView.GetCodeString());
}

void CMainFrame::OnUpdateIndex(CCmdUI* pCmdUI)
{
	static TCHAR szCode[32];

	wsprintf( szCode, _T("%3d / %3d"), 
		(1+m_wndView.m_nCurIndex), m_wndView.GetCurLen());

	pCmdUI->SetText(szCode);
}

void CMainFrame::OnFontBold() 
{
	m_nFlags ^= APPFLAGS_BOLD;
	m_wndView.InvalidateRect(NULL);
}

void CMainFrame::OnUpdateFontBold(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( (m_nFlags & APPFLAGS_BOLD) ? 1 : 0 );
}

void CMainFrame::OnFontItalic() 
{
	m_nFlags ^= APPFLAGS_ITALIC;
	m_wndView.InvalidateRect(NULL);
}

void CMainFrame::OnUpdateFontItalic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( (m_nFlags & APPFLAGS_ITALIC) ? 1 : 0 );
}



void CMainFrame::OnToolsOptions()
{

	m_options.DoModal();
}
