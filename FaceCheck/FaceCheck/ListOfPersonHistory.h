#pragma once
#include "CustomListView.h"

struct tagPersonHistoryCell
{
	HBITMAP hPhoto;
	CString strTime;
	CString strName;
	CString strGender;
	CString strAge;
	CString strPlace;
	CString strView;
	CString strComment;
};

class CListOfPersonHistory :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfPersonHistory)

public:
	CListOfPersonHistory();
	~CListOfPersonHistory();

public:
	int m_nCount = 0;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
	std::vector<tagPersonHistoryCell> m_cellsData;
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

