#if !defined(AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDialog.h
//

/////////////////////////////////////////////////////////////////////////////
// CInputDialog

class CInputDialog : public CDialog
{
public:
	CInputDialog(CWnd* pParent = NULL);

	//{{AFX_DATA(CInputDialog)
	enum { IDD = IDD_DIALOG_INPUT };
	CString	m_strString;
	//}}AFX_DATA


	// ClassWizard
	//{{AFX_VIRTUAL(CInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CInputDialog)
		//
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_editInputString;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_)
