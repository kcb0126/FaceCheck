#pragma once
#include "CustomListView.h"
class CListOfUserManage :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfUserManage)

public:
	CListOfUserManage();
	~CListOfUserManage();

public:
	int m_nCount = 5;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
};

