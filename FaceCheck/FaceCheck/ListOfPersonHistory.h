#pragma once
#include "CustomListView.h"
class CListOfPersonHistory :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfPersonHistory)

public:
	CListOfPersonHistory();
	~CListOfPersonHistory();

public:
	int m_nCount = 5;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
};

