#include "stdafx.h"
#include "ListOfPersonManage.h"
#include "CellOfPersonManage.h"


IMPLEMENT_DYNCREATE(CListOfPersonManage, CScrollView)

CListOfPersonManage::CListOfPersonManage()
{
}


CListOfPersonManage::~CListOfPersonManage()
{
}

int CListOfPersonManage::GetCellCount()
{
	return m_nCount;
}

CWnd* CListOfPersonManage::GetCellAt(int nIndex)
{
	CCellOfPersonManage* pCell;
	pCell = new CCellOfPersonManage;
	pCell->Create(CCellOfPersonManage::IDD, this);
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}