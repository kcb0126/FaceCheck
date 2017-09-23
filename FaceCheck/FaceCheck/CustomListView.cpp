// CustomListView.cpp : implementation file
//

#include "stdafx.h"
#include "CustomListView.h"


// CCustomListView

IMPLEMENT_DYNCREATE(CCustomListView, CScrollView)

CCustomListView::CCustomListView()
{

}

CCustomListView::~CCustomListView()
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		if (m_cells[i] != NULL)
		{
			delete m_cells[i];
			m_cells[i] = NULL;
		}
	}
}


BEGIN_MESSAGE_MAP(CCustomListView, CScrollView)
END_MESSAGE_MAP()


// CCustomListView drawing

void CCustomListView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	this->drawContents();
}

void CCustomListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	for (int i = 0; i < m_cells.size(); i++)
	{
		m_cells[i]->ShowWindow(SW_SHOW);
	}
}


// CCustomListView diagnostics

#ifdef _DEBUG
void CCustomListView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CCustomListView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

void CCustomListView::drawContents()
{
	m_cells.clear();
	int nCount = this->getCellCount();
	int nWidth = 0, nHeight = 0;
	CRect rect;
	CWnd* pCell;
	for (int i = 0; i < nCount; i++)
	{
		pCell = this->getCellAt(i);
		pCell->GetWindowRect(&rect);
		pCell->SetWindowPos(NULL, 0, nHeight, rect.Width(), rect.Height(), SWP_NOZORDER);
		nWidth = (nWidth > rect.Width()) ? nWidth : rect.Width();
		nHeight += rect.Height();
		m_cells.push_back(pCell);
	}
	SIZE sizeTotal;
	sizeTotal.cx = nWidth;
	sizeTotal.cy = nHeight;
	this->SetScrollSizes(MM_TEXT, sizeTotal);
}


// CCustomListView message handlers
