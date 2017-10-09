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
	pCell->m_nNo = m_cellsData[nIndex].nNo;
	pCell->m_staticPhoto.SetBitmap(m_cellsData[nIndex].hPhoto);
	pCell->m_lblName.SetWindowText(m_cellsData[nIndex].strName);
	pCell->m_lblNickname.SetWindowText(m_cellsData[nIndex].strNickname);
	pCell->m_lblGender.SetWindowText(m_cellsData[nIndex].strGender);
	pCell->m_lblBirthday.SetWindowText(m_cellsData[nIndex].strBirthday);
	pCell->m_lblGuesttype.SetWindowText(m_cellsData[nIndex].strGuesttype);
	pCell->m_lblSafetytype.SetWindowText(m_cellsData[nIndex].strSafetytype);
	pCell->m_lblBlocked.SetWindowText(m_cellsData[nIndex].strBlocked);
	pCell->m_nID = m_cellsData[nIndex].nID;
	pCell->UpdateData(FALSE);
	pCell->ShowWindow(SW_SHOW);
	return pCell;
}
BEGIN_MESSAGE_MAP(CListOfPersonManage, CCustomListView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL CListOfPersonManage::OnEraseBkgnd(CDC* pDC)
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
