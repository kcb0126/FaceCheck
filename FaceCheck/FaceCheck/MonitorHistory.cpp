#include "stdafx.h"
#include "MonitorHistory.h"
#include "MonitorHistoryCell.h"

CMonitorHistory::CMonitorHistory()
{
}


CMonitorHistory::~CMonitorHistory()
{
}

int CMonitorHistory::getCellCount()
{
	return 5;
}

CWnd* CMonitorHistory::getCellAt(int nIndex)
{
	CMonitorHistoryCell* pCell;
	pCell = new CMonitorHistoryCell;
	pCell->Create(CMonitorHistoryCell::IDD, this);
	pCell->ShowWindow(SW_SHOW);

	return pCell;
}