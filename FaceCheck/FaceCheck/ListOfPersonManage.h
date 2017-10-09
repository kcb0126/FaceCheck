#pragma once
#include "CustomListView.h"

struct tagPersonManageCell
{
	int nNo;
	int nID;
	HBITMAP hPhoto;
	CString strName;
	CString strNickname;
	CString strGender;
	CString strBirthday;
	CString strGuesttype;
	CString strSafetytype;
	CString strBlocked;
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
	std::vector<tagPersonManageCell> m_cellsData;
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

