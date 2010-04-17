// MainDropTarget.cpp: implementation of the CMainDropTarget class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDropTarget.h"
#include "larmoji.h"

#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainDropTarget::CMainDropTarget(CWnd* /* pParent */)
{
}

CMainDropTarget::~CMainDropTarget()
{
}



//
// OnDragEnter is called by OLE dll's when drag cursor enters
// a window that is REGISTERed with the OLE dll's
//
DROPEFFECT CMainDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* 
           pDataObject, DWORD dwKeyState, CPoint point )
{
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(dwKeyState);
	UNREFERENCED_PARAMETER(pWnd);
	if (!pDataObject->IsDataAvailable(CF_UNICODETEXT))
	{
		return DROPEFFECT_NONE;
	
	}

    return DROPEFFECT_COPY;
}

DROPEFFECT CMainDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* 
           pDataObject, DWORD dwKeyState, CPoint point )
{     
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(dwKeyState);
	UNREFERENCED_PARAMETER(pWnd);

	if (!pDataObject->IsDataAvailable(CF_UNICODETEXT))
		return DROPEFFECT_NONE;

    return DROPEFFECT_COPY;  // move source
}


BOOL CMainDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject, 
                 DROPEFFECT dropEffect, CPoint point )
{
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(pWnd);

	if (pDataObject->IsDataAvailable(CF_UNICODETEXT))
	{
		STGMEDIUM Stg;
		pDataObject->GetData(CF_UNICODETEXT, &Stg);		
		((CMainFrame*)theApp.m_pMainWnd)->m_wndView.SetTheString((LPCWSTR)GlobalLock(Stg.hGlobal));
		
				
		GlobalUnlock(Stg.hGlobal);
		GlobalFree(Stg.hGlobal);		

		return 1;
	}

    if((dropEffect&DROPEFFECT_COPY) != DROPEFFECT_COPY)
        return FALSE;

    return TRUE;
}

