#if !defined(AFX_OLEFAVDROPTARGET_H__2EA91880_6752_11D4_8DFC_9BA945BEAE5A__INCLUDED_)
#define AFX_OLEFAVDROPTARGET_H__2EA91880_6752_11D4_8DFC_9BA945BEAE5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDropTarget.h
//

class CShellTreeFav;
class CMainDropTarget : public COleDropTarget  
{
public:
	CMainDropTarget(CWnd* pParent = NULL);
	virtual ~CMainDropTarget();

   DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD 
                                                dwKeyState, CPoint point );
   DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD 
                                               dwKeyState, CPoint point );
   
   BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT 
                                          dropEffect, CPoint point );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++

#endif // !defined(AFX_OLEFAVDROPTARGET_H__2EA91880_6752_11D4_8DFC_9BA945BEAE5A__INCLUDED_)
