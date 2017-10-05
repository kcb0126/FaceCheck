#include "stdafx.h"
#include "ListOfPersonHistory.h"
#include "CellOfPersonHistory.h"


IMPLEMENT_DYNCREATE(CListOfPersonHistory, CScrollView)

CListOfPersonHistory::CListOfPersonHistory()
{
}


CListOfPersonHistory::~CListOfPersonHistory()
{
}

int CListOfPersonHistory::GetCellCount()
{
	return m_nCount;
}

CWnd* CListOfPersonHistory::GetCellAt(int nIndex)
{
	CCellOfPersonHistory* pCell;
	pCell = new CCellOfPersonHistory;
	pCell->Create(CCellOfPersonHistory::IDD, this);
	pCell->m_staticPhoto.SetBitmap(m_cellsData[nIndex].hPhoto);
	pCell->m_strTime = m_cellsData[nIndex].strTime;
	pCell->m_strName = m_cellsData[nIndex].strName;
	pCell->m_strGender = m_cellsData[nIndex].strGender;
	pCell->m_strAge = m_cellsData[nIndex].strAge;
	pCell->m_strPlace = m_cellsData[nIndex].strPlace;
	pCell->m_strView = m_cellsData[nIndex].strView;
	pCell->m_strComment = m_cellsData[nIndex].strComment;
	pCell->UpdateData(FALSE);
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}BEGIN_MESSAGE_MAP(CListOfPersonHistory, CCustomListView)
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CListOfPersonHistory::OnEraseBkgnd(CDC* pDC)
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
