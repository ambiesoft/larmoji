
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


CLarmojiApp::CLarmojiApp()
{
	m_bCopying = FALSE;
}


CLarmojiApp theApp;

BOOL CLarmojiApp::InitInstance()
{
#ifdef LANGUAGE_ENGLISH
	HINSTANCE hResource = ::LoadLibrary(_T("larmoji_english.dll"));
	if (hResource != NULL)
		AfxSetResourceHandle(hResource);
#endif

#ifdef _AFXDLL
	// Enable3dControls();
#else
	Enable3dControlsStatic();
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

	CF_LARMOJIIGNORE = RegisterClipboardFormat(_T("CLIPBOARDFORMAT_LARMOJI_IGNORE"));

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;


	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, 
		NULL);

	WINDOWPLACEMENT wp = {0};
	if( GetPrivateProfileStruct(STR_SECTION_SETTING, STR_SECKEY_WP, &wp, sizeof(wp),
		m_pszProfileName) )
	{
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





class CAboutDlg : public CDialog
{
public:
	CAboutDlg();


	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL


protected:
	//{{AFX_MSG(CAboutDlg)
		// 
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
		// 
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CLarmojiApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CLarmojiApp::OnFileNew() 
{
	TCHAR szT[MAX_PATH] = {0};
	VERIFY(GetModuleFileName(NULL, szT, sizeof(szT)));

	ShellExecute(*m_pMainWnd, NULL, szT, NULL, NULL, SW_SHOW);
}
