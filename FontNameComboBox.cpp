// FontNameComboBox.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "larmoji.h"
#include "FontNameComboBox.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontNameComboBox

CFontNameComboBox::CFontNameComboBox()
{
}

CFontNameComboBox::~CFontNameComboBox()
{
}


BEGIN_MESSAGE_MAP(CFontNameComboBox, CComboBoxEx)
	//{{AFX_MSG_MAP(CFontNameComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontNameComboBox ���b�Z�[�W �n���h��

void CFontNameComboBox::OnSelchange() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	((CMainFrame*)theApp.m_pMainWnd)->m_wndView.InvalidateRect(NULL);
}
