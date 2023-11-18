
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
	m_nCurLen = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_COMMAND(IDM_FONT_PREV, OnLetterPrev)
	ON_UPDATE_COMMAND_UI(IDM_FONT_PREV, OnUpdateLetterPrev)
	ON_COMMAND(IDM_FONT_NEXT, OnLetterNext)
	ON_UPDATE_COMMAND_UI(IDM_FONT_NEXT, OnUpdateLetterNext)
	ON_COMMAND(IDM_MENU_INPUTSTRING, OnMenuInputstring)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	//}}AFX_MSG_MAP
	ON_WM_MOUSEWHEEL()
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
	CString curFontName = MF_->GetCurFontName();
	if (curFontName.IsEmpty())
		return;

	CPaintDC dc(this);
	
	if( m_strTheString.length()==0 )
	{
		dc.TextOut(0, 0, m_strTheString.c_str());
		return;
	}

	CFont font;
	CRect r;
	GetClientRect(r);

	WCHAR tc[2];
	tc[0] = m_strTheString[m_nCurIndex];
	tc[1] = 0;
	if (IS_SURROGATE_PAIR(m_strTheString[m_nCurIndex], m_strTheString[m_nCurIndex + 1]))
	{
		tc[1]= m_strTheString[m_nCurIndex+1];
	}
	

	LOGFONT lf = {0};
	lf.lfHeight = r.Height();
	lf.lfWidth = 0;


	if (MF_->IsBold())
		lf.lfWeight = FW_BOLD;

	if (MF_->IsItalic())
		lf.lfItalic = TRUE;

	lf.lfCharSet = 0;
	lf.lfPitchAndFamily = FF_MODERN;

	lstrcpy(lf.lfFaceName, curFontName);
	font.CreateFontIndirect(&lf);
	CFont* pOldFont = dc.SelectObject(&font);

	ASSERT(m_strTheString.length() != 0);

	DrawTextW(dc,
		tc,
		tc[1] ? 2 : 1,
		&r,
		DT_CENTER | DT_TOP);


	dc.SelectObject(pOldFont);
}

void CChildView::SetTheString(LPCWSTR lpszString)
{
	if (lpszString == NULL)
	{
		m_strTheString = L"";
	}
	else
	{
		WCHAR* p = (WCHAR*)calloc(256, sizeof(WCHAR));
		memcpy(p, lpszString, sizeof(WCHAR)*min(255, wcslen(lpszString)));
		m_strTheString = p;
		free(p);
	}

	m_nCurIndex = 0;
	m_nCurLen = (int)m_strTheString.length();
	InvalidateRect(NULL);

	CString strTitle;
	strTitle.Format(L"%s | %s", m_strTheString.c_str(), AfxGetAppName());
	AfxGetMainWnd()->SetWindowText(strTitle);
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_oleTarget.Register(this);
	return 0;
}

CString CChildView::GetCodeString()
{
	CString strRet;
	if (IS_SURROGATE_PAIR(m_strTheString[m_nCurIndex], m_strTheString[m_nCurIndex + 1]))
	{
		strRet.Format(_T(" 0x%04X,0x%04X"),
			0xFFFF & (WCHAR)(UINT)m_strTheString[m_nCurIndex],
			0xFFFF & (WCHAR)(UINT)m_strTheString[m_nCurIndex + 1]);
	}
	else
	{
		strRet.Format(_T(" 0x%04X=%d"),
			0xFFFF & (WCHAR)(UINT)m_strTheString[m_nCurIndex],
			(UINT)m_strTheString[m_nCurIndex]);
	}
	return strRet;
}

void CChildView::OnLetterPrev() 
{
	if( m_strTheString.length() <= m_nCurIndex )
		return;

	if(m_nCurIndex==0)
		return;

	m_nCurIndex--;
	if (m_nCurIndex != 0)
	{
		if (IS_SURROGATE_PAIR(m_strTheString[m_nCurIndex-1], m_strTheString[m_nCurIndex]))
			m_nCurIndex--;
	}

	InvalidateRect(NULL);
}

void CChildView::OnUpdateLetterPrev(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nCurIndex != 0);
}

void CChildView::OnLetterNext() 
{
	if( m_strTheString.length() <= (m_nCurIndex+1) )
		return;
	
	if (IS_SURROGATE_PAIR(m_strTheString[m_nCurIndex], m_strTheString[m_nCurIndex + 1]))
	{
		++m_nCurIndex;
		if (m_strTheString.length() <= (m_nCurIndex + 1))
		{
			--m_nCurIndex;
			return;
		}
		++m_nCurIndex;
	}
	else
	{
		++m_nCurIndex;
	}

	InvalidateRect(NULL);
}

void CChildView::OnUpdateLetterNext(CCmdUI* pCmdUI) 
{
	if( m_strTheString.length()==0 )
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if(IS_SURROGATE_PAIR(m_strTheString[m_nCurIndex], m_strTheString[m_nCurIndex+1]))
		{
			pCmdUI->Enable(m_strTheString.length() > (m_nCurIndex + 2));
		}
		else
		{
			pCmdUI->Enable(m_strTheString.length() > (m_nCurIndex + 1));
		}
	}
}

void CChildView::OnMenuInputstring() 
{
	CInputDialog dlg;

	if (IDOK != dlg.DoModal())
		return;

	SetTheString(dlg.m_strString);
#ifndef UNICODE
	ASSERT(0);
#endif
	InvalidateRect(NULL);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (MF_->IsMoveByClick())
		OnLetterNext();
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(MF_->IsMoveByClick())
		OnLetterPrev();

	CWnd::OnRButtonDown(nFlags, point);
}




void CChildView::OnMButtonUp(UINT nFlags, CPoint point) 
{
	OnEditCopy();
	
	CWnd ::OnMButtonUp(nFlags, point);
}

void CChildView::OnEditCopy() 
{
	TCHAR c = GetCurChar();

	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, 2*sizeof(TCHAR));
	HGLOBAL h2 = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, 4);

	LPWSTR p = (LPWSTR)GlobalLock(h);
	LPWSTR p2 = (LPWSTR)GlobalLock(h2);
//	lstrcpyW(p, str.c_str());
	p[0] = c;
	p[1] = 0;
	p2[0]=0;
	if( OpenClipboard() )
	{
		if( EmptyClipboard() )
		{
			SetClipboardData(theApp.CF_LARMOJIIGNORE, h2);
			SetClipboardData(CF_UNICODETEXT,h);
		}
		CloseClipboard();

		GlobalUnlock(h);
		GlobalUnlock(h2);

	}
	else
	{
		GlobalFree(h);
		GlobalFree(h2);
	}
}

void CChildView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_strTheString.length() != 0);
}


BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (MF_->IsMoveByWheel())
	{
		if (zDelta < 0)
			OnLetterNext();
		else
			OnLetterPrev();
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
