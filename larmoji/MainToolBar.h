#if !defined(AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
#define AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_

#include "FontNameComboBox.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainToolBar.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar ウィンドウ

class CMainToolBar : public CToolBar
{
// コンストラクション
public:
	CMainToolBar();

// アトリビュート
public:
	
// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMainToolBar)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	CFontNameComboBox m_wndFontName;
	virtual ~CMainToolBar();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMainToolBar)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAINTOOLBAR_H__354BCF43_7528_11D5_8E03_D89D0C1C4A46__INCLUDED_)
