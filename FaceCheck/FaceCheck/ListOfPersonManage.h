#pragma once
#include "CustomListView.h"

struct tagPersonManageCell
{

};

class CListOfPersonManage :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfPersonManage)

public:
	CListOfPersonManage();
	~CListOfPersonManage();

public:
	int m_nCount = 0;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
};

