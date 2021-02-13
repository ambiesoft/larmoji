#pragma once


class COptionDialog : public CDialogEx
{
	DECLARE_DYNAMIC(COptionDialog)

private:
	const wchar_t* SECTION_OPTION = L"Options";
	const wchar_t* KEY_MOVEBYCLICK = L"MoveByClick";
	const wchar_t* KEY_MOVEBYWHELL = L"MoveByWheel";

	LPCWSTR m_pIniPath;
public:
	COptionDialog(LPCWSTR pIniPath, CWnd* pParent = nullptr);
	virtual ~COptionDialog();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bMoveByClick;
	BOOL m_bMoveByWheel;
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
};
