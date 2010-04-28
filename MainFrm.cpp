// MainFrm.cpp : CMainFrame クラスの動作の定義を行います。
//

#include "stdafx.h"

#include "larmoji.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SJISCODE, OnUpdateCode)
//	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DBCSINDEX, OnUpdateDBCSIndex)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DBCSINDEX, OnUpdateIndex)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケータ
//	ID_INDICATOR_KANA,
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
	ID_INDICATOR_DBCSINDEX,
	ID_INDICATOR_SJISCODE,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの構築/消滅

CMainFrame::CMainFrame()
{
	// TODO: この位置にメンバの初期化処理コードを追加してください。
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

	HICON hIcon = LoadIcon(theApp.m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	// フレームのクライアント領域全体を占めるビューを作成します。
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // 作成に失敗
	}

	int nWatchCBIndex = m_wndToolBar.CommandToIndex(IDM_WATCH_CLIPBOARD);
	ASSERT(nWatchCBIndex != -1);
	m_wndToolBar.SetButtonStyle(nWatchCBIndex, TBBS_CHECKBOX); 



	#define SNAP_WIDTH 150 //the width of the combo box
	CRect rect;
	//set up the ComboBox control as a snap mode select box
	//
	//First get the index of the placeholder's position in the toolbar
	int nFontNameIndex = 0;
	while (m_wndToolBar.GetItemID(nFontNameIndex) != IDP_FONTNAME) nFontNameIndex++;

	//next convert that button to a seperator and get its position
	m_wndToolBar.SetButtonInfo(nFontNameIndex, IDP_FONTNAME, TBBS_SEPARATOR,
		SNAP_WIDTH);
	m_wndToolBar.GetItemRect(nFontNameIndex, &rect);

	//expand the rectangle to allow the combo box room to drop down
	rect.top+=1;
	rect.bottom += 200;

	// then .Create the combo box and show it
	if (!m_wndToolBar.m_wndFontName.Create(WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL| 
									   CBS_DROPDOWNLIST,
									   rect, &m_wndToolBar, IDC_FONTNAME_COMBO))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // 作成に失敗
	}

	// TODO: ツール バーをドッキング可能にしない場合は以下の３行を削除
	//       してください。
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
	// TODO: この位置で CREATESTRUCT cs を修正して、Window クラスやスタイルを
	//       修正してください。

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	if( m_nFlags & APPFLAGS_ALWAYSTOP )
		cs.dwExStyle |= WS_EX_TOPMOST;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame クラスの診断

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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame メッセージ ハンドラ
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// ビュー ウィンドウにフォーカスを与えます。
	UNREFERENCED_PARAMETER(pOldWnd);
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ビューに最初にコマンドを処理する機会を与えます。
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 処理されなかった場合にはデフォルトの処理を行います。
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnWatchClipboard() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
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
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
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

	int nLastSel = m_wndToolBar.m_wndFontName.GetCurSel();
	if( nLastSel != CB_ERR )
		theApp.WriteProfileInt(STR_SECTION_SETTING, STR_FONTFACECOMBO_INDEX, nLastSel);
	
	CFrameWnd::OnDestroy();
}

void CMainFrame::OnEditPaste() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
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
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	pCmdUI->Enable(::IsClipboardFormatAvailable(CF_UNICODETEXT));
}




void CMainFrame::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter) 
{
	CFrameWnd::OnChangeCbChain(hWndRemove, hWndAfter);
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
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
	
	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	ASSERT(m_nFlags & APPFLAGS_WATCHCB);

	if( !theApp.m_bCopying )
		OnEditPaste();

	if(m_hNextWnd)
		::SendMessage(m_hNextWnd, WM_DRAWCLIPBOARD, 0, 0);

	PostMessage(WM_SETMESSAGESTRING);
}

void CMainFrame::OnWindowAlwaystop() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	m_nFlags ^= APPFLAGS_ALWAYSTOP;
	
	SetWindowPos( (m_nFlags & APPFLAGS_ALWAYSTOP) ? &wndTopMost: &wndNoTopMost,
		0,0,0,0, SWP_NOMOVE|SWP_NOSIZE );
}

void CMainFrame::OnUpdateWindowAlwaystop(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	pCmdUI->SetCheck( (m_nFlags & APPFLAGS_ALWAYSTOP) != 0 );
}


int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe,NEWTEXTMETRICEX *lpntme,int nFontType,LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lpntme);
	ASSERT(lpelfe);
	ASSERT(lParam);
//	CFontNameComboBox* pwndFontName = (CFontNameComboBox*)lParam;
	if( nFontType == TRUETYPE_FONTTYPE 
		&& lpelfe->elfLogFont.lfFaceName[0] != _T('@') )
//		&& (lpelfe->elfLogFont.lfPitchAndFamily & VARIABLE_PITCH)==0 )
	{
		TRACE(CString(lpelfe->elfLogFont.lfFaceName)+_T('\n'));
	//fill the combo box
		set<wstring>* pset = (set<wstring>*)lParam;
		pset->insert(lpelfe->elfLogFont.lfFaceName);
	}
	return 1;
}

BOOL CMainFrame::InitCombobox()
{
	CDC* pDC = GetDC();
	

	set<wstring> stringset;

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


	set<wstring>::iterator it;
	for ( it = stringset.begin() ; it != stringset.end() ; ++it )
	{
		COMBOBOXEXITEM item = {0};
		item.iItem = 0;
		item.mask = CBEIF_TEXT;
//		item.pszText = (LPTSTR)lpelfe->elfLogFont.lfFaceName;
		item.pszText = (LPTSTR)((*it).c_str());
		m_wndToolBar.m_wndFontName.InsertItem(&item);
	}

	int nLastSel = theApp.GetProfileInt(STR_SECTION_SETTING, STR_FONTFACECOMBO_INDEX, 0);
	if( nLastSel > m_wndToolBar.m_wndFontName.GetCount() )
		nLastSel = 0;

	m_wndToolBar.m_wndFontName.SetCurSel(nLastSel);
	
	ReleaseDC(pDC);
	return TRUE;
}

CString CMainFrame::GetCurFontName()
{
	CString strRet;
	
	int nCurSel = m_wndToolBar.m_wndFontName.GetCurSel();
	ASSERT(nCurSel != CB_ERR );
	
	COMBOBOXEXITEM item = {0};
	item.iItem = nCurSel;
	item.cchTextMax = LF_FACESIZE + 1;
	item.mask = CBEIF_TEXT;
	item.pszText = strRet.GetBuffer(LF_FACESIZE+1);
	m_wndToolBar.m_wndFontName.GetItem(&item);

	strRet.ReleaseBuffer();
	return strRet;
}

void CMainFrame::OnUpdateCode(CCmdUI* pCmdUI)
{
	static TCHAR szCode[32];
	m_wndView.SetCodeString(szCode);
	pCmdUI->SetText(szCode);
}

/**
void CMainFrame::OnUpdateDBCSIndex(CCmdUI* pCmdUI)
{
	static TCHAR szCode[20];

	wsprintf( szCode, _T("%3d / %3d"), 
		(1+m_wndView.m_nCurDBCSIndex), m_wndView.GetCurDBCSLen());

	pCmdUI->SetText(szCode);
}
**/

void CMainFrame::OnUpdateIndex(CCmdUI* pCmdUI)
{
	static TCHAR szCode[32];

	wsprintf( szCode, _T("%3d / %3d"), 
		(1+m_wndView.m_nCurIndex), m_wndView.GetCurLen());

	pCmdUI->SetText(szCode);
}

void CMainFrame::OnFontBold() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	m_nFlags ^= APPFLAGS_BOLD;
	m_wndView.InvalidateRect(NULL);
}

void CMainFrame::OnUpdateFontBold(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	pCmdUI->SetCheck( (m_nFlags & APPFLAGS_BOLD) ? 1 : 0 );
}

void CMainFrame::OnFontItalic() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	m_nFlags ^= APPFLAGS_ITALIC;
	m_wndView.InvalidateRect(NULL);
}

void CMainFrame::OnUpdateFontItalic(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	pCmdUI->SetCheck( (m_nFlags & APPFLAGS_ITALIC) ? 1 : 0 );
}

//DEL void CMainFrame::OnMenuInputstring() 
//DEL {
//DEL 	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
//DEL 	
//DEL }
