#pragma once
#include "CustomListView.h"

struct tagUserHistoryCell
{
	int nNo;
	CString strUsername;
	CString strAction;
	CString strTime;
	CString strContent;
};

class CListOfUserHistory :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfUserHistory)

public:
	CListOfUserHistory();
	~CListOfUserHistory();

public:
	int m_nCount = 0;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
	std::vector<tagUserHistoryCell> m_cellsData;
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

