#if !defined(AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CInputDialog �_�C�A���O

class CInputDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CInputDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CInputDialog)
	enum { IDD = IDD_DIALOG_INPUT };
	CString	m_strString;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CInputDialog)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_)
