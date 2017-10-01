#include "stdafx.h"
#include "ListOfUserManage.h"
#include "CellOfUserManage.h"


IMPLEMENT_DYNCREATE(CListOfUserManage, CScrollView)

CListOfUserManage::CListOfUserManage()
{
}


CListOfUserManage::~CListOfUserManage()
{
}

int CListOfUserManage::GetCellCount()
{
	return m_nCount;
}

CWnd* CListOfUserManage::GetCellAt(int nIndex)
{
	CCellOfUserManage* pCell;
	pCell = new CCellOfUserManage;
	pCell->Create(CCellOfUserManage::IDD, this);
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}