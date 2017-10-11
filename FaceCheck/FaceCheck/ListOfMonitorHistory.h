#pragma once
#include "CustomListView.h"

struct tagMonitorHistoryCell
{
	int nIDX;
	HBITMAP hPhoto;
	HBITMAP hPhotoRegistered;
	CString strName;
	CString strAgeGender;
	CString strAccessedWhen;
	CString strStatus;
};

class CListOfMonitorHistory :
	public CCustomListView
{
	DECLARE_DYNCREATE(CListOfMonitorHistory)

public:
	CListOfMonitorHistory();
	~CListOfMonitorHistory();

public:
	int m_nCount = 0;
	virtual int GetCellCount();
	virtual CWnd* GetCellAt(int nIndex);
	std::vector<tagMonitorHistoryCell> m_cellsData;
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

