#pragma once
#include "CustomListView.h"
class CListOfUserHistory :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfUserHistory)

public:
	CListOfUserHistory();
	~CListOfUserHistory();

public:
	int m_nCount = 5;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
};

