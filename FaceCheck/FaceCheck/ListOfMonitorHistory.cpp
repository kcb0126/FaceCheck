#include "stdafx.h"
#include "ListOfMonitorHistory.h"
#include "CellOfMonitorHistory.h"


IMPLEMENT_DYNCREATE(CListOfMonitorHistory, CScrollView)

CListOfMonitorHistory::CListOfMonitorHistory()
{
}


CListOfMonitorHistory::~CListOfMonitorHistory()
{
}

int CListOfMonitorHistory::GetCellCount()
{
	return m_nCount;
}

CWnd* CListOfMonitorHistory::GetCellAt(int nIndex)
{
	CCellOfMonitorHistory* pCell;
	pCell = new CCellOfMonitorHistory;
	pCell->Create(CCellOfMonitorHistory::IDD, this);
	pCell->m_staticPhoto.SetBitmap(m_cellsData[nIndex].hPhoto);
	pCell->m_staticPhotoRegistered.SetBitmap(m_cellsData[nIndex].hPhotoRegistered);
	pCell->m_strName = m_cellsData[nIndex].strName;
	pCell->m_strAgeNGender = m_cellsData[nIndex].strAgeGender;
	pCell->m_strAccessedwhen = m_cellsData[nIndex].strAccessedWhen;
	pCell->m_strStatus = m_cellsData[nIndex].strStatus;
	pCell->UpdateData(FALSE);
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}
BEGIN_MESSAGE_MAP(CListOfMonitorHistory, CCustomListView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CListOfMonitorHistory::OnEraseBkgnd(CDC* pDC)
{
	CCustomListView::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap;

	CBitmap bmpLightGray;
	bmpLightGray.LoadBitmap(IDB_LIGHTGRAY);
	pOldBitmap = dc.SelectObject(&bmpLightGray);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, 100, 100, SRCCOPY);
	return TRUE;
}
