#if !defined(AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_

#include "FontNameComboBox.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainToolBar.h :
//

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar

class CMainToolBar : public CToolBar
{
public:
	CMainToolBar();

public:
	
public:

	// ClassWizard
	//{{AFX_VIRTUAL(CMainToolBar)
	//}}AFX_VIRTUAL

public:
	CFontNameComboBox m_cmbFontName;
	virtual ~CMainToolBar();

protected:
	//{{AFX_MSG(CMainToolBar)
		// 
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
