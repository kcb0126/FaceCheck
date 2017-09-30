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
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}
