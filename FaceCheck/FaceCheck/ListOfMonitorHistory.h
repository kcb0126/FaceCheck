#pragma once
#include "CustomListView.h"
class CListOfMonitorHistory :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfMonitorHistory)

public:
	CListOfMonitorHistory();
	~CListOfMonitorHistory();

public:
	int m_nCount = 5;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
};

