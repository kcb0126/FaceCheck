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
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}