#if !defined(AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_

#include "FontNameComboBox.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainToolBar.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar �E�B���h�E

class CMainToolBar : public CToolBar
{
// �R���X�g���N�V����
public:
	CMainToolBar();

// �A�g���r���[�g
public:
	
// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMainToolBar)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	CFontNameComboBox m_wndFontName;
	virtual ~CMainToolBar();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CMainToolBar)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
