#include "stdafx.h"
#include "ListOfUserHistory.h"
#include "CellOfUserHistory.h"


IMPLEMENT_DYNCREATE(CListOfUserHistory, CScrollView)

CListOfUserHistory::CListOfUserHistory()
{
}


CListOfUserHistory::~CListOfUserHistory()
{
}

int CListOfUserHistory::GetCellCount()
{
	return m_nCount;
}

CWnd* CListOfUserHistory::GetCellAt(int nIndex)
{
	CCellOfUserHistory* pCell;
	pCell = new CCellOfUserHistory;
	pCell->Create(CCellOfUserHistory::IDD, this);
	CString strNo;
	strNo.Format(_T("%d"), m_cellsData[nIndex].nNo);
	pCell->m_lblNo.SetText(strNo);
	pCell->m_strUsername = m_cellsData[nIndex].strUsername;
	pCell->m_strAction = m_cellsData[nIndex].strAction;
	pCell->m_strTime = m_cellsData[nIndex].strTime;
	pCell->m_strContent = m_cellsData[nIndex].strContent;
	pCell->UpdateData(FALSE);
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}BEGIN_MESSAGE_MAP(CListOfUserHistory, CCustomListView)
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CListOfUserHistory::OnEraseBkgnd(CDC* pDC)
{
	CCustomListView::OnEraseBkgnd(pDC);

	if (!pDC)return FALSE;

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
