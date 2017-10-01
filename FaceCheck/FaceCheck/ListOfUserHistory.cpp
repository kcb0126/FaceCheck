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
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}