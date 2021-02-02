#if !defined(AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFontNameComboBox : public CComboBoxEx
{
public:
	CFontNameComboBox();

public:
	// ClassWizard
	//{{AFX_VIRTUAL(CFontNameComboBox)
	//}}AFX_VIRTUAL


public:
	virtual ~CFontNameComboBox();


protected:
	//{{AFX_MSG(CFontNameComboBox)
	afx_msg void OnSelchange();
	//}}AFX_MSG
	afx_msg void OnCloseUp();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
