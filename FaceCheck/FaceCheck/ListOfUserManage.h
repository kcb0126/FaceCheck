#pragma once
#include "CustomListView.h"

struct tagUserManageCell
{
	int nIndex;
	CString strUsername;
	CString strPrivilege;
	CString strCreator;
	CString strPhoneNo;
	CString strBlocked;
};

class CListOfUserManage :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfUserManage)

public:
	CListOfUserManage();
	~CListOfUserManage();

public:
	int m_nCount = 0;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
	std::vector<tagUserManageCell> m_cellsData;
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

