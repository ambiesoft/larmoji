#if !defined(AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontNameComboBox.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CFontNameComboBox �E�B���h�E

class CFontNameComboBox : public CComboBoxEx
{
// �R���X�g���N�V����
public:
	CFontNameComboBox();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFontNameComboBox)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CFontNameComboBox();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CFontNameComboBox)
	afx_msg void OnSelchange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
