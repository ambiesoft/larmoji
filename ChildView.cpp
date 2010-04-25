
#include "stdafx.h"
#include "larmoji.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "InputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView
CChildView::CChildView()
{
	m_nCurIndex = 0;
//	m_nCurDBCSIndex = 0;
//	m_pLasthitToMB = NULL;
	m_nCurLen = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_COMMAND(IDM_FONT_PREV, OnFontPrev)
	ON_UPDATE_COMMAND_UI(IDM_FONT_PREV, OnUpdateFontPrev)
	ON_COMMAND(IDM_FONT_NEXT, OnFontNext)
	ON_UPDATE_COMMAND_UI(IDM_FONT_NEXT, OnUpdateFontNext)
	ON_COMMAND(IDM_MENU_INPUTSTRING, OnMenuInputstring)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 描画用のデバイス コンテキスト
	
	if( m_strTheString.length()==0 )
	{
		dc.TextOut(0,0,m_strTheString.c_str());
		return;
	}
	// TODO: メッセージ ハンドラのコードをここに追加してください。
//	dc.SetMapMode(MM_TEXT);
	CFont font;
	CRect r;
	GetClientRect(r);
	WCHAR tc = m_strTheString[m_nCurIndex];

//	dc.DPtoLP(r);
	LOGFONT lf = {0};
//	lf.lfHeight = 0;//-MulDiv(r.Height(), GetDeviceCaps(dc, LOGPIXELSY), 72);//-r.Height();
	lf.lfHeight = r.Height();
	lf.lfWidth = 0;


	if( ((CMainFrame*)theApp.m_pMainWnd)->IsBold() )
		lf.lfWeight = FW_BOLD;

	if( ((CMainFrame*)theApp.m_pMainWnd)->IsItalic() )
		lf.lfItalic = TRUE;

	lf.lfCharSet = 0;//GB2312_CHARSET;
	lf.lfPitchAndFamily = FF_MODERN;

	lstrcpy(lf.lfFaceName, ((CMainFrame*)theApp.m_pMainWnd)->GetCurFontName());
	font.CreateFontIndirect(&lf);
	CFont* pOldFont = dc.SelectObject(&font);

	WCHAR szText[3];
	if( m_strTheString.length()==0 )
	{
//		dc.TextOut(0,0,m_strTheString.c_str());
		TextOutW(dc, 0, 0, m_strTheString.c_str(), m_strTheString.length());
	}
#if 0
	else if( IsDBCSLeadByte( (BYTE)(TCHAR)m_strTheString[m_nCurIndex] ))
	{
		szText[0] = m_strTheString[m_nCurIndex];
		szText[1] = m_strTheString[m_nCurIndex+1];
		dc.TextOut(0,0,szText,2);
	}
#endif
	else
	{
		szText[0] = m_strTheString[m_nCurIndex];
		DrawTextW(dc, &tc, 1,
			&r, DT_CENTER|DT_TOP);
	}

	dc.SelectObject(pOldFont);
}

void CChildView::SetTheString(LPCWSTR lpszString)
{

	if( lpszString==NULL )
	{
//		m_strTheString.Empty();
		m_strTheString = L"";
	}
	else
	{
#if 0
		int nCount = 0;
		int nOrgLen = lstrlen(lpszString);
		LPTSTR p = m_strTheString.GetBuffer(min(260,nOrgLen));
		while(*lpszString && nCount < 256)
		{
			if( *lpszString != _T('\t') 
				&& *lpszString != _T('\r') 
				&& *lpszString != _T('\n') )
			{
				p[nCount++] = *(lpszString++);
				if( IsDBCSLeadByte( (BYTE)*(lpszString-1) ) )
				{
					p[nCount++] = *(lpszString++);
				}
			}
			else
				lpszString++;
		}
		p[nCount] = _T('\0');
		m_strTheString.ReleaseBuffer();
#endif

		WCHAR* p = (WCHAR*)calloc(256, sizeof(WCHAR));
		memcpy(p, lpszString, sizeof(WCHAR)*min(255, wcslen(lpszString)));
		m_strTheString = p;
		free(p);
	}

//	m_strTheString = lpszString;
	m_nCurIndex = 0;
//	m_nCurDBCSIndex = 0;
//	m_pLasthitToMB = NULL;
	
//	{
//		BSTR p = m_strTheString.AllocSysString();
//		m_nCurDBCSLen = wcslen(p);
//		::SysFreeString(p);
//	}
	m_nCurLen = m_strTheString.length();
	InvalidateRect(NULL);
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CWnd ::OnLButtonDblClk(nFlags, point);
/***
	CInputDialog dlg;
	if( IDOK!=dlg.DoModal() )
		return;

	SetTheString(dlg.m_strString);
#ifndef UNICODE
	ASSERT(0);
#endif
	InvalidateRect(NULL);

***/
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_oleTarget.Register(this);
	return 0;
}

BOOL CChildView::SetCodeString(LPTSTR szCode)
{
/**
	if( m_strTheString.IsEmpty() )
	{
		lstrcpy(szCode, _T("SJIS :"));
	}
	else if( IsDBCSLeadByte((BYTE)m_strTheString[m_nCurIndex]) )
	{
		_stprintf(szCode, _T("SJIS : 0x%02x%02x"), 
			(0xFF & (int)(UINT)m_strTheString[m_nCurIndex]),
			(0xFF & (int)(UINT)m_strTheString[m_nCurIndex+1]));

	}
	else
	{
		_stprintf(szCode, _T("SJIS : 0x%02x"), 
			(0xFF & (int)(UINT)m_strTheString[m_nCurIndex]));
	}
**/

	_stprintf(szCode, _T(" 0x%04x"),
		0xFFFF & (WCHAR)(UINT)m_strTheString[m_nCurIndex])    ;
	return TRUE;
}

void CChildView::OnFontPrev() 
{
	// TODO: この位置にコマンド　 ハンドラ用のコードを追加してください
	if( m_strTheString.length() <= m_nCurIndex )
		return;

	if(m_nCurIndex==0)
		return;

	if( m_nCurIndex >= 2 )
	{	
//		TRACE(CString(m_strTheString[m_nCurIndex-2])+_T('\n'));

//		if( m_pLasthitToMB==NULL )
//		{
			m_nCurIndex--;
//		}
//		else
		{
/**
			LPCTSTR pBuff = m_strTheString;
			pBuff += m_nCurIndex;
			LPCTSTR pPrev = _tcsdec(m_pLasthitToMB, pBuff);
			if(NULL == pPrev)
			{
				pPrev = _tcsdec((LPCTSTR)m_strTheString, pBuff);
				ASSERT(pPrev);
			}

			m_pLasthitToMB = pPrev;
			m_nCurIndex-=(pBuff-pPrev);
**/

		}
	}
	else
	{
		m_nCurIndex--;
	}

	InvalidateRect(NULL);
	
}

void CChildView::OnUpdateFontPrev(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	pCmdUI->Enable(m_nCurIndex!=0);	
}

void CChildView::OnFontNext() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	if( m_strTheString.length() <= (m_nCurIndex+1) )
		return;

//	if( IsDBCSLeadByte((BYTE)m_strTheString[m_nCurIndex]) )
//	{
//		m_pLasthitToMB = m_strTheString;
//		m_pLasthitToMB += m_nCurIndex;
//		m_nCurIndex++;
//	}
	m_nCurIndex++;
//	m_nCurDBCSIndex++;
	InvalidateRect(NULL);
}

void CChildView::OnUpdateFontNext(CCmdUI* pCmdUI) 
{
	// TODO: この位置に command update UI ハンドラ用のコードを追加してください
	if( m_strTheString.length()==0 )
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
//		if( IsDBCSLeadByte( (BYTE)m_strTheString[m_nCurIndex] ) )
//		{
//			pCmdUI->Enable(m_strTheString.GetLength() > (m_nCurIndex+2));	
//		}
//		else
		{
			pCmdUI->Enable(m_strTheString.length() > (m_nCurIndex+1));	
		}
	}
}

void CChildView::OnMenuInputstring() 
{
	// TODO: この位置にコマンド ハンドラ用のコードを追加してください
	CInputDialog dlg;
	if( IDOK!=dlg.DoModal() )
		return;

	SetTheString(dlg.m_strString);
#ifndef UNICODE
	ASSERT(0);
#endif
	InvalidateRect(NULL);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	OnFontNext();
	CWnd ::OnLButtonDown(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	OnFontPrev();
	CWnd ::OnRButtonDown(nFlags, point);
}



int CChildView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	TRACE(_T("%d %d\n"), nHitTest, message);
	return CWnd ::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
