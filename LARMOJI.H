// larmoji.h : LARMOJI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//

#if !defined(AFX_LARMOJI_H__D5783066_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
#define AFX_LARMOJI_H__D5783066_745A_11D5_8E03_A40A1FE48159__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��
#include "strings.h"
/////////////////////////////////////////////////////////////////////////////
// CLarmojiApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� larmoji.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CLarmojiApp : public CWinApp
{
public:
	CLarmojiApp();
	BOOL m_bCopying;
	UINT CF_LARMOJIIGNORE;
// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLarmojiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

public:
	//{{AFX_MSG(CLarmojiApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CLarmojiApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LARMOJI_H__D5783066_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
