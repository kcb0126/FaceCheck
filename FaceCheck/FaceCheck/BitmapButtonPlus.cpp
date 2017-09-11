// BitmapButtonPlus.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "BitmapButtonPlus.h"


// CBitmapButtonPlus

IMPLEMENT_DYNAMIC(CBitmapButtonPlus, CBitmapButton)

CBitmapButtonPlus::CBitmapButtonPlus()
{
	m_clrTrans = RGB(255, 0, 255);
	m_bMouseHover = FALSE;
	m_nIDBitmapResourceHover = 0;
	ZeroMemory(&m_stTrackMouse, sizeof(m_stTrackMouse));
}

CBitmapButtonPlus::~CBitmapButtonPlus()
{
}


BEGIN_MESSAGE_MAP(CBitmapButtonPlus, CBitmapButton)
	ON_WM_ERASEBKGND()
	//	ON_WM_DRAWITEM()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CBitmapButtonPlus message handlers




BOOL CBitmapButtonPlus::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;

	//	return CBitmapButton::OnEraseBkgnd(pDC);
}


void CBitmapButtonPlus::OnMouseMove(UINT nFlags, CPoint point)
{
	if (FALSE == m_bMouseHover)
	{
		::_TrackMouseEvent(&m_stTrackMouse);
		m_bMouseHover = TRUE;
		Invalidate(FALSE);
	}

	CBitmapButton::OnMouseMove(nFlags, point);
}


void CBitmapButtonPlus::OnMouseLeave()
{
	m_bMouseHover = FALSE;
	Invalidate(FALSE);

	CBitmapButton::OnMouseLeave();
}


int CBitmapButtonPlus::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBitmapButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_stTrackMouse.cbSize = sizeof(TRACKMOUSEEVENT);
	m_stTrackMouse.dwFlags = TME_LEAVE;
	m_stTrackMouse.dwHoverTime = HOVER_DEFAULT;
	m_stTrackMouse.hwndTrack = GetSafeHwnd();

	return 0;
}

void CBitmapButtonPlus::SetHoverBitmapID(IN UINT nIDBitmapResourceHover)
{
	m_nIDBitmapResourceHover = nIDBitmapResourceHover;
	if (0 != m_nIDBitmapResourceHover)
	{
		m_cBitmapHover.DeleteObject();
		m_cBitmapHover.LoadBitmap(m_nIDBitmapResourceHover);
	}
}

// cpp file
void CLayoutMgr::DrawBitmapTrans(IN OUT CDC* pDC, IN CBitmap* pcBitmap, IN int x, IN int y, IN COLORREF crMask)
{
	CBitmap		*pOldBitmapImage = NULL;
	CBitmap		*pOldBitmapTrans = NULL;
	COLORREF	clrOldBack = 0;
	COLORREF	clrOldText = 0;
	BITMAP		bm = { 0, };
	CDC			dcImage;
	CDC			dcTrans;
	CBitmap		bitmapTrans;

	if ((NULL == pcBitmap) || (NULL == pDC))
	{
		return;
	}

	pcBitmap->GetBitmap(&bm);
	dcImage.CreateCompatibleDC(pDC);
	pOldBitmapImage = dcImage.SelectObject(pcBitmap);
	clrOldBack = pDC->SetBkColor(RGB(255, 255, 255));
	clrOldText = pDC->SetTextColor(RGB(0, 0, 0));
	dcTrans.CreateCompatibleDC(pDC);
	bitmapTrans.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);
	dcImage.SetBkColor(crMask);
	dcTrans.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCINVERT);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcTrans, 0, 0, SRCAND);
	pDC->BitBlt(x, y, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCINVERT);
	dcTrans.SelectObject(pOldBitmapTrans);
	pDC->SetBkColor(clrOldBack);
	pDC->SetTextColor(clrOldText);
	bitmapTrans.DeleteObject();
	dcTrans.DeleteDC();
	dcImage.SelectObject(pOldBitmapImage);
	dcImage.DeleteDC();
}

void CBitmapButtonPlus::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct != NULL);
	// must have at least the first bitmap loaded before calling DrawItem
	ASSERT(m_bitmap.m_hObject != NULL);		//required

	// use the main bitmap for up, the selected bitmap for down
	CBitmap * pBitmap = &m_bitmap;
	UINT state = lpDrawItemStruct->itemState;
	if ((state & ODS_SELECTED) && m_bitmapSel.m_hObject != NULL)
		pBitmap = &m_bitmap;
	else if ((state & ODS_FOCUS) && m_bitmapFocus.m_hObject != NULL)
		pBitmap = &m_bitmapFocus;			// third image for focused
	else if ((state & ODS_DISABLED) && m_bitmapDisabled.m_hObject != NULL)
		pBitmap = &m_bitmapDisabled;		// last image for disabled
	if ((TRUE == m_bMouseHover) && NULL != m_cBitmapHover.GetSafeHandle())
	{
		pBitmap = &m_cBitmapHover;
	}

	// draw the whole button
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CRect rect;
	rect.CopyRect(&lpDrawItemStruct->rcItem);

	CLayoutMgr::DrawBitmapTrans(pDC, pBitmap, rect.left, rect.top, m_clrTrans);
}

void CBitmapButtonPlus::OnSet() {
	m_stTrackMouse.cbSize = sizeof(TRACKMOUSEEVENT);
	m_stTrackMouse.dwFlags = TME_LEAVE;
	m_stTrackMouse.dwHoverTime = HOVER_DEFAULT;
	m_stTrackMouse.hwndTrack = GetSafeHwnd();
}