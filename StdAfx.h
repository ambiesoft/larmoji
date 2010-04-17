// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__D5783068_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
#define AFX_STDAFX_H__D5783068_745A_11D5_8E03_A40A1FE48159__INCLUDED_

#pragma warning(disable:4786)
#pragma warning(disable:4018)
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxpriv.h>    // for WM_SETMESSAGESTRING
#include <afxole.h>

#include <string>
#include <set>
using namespace std;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__D5783068_745A_11D5_8E03_A40A1FE48159__INCLUDED_)
