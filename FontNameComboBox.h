#if !defined(AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FontNameComboBox.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CFontNameComboBox ウィンドウ

class CFontNameComboBox : public CComboBoxEx
{
// コンストラクション
public:
	CFontNameComboBox();

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CFontNameComboBox)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CFontNameComboBox();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CFontNameComboBox)
	afx_msg void OnSelchange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_FONTNAMECOMBOBOX_H__354BCF44_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
