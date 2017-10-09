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
	CString strNo;
	strNo.Format(_T("%d"), m_cellsData[nIndex]);
	pCell->m_lblNo.SetText(strNo);
	pCell->m_strUsername = m_cellsData[nIndex].strUsername;
	pCell->m_strPrivilege = m_cellsData[nIndex].strPrivilege;
	pCell->m_strCreator = m_cellsData[nIndex].strCreator;
	pCell->m_strPhoneNo = m_cellsData[nIndex].strPhoneNo;
	pCell->m_strBlocked = m_cellsData[nIndex].strBlocked;
	pCell->m_nIndex = nIndex;
	pCell->UpdateData(FALSE);
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}BEGIN_MESSAGE_MAP(CListOfUserManage, CCustomListView)
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CListOfUserManage::OnEraseBkgnd(CDC* pDC)
{
	CCustomListView::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap;

	CBitmap bmpLightGray;
	bmpLightGray.LoadBitmap(IDB_LIGHTGRAY);
	pOldBitmap = dc.SelectObject(&bmpLightGray);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, 100, 100, SRCCOPY);
	return TRUE;
}
