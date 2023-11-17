#include "StdAfx.h"
#include "larmoji.h"
#include "COptionDialog.h"

using namespace Ambiesoft;

IMPLEMENT_DYNAMIC(COptionDialog, CDialogEx)

COptionDialog::COptionDialog(LPCWSTR pIniPath, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPTION, pParent)
	, m_pIniPath(pIniPath)
	, m_bMoveByClick(FALSE)
	, m_bMoveByWheel(FALSE)
{
	m_bMoveByClick = theApp.GetProfileInt(SECTION_OPTION, KEY_MOVEBYCLICK, FALSE);
	m_bMoveByWheel = theApp.GetProfileInt(SECTION_OPTION, KEY_MOVEBYWHELL, TRUE);
}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_MOVEBYCLICK, m_bMoveByClick);
	DDX_Check(pDX, IDC_CHECK_MOVEBYWHEEL, m_bMoveByWheel);
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialogEx)
END_MESSAGE_MAP()


void COptionDialog::PostNcDestroy()
{
	theApp.WriteProfileInt(SECTION_OPTION, KEY_MOVEBYCLICK, m_bMoveByClick);
	theApp.WriteProfileInt(SECTION_OPTION, KEY_MOVEBYWHELL, m_bMoveByWheel);

	CDialogEx::PostNcDestroy();
}


BOOL COptionDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	i18nChangeDialogText(*this);

	return TRUE;  // return TRUE unless you set the focus to a control
}
