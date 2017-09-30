#pragma once
#include "CustomListView.h"
class CListOfPersonManage :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfPersonManage)

public:
	CListOfPersonManage();
	~CListOfPersonManage();

public:
	int m_nCount = 5;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
};

