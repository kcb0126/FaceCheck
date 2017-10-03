#pragma once
#include "CustomListView.h"

struct tagMonitorHistoryCell
{
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
};

