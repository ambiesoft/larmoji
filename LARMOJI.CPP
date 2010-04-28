// larmoji.cpp : アプリケーション用クラスの機能定義を行います。
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
// CLarmojiApp

BEGIN_MESSAGE_MAP(CLarmojiApp, CWinApp)
	//{{AFX_MSG_MAP(CLarmojiApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLarmojiApp クラスの構築

CLarmojiApp::CLarmojiApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
	m_bCopying = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CLarmojiApp オブジェクト

CLarmojiApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLarmojiApp クラスの初期化

BOOL CLarmojiApp::InitInstance()
{
#ifdef LANGUAGE_ENGLISH
	HINSTANCE hResource = ::LoadLibrary(_T("larmoji_english.dll"));
	if (hResource != NULL)
		AfxSetResourceHandle(hResource);
#endif
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さく
	// したければ以下の特定の初期化ルーチンの中から不必要なもの
	// を削除してください。

#ifdef _AFXDLL
	Enable3dControls();		// 共有 DLL の中で MFC を使用する場合にはここを呼び出してください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクしている場合にはここを呼び出してください。
#endif

	if( !AfxOleInit() )
		return FALSE;

	TCHAR szProfileName[MAX_PATH] = {_T('\0')};
	VERIFY(GetModuleFileName(NULL, szProfileName, sizeof(szProfileName)));
	LPTSTR lpszExt = _tcsrchr(szProfileName, '.');
	ASSERT(lpszExt);
	*lpszExt = _T('\0');
	lstrcat(szProfileName, _T(".ini"));
	free((void*)m_pszProfileName);
	m_pszProfileName = _tcsdup(szProfileName);

	// メイン ウインドウを作成するとき、このコードは新しいフレーム ウインドウ オブジェクトを作成し、
	// それをアプリケーションのメイン ウインドウにセットします

	CF_LARMOJIIGNORE = RegisterClipboardFormat(_T("CLIPBOARDFORMAT_LARMOJI_IGNORE"));

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// フレームをリソースからロードして作成します
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, 
		NULL);


	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	// サイズの復元
	WINDOWPLACEMENT wp = {0};
	if( GetPrivateProfileStruct(STR_SECTION_SETTING, STR_SECKEY_WP, &wp, sizeof(wp),
		m_pszProfileName) )
	{// 保存データあり
		wp.showCmd &= ~SW_SHOWMINIMIZED;
		pFrame->SetWindowPlacement(&wp);
	}
	else
	{
		pFrame->SetWindowPos(NULL, 0,0, 400,400,SWP_NOMOVE|SWP_NOZORDER);
	}

	pFrame->InitCombobox();	
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLarmojiApp message handlers





/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard 仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラはありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ダイアログを実行するためのアプリケーション コマンド
void CLarmojiApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLarmojiApp メッセージ ハンドラ

void CLarmojiApp::OnFileNew() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	TCHAR szT[MAX_PATH] = {0};
	VERIFY(GetModuleFileName(NULL, szT, sizeof(szT)));

	ShellExecute(*m_pMainWnd, NULL, szT, NULL, NULL, SW_SHOW);
}
