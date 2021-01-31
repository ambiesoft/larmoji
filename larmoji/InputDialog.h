#if !defined(AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDialog.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CInputDialog ダイアログ

class CInputDialog : public CDialog
{
// コンストラクション
public:
	CInputDialog(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CInputDialog)
	enum { IDD = IDD_DIALOG_INPUT };
	CString	m_strString;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CInputDialog)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_INPUTDIALOG_H__4D71F109_753F_11D5_8E03_D89D0C1C4A46__INCLUDED_)
